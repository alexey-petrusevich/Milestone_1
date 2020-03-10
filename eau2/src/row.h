//lang::CwC
#pragma once

#include "object.h"
#include "string.h"
#include "schema.h"
#include "columns.h"
#include "fielder.h"


/*************************************************************************
 * Row::
 *
 * This class represents a single row of data constructed according to a
 * data frame's schema. The purpose of this class is to make it easier to add
 * read/write complete rows. Internally a data frame hold data in columns.
 * Rows have pointer equality.
 */
class Row : public Object {
public:
    Schema *schema; // owned
    ColumnArray* columnArray;
    size_t rowIndex;


    /** Build a row following a schema.
     *
     * @param scm the given schema being used by this row
     */
    Row(Schema &scm) {
        this->schema = new Schema(scm);
        this->initColumnArray();
    }


    void initColumnArray() {
        this->columnArray = new ColumnArray(this->schema->numCols);
        for (size_t colIndex = 0; colIndex < this->schema->numCols; colIndex++) {
            switch (this->schema->col_type(colIndex)) {
            case INTEGER:
                this->columnArray->append(new IntColumn(1));
                this->columnArray->get(colIndex)->push_back(0);
                break;
            case FLOAT:
                this->columnArray->append(new FloatColumn(1));
                this->columnArray->get(colIndex)->push_back(0);
                break;
            case BOOLEAN:
                this->columnArray->append(new BoolColumn(1));
                this->columnArray->get(colIndex)->push_back(false);
                break;
            case STRING:
                this->columnArray->append(new StringColumn(1));
                this->columnArray->get(colIndex)->push_back(nullptr);
                break;
            default:
                assert(false);
            }
        }
    }


    /**
     * Constructor that accepts a pointer to the ColumnArray containing data, and uses its schema
     * to define the schema of this row.
     *
     * @param columnArray ColumnArray containing the data for this row
     * @param rowIndex the index of the row in the given Data Frame
     */
    Row(ColumnArray *columnArray, size_t rowIndex) {
        assert(columnArray != nullptr);
        assert(rowIndex < columnArray->get(0)->size());
        this->columnArray = columnArray;
        Schema* schema = columnArray->getSchema();
        this->schema = new Schema(*schema);
        this->rowIndex = rowIndex;
        delete schema;
    }
    

    /** Setters: set the given column with the given value.
     *
     * @param col the column index of the value being set
     * @param val the integer value of the new entry
     */
    void set(size_t col, int val) {
        assert(col < this->schema->numCols);
        assert(this->columnArray != nullptr);
        IntColumn *intColumn = this->columnArray->get(col)->as_int();
        intColumn->set(0, val);
    }


    /**
     * Sets the value of the given column with a given float.
     *
     * @param col the column index of the entry being set
     * @param val the float value of the new entry
     */
    void set(size_t col, float val) {
        assert(col < this->schema->numCols);
        assert(this->columnArray != nullptr);
        FloatColumn *floatColumn = this->columnArray->get(col)->as_float();
        floatColumn->set(0, val);
    }


    /**
     * Sets the value of the given column with a given boolean.
     *
     * @param col the column index of the entry being set
     * @param val the boolean value of the new entry
     */
    void set(size_t col, bool val) {
        assert(col < this->schema->numCols);
        assert(this->columnArray != nullptr);
        BoolColumn *boolColumn = this->columnArray->get(col)->as_bool();
        boolColumn->set(0, val);
    }


    /**
     * Sets the value of the given column with a given String.
     * Acquire ownership of the string.
     *
     * @param col the column index of the entry being set
     * @param val the String value of the new entry
     */
    void set(size_t col, String *val) {
        assert(col < this->schema->numCols);
        assert(this->columnArray != nullptr);
        StringColumn *stringColumn = this->columnArray->get(col)->as_string();
        stringColumn->set(0, val);
    }


    /** Set/get the index of this row (ie. its position in the data frame. This is
     *  only used for informational purposes, unused otherwise */
    /**
     * Sets the row index of this row in the data frame.
     *
     * @param idx the index of the row in the data frame this row is associated
     * with
     */
    void set_idx(size_t idx) {
        assert(idx < this->schema->numRows);
        this->rowIndex = idx;
    }


    /**
     * Returns the row index of this row.
     *
     * @return the row index of this row in the data frame
     */
    size_t get_idx() {
        return this->rowIndex;
    }


    /** Getters: get the value at the given column. If the column is not
      * of the requested type, the result is undefined. */
    /**
     * Returns the integer value of the given column.
     *
     * @param col the index of the column which value is being requested
     * @return the value of the column at the given index
     */
    int get_int(size_t col) {
        assert(col < this->schema->numCols);
        IntColumn *intColumn = this->columnArray->get(col)->as_int();
        return intColumn->get(0);
    }


    /**
     * Returns the boolean value of the given column.
     *
     * @param col the index of the column which value is being requested
     * @return the value of the column at the given index
     */
    bool get_bool(size_t col) {
        assert(col < this->schema->numCols);
        BoolColumn *boolColumn = this->columnArray->get(col)->as_bool();
        return boolColumn->get(0);
    }


    /**
     * Returns the float value of the given column.
     *
     * @param col the index of the column which value is being requested
     * @return the value of the column at the given index
     */
    float get_float(size_t col) {
        assert(col < this->schema->numCols);
        FloatColumn *floatColumn = this->columnArray->get(col)->as_float();
        return floatColumn->get(0);
    }


    /**
     * Returns the String value of the given column.
     *
     * @param col the index of the column which value is being requested
     * @return the value of the column at the given index
     */
    String *get_string(size_t col) {
        assert(col < this->schema->numCols);
        StringColumn *stringColumn = this->columnArray->get(col)->as_string();
        return stringColumn->get(0);
    }


    /** Number of fields in the row.
     *
     * @return the number of fields in this row
     */
    size_t width() {
        return this->schema->width();
    }


    /** Type of the field at the given position. An idx >= width is
     *  undefined.
     *
     *  @param idx the index of the column which type is being requested
     *  @return the type of the column being requested
     */
    char col_type(size_t idx) {
        // idx is the index of the column
        assert(idx < this->schema->numCols);
        return this->schema->col_type(idx);
    }


    /** Given a Fielder, visit every field of this row.
      * Calling this method before the row's fields have been set is undefined.
          *
          * @param idx the index of the row in the data frame this row is associated
          * with
          * @param f the fields being used to iterate through the field of
          * the row at the given index
          * */
    void visit(size_t idx, Fielder &f) {
        assert(idx == this->rowIndex);
        assert(this->columnArray != nullptr);

        f.start(idx);

        for (size_t colIndex = 0; colIndex < this->schema->numCols; colIndex++) {
            this->columnArray->get(colIndex)->accept(&f);
        }
        // all fields have been seen
        f.done();
    }


    /**
     * Destructor of this row.
     */
    virtual ~Row() {
        delete this->schema;
    }

};