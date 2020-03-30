//lang:CwC

#pragma once

#include "object.h"
#include "string.h"
#include "array.h"
#include "coltypes.h"


/*************************************************************************
 * Schema::
 * A schema is a description of the contents of a data frame, the schema
 * knows the number of columns and number of rows, the type of each column,
 * optionally columns and rows can be named by strings.
 * The valid types are represented by the chars 'S', 'B', 'I' and 'F'.
 */
class Schema : public Object {
public:
    size_t numRows;
    size_t numCols;
    Array *rowNames; // owned
    Array *colNames; // owned
    ColTypeArray *colTypes; // owned; same size as numCols


    /** Copying constructor */
    /**
     * Creates this schema using another schema.
     *
     * @param from another schema being used for creating this schema
     */
    Schema(Schema &from) : Object() {
        this->numRows = from.numRows;
        this->numCols = from.numCols;
        this->rowNames = new Array();

        // copy row names
        for (size_t rowIndex = 0; rowIndex < this->numRows; rowIndex++) {
            this->rowNames->append(from.row_name(rowIndex));
        }

        // add col names
        this->colNames = new Array();
        for (size_t colIndex = 0; colIndex < this->numCols; colIndex++) {
            char buffer[50];
            sprintf(buffer, "%zu", colIndex);
            // this->colNames->append(from.col_name(colIndex));
            this->colNames->append(new String(buffer));
        }

        // copy col types
        this->colTypes = new ColTypeArray();
        for (size_t colTypeIndex = 0; colTypeIndex < this->numCols; colTypeIndex++) {
            this->colTypes->append(from.col_type(colTypeIndex));
        }
    }


    /** Create an empty schema **/
    Schema() : Object(){
        this->numRows = 0;
        this->numCols = 0;
        this->rowNames = new Array();
        this->colNames = new Array();
        this->colTypes = new ColTypeArray();
    }


    /** Create a schema from a string of types. A string that contains
      * characters other than those identifying the four type results in
      * undefined behavior. The argument is external, a nullptr is
      * undefined. **/
    Schema(const char *types) {
        assert(types != nullptr);
        this->numRows = 0;
        this->numCols = strlen(types);
        this->rowNames = new Array();
        this->colNames = new Array(this->numCols);
        this->colTypes = new ColTypeArray(this->numCols);

        // add ColTypes to this Schema
        for (size_t i = 0; i < this->numCols; i++) {
            // appending a character of the unknown type produces assertion error
            this->colTypes->append(types[i]);
        }

        // add col names
        this->colNames = new Array();
        for (size_t colIndex = 0; colIndex < this->numCols; colIndex++) {
            char buffer [50];
            sprintf(buffer, "%zu", colIndex);
            this->colNames->append(new String(buffer));
        }
    }


    /** Add a column of the given type and name (can be nullptr), name
     * is external.
     *
     * @param typ the type of the column
     * @param name the name of the given column
     */
    void add_column(char typ, String *name) {
        this->colNames->append(name);
        // appending the unknown type to types produces assertion error
        // may exit of 'typ' value is not one of the values defined in ColType enumerator
        this->colTypes->append(typ);
        this->numCols++;
    }


    /**
     * Adds a new ColType to this Column.
     *
     * @param type the type of the Column
     */
    void add_col_type(ColType type) {
        this->colTypes->append(type);
        this->numCols++;
    }


    /** Add a row with a name (possibly nullptr), name is external.
     *
     * @param name the name of the new row
     */
    void add_row(String *name) {
        this->rowNames->append(name);
        this->numRows++;
    }


    /** Return name of row at idx; nullptr indicates no name. An idx >= width
      * is undefined.
      *
      * @param idx the index of the row which name is being returned
      * @return the name of the row at the given index
      */
    String *row_name(size_t idx) {
        assert(idx < this->numRows);
        return dynamic_cast<String*>(this->rowNames->get(idx));
    }


    /** Return name of column at idx; nullptr indicates no name given.
      *  An idx >= width is undefined.
      *
      *  @param idx the index of the column which name is being returned
      *  @return the name of the column at the given index
      */
    String *col_name(size_t idx) {
        assert(idx < this->numCols);
        return dynamic_cast<String*>(this->colNames->get(idx));
    }


    /** Return type of column at idx. An idx >= width is undefined.
     *
     * @param the index of the column which type is being returned
     * @return the type of the column at the given index
     */
    char col_type(size_t idx) {
        assert(idx < this->numCols);
        return static_cast<char>(this->colTypes->get(idx));
    }


    /** Given a column name return its index, or -1.
     *
     * @param name the name of the column
     * @return the index of the column with the given name
     */
    int col_idx(const char *name) {
        // colNames is represented by Array (arrayList), which allows storing nullptrs
        String *temp = nullptr;
        int index = -1;
        if (name != nullptr) {
            String *temp = new String(name);
            index = this->colNames->index(temp);
            delete temp;
        } else {
            index = this->colNames->index(nullptr);
        }
        return index;
    }


    /** Given a row name return its index, or -1.
     *
     * @param name the name of the column which index is being returned
     * @return the index of the column
     */
    int row_idx(const char *name) {
        String *temp = nullptr;
        if (name != nullptr) {
            temp = new String(name);
        }
        // rowNames is represented by Array (arrayList) class, that allows storing nullptr
        int idx = this->rowNames->index(temp);
        if (temp != nullptr) {
            delete temp;
        }
        return idx;
    }


    /** The number of columns.
     *
     * @return the number of columns
     */
    size_t width() {
        return this->numCols;
    }


    /** The number of rows.
     *
     * @return the number of rows
     */
    size_t length() {
        return this->numRows;
    }


    bool equals(Object *o) {
        Schema* otherSchema = dynamic_cast<Schema*>(o);
        if (otherSchema == nullptr) {
            return false;
        }
        return this->numCols == otherSchema->numCols
            && this->numRows == otherSchema->numRows
            && this->colNames->equals(otherSchema->colNames)
            && this->rowNames->equals(otherSchema->rowNames)
            && this->colTypes->equals(otherSchema->colTypes);
    }


    size_t hash() {
        return this->numCols + this->numRows + this->colNames->hash()
            + this->rowNames->hash() + this->colTypes->hash();
    }


    /**
     * Destructor of this Schema.
     */
    ~Schema() {
        delete this->colNames;
        delete this->rowNames;
        delete this->colTypes;
    }
};
