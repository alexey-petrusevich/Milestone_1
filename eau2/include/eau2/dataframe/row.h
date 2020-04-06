#pragma once

#include "../collections/arrays/column_array.h"
#include "../utils/object.h"
#include "../utils/string.h"
#include "fielders/fielder.h"
#include "schema.h"

/**
 * @brief This file represents implementation of the Row class that is used by
 * DataFrame.
 * @file row.h
 * @author Aliaksei Petrusevich <petrusevich.a@husky.neu.edu>
 * @author Megha Rao <rao.m@husky.neu.edu>
 * @date March 30, 2020
 */

/**
 * @brief This class represents a single row of data constructed according to a
 * data frame's schema. The purpose of this class is to make it easier to add
 * read/write complete rows. Internally a data frame hold data in columns.
 * Rows have pointer equality.
 * @file row.h
 * @author Aliaksei Petrusevich <petrusevich.a@husky.neu.edu>
 * @author Megha Rao <rao.m@husky.neu.edu>
 * @date March 30, 2020
 */
class Row : public Object {
   public:
    Schema *schema;  // owned
    ColumnArray *columnArray;
    size_t rowIndex;

    /** Build a row following a schema.
     *
     * @param scm the given schema being used by this row
     */
    Row(Schema &scm);

    /**
     * Initializes the column array of this Row.
     */
    void initColumnArray();

    /**
     * Constructor that accepts a pointer to the ColumnArray containing data,
     * and uses its schema to define the schema of this row.
     * @param columnArray ColumnArray containing the data for this row
     * @param rowIndex the index of the row in the given Data Frame
     */
    Row(ColumnArray *columnArray, size_t rowIndex);

    /** Setters: set the given column with the given value.
     * @param col the column index of the value being set
     * @param val the integer value of the new entry
     */
    void set(size_t col, int val);

    /**
     * Sets the value of the given column with a given double.
     * @param col the column index of the entry being set
     * @param val the double value of the new entry
     */
    void set(size_t col, double val);

    /**
     * Sets the value of the given column with a given boolean.
     * @param col the column index of the entry being set
     * @param val the boolean value of the new entry
     */
    void set(size_t col, bool val);

    /**
     * Sets the value of the given column with a given String.
     * Acquire ownership of the string.
     *
     * @param col the column index of the entry being set
     * @param val the String value of the new entry
     */
    void set(size_t col, String *val);

    /**
     * Sets the row index of this row in the data frame.
     *
     * @param idx the index of the row in the data frame this row is associated
     * with
     */
    void set_idx(size_t idx);

    /**
     * Returns the row index of this row.
     *
     * @return the row index of this row in the data frame
     */
    size_t get_idx();

    /**
     * Returns the integer value of the given column.
     *
     * @param col the index of the column which value is being requested
     * @return the value of the column at the given index
     */
    int get_int(size_t col);

    /**
     * Returns the boolean value of the given column.
     * @param col the index of the column which value is being requested
     * @return the value of the column at the given index
     */
    bool get_bool(size_t col);

    /**
     * Returns the double value of the given column.
     * @param col the index of the column which value is being requested
     * @return the value of the column at the given index
     */
    double get_double(size_t col);

    /**
     * Returns the String value of the given column.
     *
     * @param col the index of the column which value is being requested
     * @return the value of the column at the given index
     */
    String *get_string(size_t col);

    /** Number of fields in the row.
     *
     * @return the number of fields in this row
     */
    size_t width();

    /**
     * Type of the field at the given position. An idx >= width is
     * undefined.
     * @param idx the index of the column which type is being requested
     * @return the type of the column being requested
     */
    char col_type(size_t idx);

    /**
     * Given a Fielder, visit every field of this row. Calling this method
     * before the row's fields have been set is undefined.
     * @param idx the index of the row in the data frame this row is associated
     * with
     * @param f the fields being used to iterate through the field of
     * the row at the given index
     */
    void visit(size_t idx, Fielder &f);

    /**
     * Destructor of this row.
     */
    virtual ~Row();
};