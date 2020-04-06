#include "../../include/eau2/sorer/sorer.h"

#include <unistd.h>

#include <cstdlib>
#include <iostream>

SOR::SOR() { columnArray = new ColumnArray(); }

SOR::~SOR() { delete columnArray; }

ColType SOR::get_col_type(size_t index) {
    if (index >= static_cast<size_t>(this->columnArray->size())) {
        return ColType::UNKNOWN;
    }
    return this->columnArray->get(index)->get_type();
}

char* SOR::get_value(size_t col_index, size_t row_index) {
    if (col_index >= static_cast<size_t>(this->columnArray->size())) {
        return nullptr;
    }
    return this->columnArray->get(col_index)->get_char(row_index);
}

bool SOR::is_missing(size_t col_index, size_t row_index) {
    return this->get_value(col_index, row_index) == nullptr;
}

void SOR::read(FILE* f, size_t from, size_t len) {
    this->infer_columns_(f, from, len);
    this->parse_(f, from, len);
}

void SOR::seek_(FILE* f, size_t from) {
    if (from == 0) {
        fseek(f, from, SEEK_SET);
    } else {
        char buf[buff_len];
        fseek(f, from - 1, SEEK_SET);
        fgets(buf, buff_len, f);
    }
}

void SOR::infer_columns_(FILE* f, size_t from, size_t len) {
    seek_(f, from);
    char buf[buff_len];

    if (fgets(buf, buff_len, f) == nullptr) {
        exit(1);
    }

    // get the number of fields (columns)
    size_t num_fields;
    char** row = parse_row_(buf, &num_fields);

    for (size_t i = 0; i < num_fields; i++) {
        ColType inferred_type = infer_type(row[i]);
        switch (inferred_type) {
            case ColType::BOOLEAN:
                this->columnArray->append(new BoolColumn());
                break;
            case ColType::INTEGER:
                this->columnArray->append(new IntColumn());
                break;
            case ColType::DOUBLE:
                this->columnArray->append(new DoubleColumn());
                break;
            default:
                this->columnArray->append(new StringColumn());
                break;
        }
    }
    delete[] row;
}

char* SOR::parse_field_(char* field, int* len) {
    char* ret = field;
    int j = 0;
    for (size_t i = 0; field[i] != '>'; i++) {
        switch (field[i]) {
            case '<':  // Malformed input
                affirm(false, "Multiple opening <");
            case ' ':  // extra space in front of field
                ret++;
                break;
            case '"':  // the start of a String
                ret++;
                j = i + 1;
                while (field[j] !=
                       '"') {  // add every character until a end quote is met.
                    j++;
                }
                field[j] = '\0';
                *len = j;
                return ret;
            default:  // add every ASCII character to field return value.
                for (j = i; field[j] != '>' && field[j] != ' '; j++)
                    ;
                field[j] = '\0';
                *len = j;
                return ret;
        }
    }
    *len = 0;
    return nullptr;  // missing value
}

char** SOR::parse_row_(char* row, size_t* len) {
    int cap = 16;
    int l = 0;
    char** output = new char*[cap];

    for (size_t i = 0; row[i] != '\0'; i++) {
        if (row[i] == '<') {
            int to_increment = 0;
            if (l >= cap) {
                cap *= 2;
                char** temp = new char*[cap];
                for (int k = 0; k < l; k++) {
                    temp[k] = output[k];
                }
                delete[] output;
                output = temp;
            }

            output[l++] = parse_field_(&row[i + 1], &to_increment);
            i = i + to_increment + 1;
        }
    }

    *len = l;
    return output;
}

void SOR::parse_(FILE* f, size_t from, size_t len) {
    seek_(f, from);
    char buf[buff_len];

    // read a line from the file
    while (fgets(buf, buff_len, f) != nullptr) {
        // number of fields
        size_t num_fields;
        // current row could have more columns than infered - parse the
        // frist len_ columns
        char** row = parse_row_(buf, &num_fields);
        // skipping rows with too few fields
        if (num_fields == 0) {
            delete[] row;
            continue;
        }

        // we skip the row as soon as we find a field that does not match
        // our schema
        bool skip = false;
        for (int i = 0; i < this->columnArray->size(); i++) {
            if (!this->columnArray->get(i)->can_add(row[i])) {
                skip = true;
                break;
            }
        }
        if (skip) {
            delete[] row;
            continue;
        }

        // add all fields in this row to columns
        for (size_t i = 0; i < static_cast<size_t>(this->columnArray->size());
             i++) {
            Column* col = this->columnArray->get(i);
            if (i >= num_fields || row[i] == nullptr) {
                col->push_nullptr();
            } else {
                col->push_back(row[i]);
            }
        }
        delete[] row;
    }
}

DataFrame* SOR::get_dataframe() {
    return DataFrame::fromColumns(this->columnArray);
}