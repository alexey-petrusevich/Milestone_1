// lang:CwC
// NOTE: the base code is taken from icicle
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "coltypes.h"
#include "columns.h"
#include "dataframe.h"
#include "helpers.h"
#include "object.h"

// The maximum length of a line buffer. No lines over 4095 bytes
static const int buff_len = 4096;

// Reads a file and determines the schema on read
class SOR : public Object {
   public:
    ColumnArray* columnArray;
    // Column** cols_;  // owned
    DataFrame* df;

    // constructor of the sorer
    SOR() { columnArray = new ColumnArray(); }

    // destructor of the sorer
    ~SOR() { delete columnArray; }

    // What is the type of the column at the given index? i
    // if the index is too big a -1 is returned
    ColType get_col_type(size_t index) {
        if (index >= this->columnArray->size()) {
            return ColType::UNKNOWN;
        }
        return this->columnArray->get(index)->get_type();
    }

    // What is the value for the given column index and row index?
    // If the coluumn or row index are too large a nullptr is returned
    char* get_value(size_t col_index, size_t row_index) {
        if (col_index >= this->columnArray->size()) {
            return nullptr;
        }
        return this->columnArray->get(col_index)->get_char(row_index);
    }

    // Is there a value at the given column and row index.
    // If the indexes are too large, true is returned.
    bool is_missing(size_t col_index, size_t row_index) {
        return this->get_value(col_index, row_index) == nullptr;
    }

    // Reads in the data from the file starting at the from byte
    // and reading at most len bytes
    void read(FILE* f, size_t from, size_t len) {
        this->infer_columns_(f, from, len);
        this->parse_(f, from, len);
    }

    // moves the file pointer to the start of the next line.
    void seek_(FILE* f, size_t from) {
        if (from == 0) {
            fseek(f, from, SEEK_SET);
        } else {
            char buf[buff_len];
            fseek(f, from - 1, SEEK_SET);
            fgets(buf, buff_len, f);
        }
    }

    // infers and creates the column objects
    void infer_columns_(FILE* f, size_t from, size_t len) {
        seek_(f, from);
        char buf[buff_len];

        size_t total_bytes = 0;
        size_t row_count = 0;
        while (fgets(buf, buff_len, f) != nullptr && row_count < 500) {
            row_count++;
            total_bytes += strlen(buf);
            if (total_bytes >= len) {
                break;
            }

            // get the number of fields (columns)
            size_t num_fields;
            char** row = parse_row_(buf, &num_fields);

            for (size_t i = 0; i < num_fields; i++) {
                if (i >= this->columnArray->size()) {
                    this->columnArray->append(new BoolColumn());
                }
                ColType inferred_type = infer_type(row[i]);
                if (inferred_type > this->columnArray->get(i)->get_type()) {
                    // delete cols_[i];
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
            }
            delete[] row;
        }
    }

    // Find the start of the field value and null terminate it.
    // ASSUMPTION: input field is terminated by '>' char
    // NOTE: will mutate the field value
    // The value of len will be the offset of the null byte
    char* parse_field_(char* field, int* len) {
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
                    while (
                        field[j] !=
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

    // parses a row and returns a list of field values as char*
    // NOTE: will mutate the row value.
    // The value of len will be the number of fields returned
    char** parse_row_(char* row, size_t* len) {
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

    // read the rows from the starting byte up to len bytes into Columns.
    void parse_(FILE* f, size_t from, size_t len) {
        seek_(f, from);
        char buf[buff_len];

        size_t total_bytes = 0;

        // read a line from the file
        while (fgets(buf, buff_len, f) != nullptr) {
            total_bytes += strlen(buf);
            if (total_bytes >= len) {
                break;
            }

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
            for (size_t i = 0; i < this->columnArray->size(); i++) {
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
            for (size_t i = 0; i < this->columnArray->size(); i++) {
                if (i >= num_fields || row[i] == nullptr) {
                    this->columnArray->get(i)->push_nullptr();
                } else {
                    this->columnArray->get(i)->push_back(row[i]);
                }
            }
            delete[] row;
        }
    }

    // returns SOR object as DataFrame
    DataFrame* get_dataframe() {
        return DataFrame::fromColumns(this->columnArray);
    }
};
