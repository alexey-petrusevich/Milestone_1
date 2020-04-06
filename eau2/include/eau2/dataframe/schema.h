#pragma once

#include "../collections/arrays/coltype_array.h"
#include "../utils/object.h"

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
    ColTypeArray *colTypes;  // owned; same size as numCols

    /** Copying constructor */
    /**
     * Creates this schema using another schema.
     *
     * @param from another schema being used for creating this schema
     */
    Schema(Schema &from);

    /** Create an empty schema **/
    Schema();

    /** Create a schema from a string of types. A string that contains
     * characters other than those identifying the four type results in
     * undefined behavior. The argument is external, a nullptr is
     * undefined. **/
    Schema(const char *types);

    /** Add a column of the given type.
     *
     * @param typ the type of the column as c-string
     */
    void add_column(char typ);

    /**
     * Adds a new ColType to this Column.
     *
     * @param type the type of the Column
     */
    void add_col_type(ColType type);

    /** Return type of column at idx. An idx >= width is undefined.
     *
     * @param the index of the column which type is being returned
     * @return the type of the column at the given index
     */
    char col_type(size_t idx);

    /** The number of columns.
     *
     * @return the number of columns
     */
    size_t width();

    /** The number of rows.
     *
     * @return the number of rows
     */
    size_t length();

    /**
     * Method that checks equality between two objects
     *
     * @param Object - object to be checked for equality
     * @return bool - true or false
     */
    bool equals(Object *o);

    // hash method
    size_t hash();

    /**
     * Destructor of this Schema.
     */
    ~Schema();
};
