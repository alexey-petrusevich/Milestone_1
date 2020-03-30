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

/**
 * @brief This file represents the sorer parses that reads the file in sor
 * format and creates a SOR object capable of returning the data in form of
 * DataFrame. The original code was taken from icicle team and then refactored
 * to fit into our implementation of the DataFrame.
 * @file sorer.h
 * @author icicle
 * @author Aliaksei Petrusevich <petrusevich.a@husky.neu.edu
 * @author Megha Rao <rao.m@husky.neu.edu>
 * @date March 30, 2020
 */

/**
 * @brief Represents a class that parses a sorer-type file into a format
 * represemtable by DataFrame class. Originally created by icicle team and then
 * refactored to fit our DataFrame class.
 * @file sorer.h
 * @author icicle
 * @author Aliaksei Petrusevich <petrusevich.a@husky.neu.edu
 * @author Megha Rao <rao.m@husky.neu.edu>
 * @date March 30, 2020
 */
class SOR : public Object {
   public:
    ColumnArray* columnArray;

    /**
     * Constructor of this SOR class.
     */
    SOR() { columnArray = new ColumnArray(); }

    /**
     * Destructor of this SOR class.
     */
    ~SOR() { delete columnArray; }

    /**
     * Returns the type of the column given its index. If index out of bounds,
     * returns ColType::UNKNOWN.
     *
     * @param index the column index of the column type being requested
     * @return the type of the requested column represented as ColType
     */
    ColType get_col_type(size_t index) {
        if (index >= static_cast<size_t>(this->columnArray->size())) {
            return ColType::UNKNOWN;
        }
        return this->columnArray->get(index)->get_type();
    }

    /**
     * Returns the value at the given column and row indices. If values are out
     * of bounds, returns nullptr. The return value is of c-string type.
     *
     * @param col_index the column index of the value being requested
     * @param row_index the row index of the value being requested
     * @return the value at the given col and row index as c-string
     */
    char* get_value(size_t col_index, size_t row_index) {
        if (col_index >= static_cast<size_t>(this->columnArray->size())) {
            return nullptr;
        }
        return this->columnArray->get(col_index)->get_char(row_index);
    }

    /**
     * Returns true if the value at the given index is missing.
     *
     * @param col_index the column index of the value being checked
     * @param row_index the row index of the value being checked
     * @return true if the value is missing and false otherwise
     */
    bool is_missing(size_t col_index, size_t row_index) {
        return this->get_value(col_index, row_index) == nullptr;
    }

    /**
     * Reads the data from the given file starting from the specified byte for
     * specified length. The read value is stored as ColumnArray.
     * 
     * @param f the file being read
     * @param from the starting position of reading the file
     * @param len the length of the sequence being read from the file
     */
    void read(FILE* f, size_t from, size_t len) {
        this->infer_columns_(f, from, len);
        this->parse_(f, from, len);
    }

    /**
     * Moves the file pointer to the start of the next line.
     *
     * @param f the file being read
     * @param from the starting index file pointer is being moved to
     */
    void seek_(FILE* f, size_t from) {
        if (from == 0) {
            fseek(f, from, SEEK_SET);
        } else {
            char buf[buff_len];
            fseek(f, from - 1, SEEK_SET);
            fgets(buf, buff_len, f);
        }
    }

    /**
     * Infers the schema of the columns by reading the first row.
     *
     * @param f the file being read
     * @param from the starting position of the file
     * @param len the length of the row
     */
    void infer_columns_(FILE* f, size_t from, size_t len) {
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

    /**
     * Finds the start of the field value and null terminate it. Assumes that
     * input fields is terminated by '>' character. Note: muates the value of
     * the field.
     * @param field the field being parsed
     * @param len the offset of the null byte
     */
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

    /**
     * Parses the given row of data read from the file by this sorer. The value
     * returned is an array of c-strings representing processed values read from
     * the sorer-type file. Note: mutates the given raw row value.
     * @param row the raw row data read from the sorer-type file
     * @param len the pointer to the value storing the number of values in the
     * row
     * @return the row of processed values
     */
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

    /**
     * Reads the rows from the starting byte up to len bytes into Columns.
     * @param f the file information is being read from
     * @param from the starting position to be read from the file
     * @param len the byte length of the file
     */
    void parse_(FILE* f, size_t from, size_t len) {
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
            for (size_t i = 0;
                 i < static_cast<size_t>(this->columnArray->size()); i++) {
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

    /**
     * Returns this SOR object as a DataFrame.
     *
     * @return this SOR object as DataFrame
     */
    DataFrame* get_dataframe() {
        return DataFrame::fromColumns(this->columnArray);
    }
};
