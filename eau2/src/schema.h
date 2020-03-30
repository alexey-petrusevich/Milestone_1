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
        this->colTypes = new ColTypeArray(this->numCols);

        // add ColTypes to this Schema
        for (size_t i = 0; i < this->numCols; i++) {
            // appending a character of the unknown type produces assertion error
            this->colTypes->append(types[i]);
        }
    }


    /** Add a column of the given type and name (can be nullptr), name
     * is external.
     *
     * @param typ the type of the column
     * @param name the name of the given column
     */
    void add_column(char typ, String *name) {
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



    /** Return type of column at idx. An idx >= width is undefined.
     *
     * @param the index of the column which type is being returned
     * @return the type of the column at the given index
     */
    char col_type(size_t idx) {
        assert(idx < this->numCols);
        return static_cast<char>(this->colTypes->get(idx));
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
            && this->colTypes->equals(otherSchema->colTypes);
    }


    size_t hash() {
        return this->numCols + this->numRows + this->colTypes->hash();
    }


    /**
     * Destructor of this Schema.
     */
    ~Schema() {
        delete this->colTypes;
    }
};
