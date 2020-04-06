#pragma once
#include "../collections/arrays/array.h"
#include "../dataframe/dataframe.h"
#include "../utils/object.h"
#include "helpers.h"

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
    SOR();

    /**
     * Destructor of this SOR class.
     */
    ~SOR();

    /**
     * Returns the type of the column given its index. If index out of bounds,
     * returns ColType::UNKNOWN.
     *
     * @param index the column index of the column type being requested
     * @return the type of the requested column represented as ColType
     */
    ColType get_col_type(size_t index);

    /**
     * Returns the value at the given column and row indices. If values are out
     * of bounds, returns nullptr. The return value is of c-string type.
     *
     * @param col_index the column index of the value being requested
     * @param row_index the row index of the value being requested
     * @return the value at the given col and row index as c-string
     */
    char* get_value(size_t col_index, size_t row_index);

    /**
     * Returns true if the value at the given index is missing.
     *
     * @param col_index the column index of the value being checked
     * @param row_index the row index of the value being checked
     * @return true if the value is missing and false otherwise
     */
    bool is_missing(size_t col_index, size_t row_index);

    /**
     * Reads the data from the given file starting from the specified byte for
     * specified length. The read value is stored as ColumnArray.
     *
     * @param f the file being read
     * @param from the starting position of reading the file
     * @param len the length of the sequence being read from the file
     */
    void read(FILE* f, size_t from, size_t len);

    /**
     * Moves the file pointer to the start of the next line.
     *
     * @param f the file being read
     * @param from the starting index file pointer is being moved to
     */
    void seek_(FILE* f, size_t from);

    /**
     * Infers the schema of the columns by reading the first row.
     *
     * @param f the file being read
     * @param from the starting position of the file
     * @param len the length of the row
     */
    void infer_columns_(FILE* f, size_t from, size_t len);

    /**
     * Finds the start of the field value and null terminate it. Assumes that
     * input fields is terminated by '>' character. Note: muates the value of
     * the field.
     * @param field the field being parsed
     * @param len the offset of the null byte
     */
    char* parse_field_(char* field, int* len);

    /**
     * Parses the given row of data read from the file by this sorer. The value
     * returned is an array of c-strings representing processed values read from
     * the sorer-type file. Note: mutates the given raw row value.
     * @param row the raw row data read from the sorer-type file
     * @param len the pointer to the value storing the number of values in the
     * row
     * @return the row of processed values
     */
    char** parse_row_(char* row, size_t* len);

    /**
     * Reads the rows from the starting byte up to len bytes into Columns.
     * @param f the file information is being read from
     * @param from the starting position to be read from the file
     * @param len the byte length of the file
     */
    void parse_(FILE* f, size_t from, size_t len);

    /**
     * Returns this SOR object as a DataFrame.
     *
     * @return this SOR object as DataFrame
     */
    DataFrame* get_dataframe();
};
