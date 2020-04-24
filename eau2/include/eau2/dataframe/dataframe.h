#pragma once

#include "../collections/arrays/column_array.h"
#include "columns/column.h"
#include "../kvstore/key.h"
#include "../kvstore/kvstore.h"
#include "../utils/object.h"
#include "../utils/string.h"
#include "row.h"
#include "rowers/rower.h"
#include "schema.h"

class KVStore;

/****************************************************************************
 * DataFrame::
 *
 * A DataFrame is table composed of columns of equal length. Each column
 * holds values of the same type (I, S, B, F). A dataframe has a schema that
 * describes it.
 */
class DataFrame : public Object {
   public:
    Schema* schema;        // owned
    ColumnArray* columns;  // owned

    /** Create a data frame with the same columns as the give df but no rows.
     *
     * @param df data frame which schema is being used for creating
     * this data frame
     */
    DataFrame(DataFrame& df);

    /** Create a data frame from a schema and columns. Results are undefined if
     * the columns do not match the schema.
     *
     * @param schema the schema being used for creating this dataframe
     */
    DataFrame(Schema& schema);

    /**
     * Method that creates a data frame from the given columnns.
     *
     * @param columnArray - the column array to be added to dataframe
     * @return DataFrame
     */
    static DataFrame* fromColumns(ColumnArray* columnArray);

    // prints this DataFrame to STDOUT as a table
    void print();

    /**
     * Make a int dataframe from a given array
     *
     * @param key - Key value
     * @param kv - KV Store
     * @param size - size of the array
     * @param vals - int vals of the array
     *
     * @return Dataframe
     */
    static DataFrame* fromArray(Key* key, KVStore* kv, size_t size, int* vals);

    /**
     * Make a double dataframe from a given array
     *
     * @param key - Key value
     * @param kv - KV Store
     * @param size - size of the array
     * @param vals - double vals of the array
     *
     * @return Dataframe
     */
    static DataFrame* fromArray(Key* key, KVStore* kv, size_t size,
                                double* vals);

    /**
     * Make a bool dataframe from a given array
     *
     * @param key - Key value
     * @param kv - KV Store
     * @param size - size of the array
     * @param vals - bool vals of the array
     *
     * @return Dataframe
     */
    static DataFrame* fromArray(Key* key, KVStore* kv, size_t size, bool* vals);

    /**
     * Make a string dataframe from a given array
     *
     * @param key - Key value
     * @param kv - KV Store
     * @param size - size of the array
     * @param vals - string vals of the array
     *
     * @return Dataframe
     */
    static DataFrame* fromArray(Key* key, KVStore* kv, size_t size,
                                String** vals);

    /**
     * Make a int dataframe from a given scalar
     *
     * @param key - Key value
     * @param kv - KV Store
     * @param value - int vals of the scalar
     *
     * @return Dataframe
     */
    static DataFrame* fromScalar(Key* key, KVStore* kv, int value);

    /**
     * Make a double dataframe from a given scalar
     *
     * @param key - Key value
     * @param kv - KV Store
     * @param value - double vals of the scalar
     *
     * @return Dataframe
     */
    static DataFrame* fromScalar(Key* key, KVStore* kv, double value);

    /**
     * Make a bool dataframe from a given scalar
     *
     * @param key - Key value
     * @param kv - KV Store
     * @param value - bool vals of the scalar
     *
     * @return Dataframe
     */
    static DataFrame* fromScalar(Key* key, KVStore* kv, bool value);

    /**
     * Make a string dataframe from a given scalar
     *
     * @param key - Key value
     * @param kv - KV Store
     * @param value - string vals of the scalar
     *
     * @return Dataframe
     */
    static DataFrame* fromScalar(Key* key, KVStore* kv, String* value);

    /**
     * Make a int dataframe from a single int value
     *
     * @param value - int val to be added to dataframe
     * @return Dataframe
     */
    static DataFrame* from_single_int(int value);

    /**
     * Make a double dataframe from a single int value
     *
     * @param value - double val to be added to dataframe
     * @return Dataframe
     */
    static DataFrame* from_single_double(double value);

    /**
     * Make a bool dataframe from a single int value
     *
     * @param value - bool val to be added to dataframe
     * @return Dataframe
     */
    static DataFrame* from_single_bool(bool value);

    /**
     * Make a string dataframe from a single int value
     *
     * @param value - string val to be added to dataframe
     * @return Dataframe
     */
    static DataFrame* from_single_string(String* value);

    /**
     * Make a int dataframe from an int array
     *
     * @param array - int array to be added to dataframe
     * @param size - size of array to be added to datafram
     * @return Dataframe
     */
    static DataFrame* from_int_array(int* array, size_t size);

    /**
     * Make a double dataframe from an int array
     *
     * @param array - double array to be added to dataframe
     * @param size - size of array to be added to datafram
     * @return Dataframe
     */
    static DataFrame* from_double_array(double* array, size_t size);

    /**
     * Make a bool dataframe from an int array
     *
     * @param array - bool array to be added to dataframe
     * @param size - size of array to be added to datafram
     * @return Dataframe
     */
    static DataFrame* from_bool_array(bool* array, size_t size);

    /**
     * Make a string dataframe from an int array
     *
     * @param array - string array to be added to dataframe
     * @param size - size of array to be added to datafram
     * @return Dataframe
     */
    static DataFrame* from_string_array(String** array, size_t size);

    /**
     * Make a dataframe from a bytes
     *
     * @param bytes - bytes to be added to dataframe
     * @return Dataframe
     */
    static DataFrame* fromBytes(byte* bytes);

    /**
     * Accepts a pointer to the object sored locally and a pointer to the
     * collection of remote object. Pointer to remote serialized object can be
     * nullptr. If that is the case, the serialized object is skipped. That is,
     * if out of 4 remote nodes, only 3 contain the data, only those 3 columns
     * will be added to the dataframe.
     *
     * @param local pointer to the local storage
     * @param remote pointer to the collection of remote bytes
     * @param num_nodes number of nodes in the network
     * @return the data from local and remote storages merged as a DataFrame
     */
    static DataFrame* merge(byte* local, byte** remote, size_t num_nodes);

    // initializes columns of this DataFrame
    void initColumns();

    /** Returns the data frame's schema. Modifying the schema after a data frame
     * has been created in undefined. */
    Schema& get_schema();

    /** Adds a column this data frame, updates the schema, the new column
     * is external, and appears as the last column of the data frame, the
     * name is optional and external. A nullptr column is undefined. */
    void add_column(Column* col);

    /** Return the value at the given column and row. Accessing rows or
     *  columns out of bounds, or request the wrong type is undefined.*/
    /**
     * Returns the integer value of the given column and row index.
     *
     * @param col the column index of the requested element
     * @param row the row index of the requested element
     * @return the integer value of the requested element
     */
    int get_int(size_t col, size_t row);

    /**
     * Returns the boolean value of the given column and row index.
     *
     * @param col the column index of the requested element
     * @param row the row index of the requested element
     * @return the boolean value of the requested element
     */
    bool get_bool(size_t col, size_t row);

    /**
     * Returns the double value of the given column and row index.
     *
     * @param col the column index of the requested element
     * @param row the row index of the requested element
     * @return the double value of the requested element
     */
    double get_double(size_t col, size_t row);

    /**
     * Returns the String value of the given column and row index.
     *
     * @param col the column index of the requested element
     * @param row the row index of the requested element
     * @return the String value of the requested element
     */
    String* get_string(size_t col, size_t row);

    /** Set the value at the given column and row to the given value.
     * If the column is not  of the right type or the indices are out of
     * bound, the result is undefined. */
    /**
     * Sets the value of the element at the given column and row index
     * with the given integer.
     *
     * @param col the column index of the element
     * @param row the row index of the element
     * @param val the integer value of the element
     */
    void set(size_t col, size_t row, int val);

    /**
     * Sets the value of the element at the given column and row index
     * with the given boolean.
     *
     * @param col the column index of the element
     * @param row the row index of the element
     * @param val the boolean value of the element
     */
    void set(size_t col, size_t row, bool val);

    /**
     * Sets the value of the element at the given column and row index
     * with the given double.
     *
     * @param col the column index of the element
     * @param row the row index of the element
     * @param val the double value of the element
     */
    void set(size_t col, size_t row, double val);

    /**
     * Sets the value of the element at the given column and row index
     * with the given String.
     *
     * @param col the column index of the element
     * @param row the row index of the element
     * @param val the String value of the element
     */
    void set(size_t col, size_t row, String* val);

    /** Set the fields of the given row object with values from the columns at
     * the given offset.  If the row is not form the same schema as the
     * data frame, results are undefined.
     *
     * @param idx the row index which values are being filled
     * @param the row that is being used as a source of values
     */
    void fill_row(size_t idx, Row& row);

    /** Add a row at the end of this data frame. The row is expected to have
     *  the right schema and be filled with values, otherwise undefined.
     *
     *  @param row the new row being added to this data frame
     */
    void add_row(Row& row);

    /** The number of rows in the data frame.
     *
     * @return the number of rows in this data frame
     */
    size_t nrows();

    /** The number of columns in the data frame.
     *
     * @return the number of columns in this data frame
     */
    size_t ncols();

    /** Visit rows in order. Cannot modify the structure of this DataFrame.
     *
     * @param r the rower used for iterating over rows of this data frame
     */
    void map(Rower& r);

    /**
     * Method that sums the Values in the given row
     *
     * @param sum - sum of ints
     * @param beginIndex - beginning index
     * @param endIndex - end index
     */
    void sumValues(int* sum, size_t beginIndex, size_t endIndex);

    /**
     * Uses map with multithreading. Sums the values of the given column.
     *
     * @param rower
     */
    void pmap(Rower& rower);

    /** Create a new dataframe, constructed from rows for which the given Rower
     * returned true from its accept method.
     *
     * @param r rowers used for iterating over rows of this data frame
     * @return the new dataframe created using the rower
     */
    DataFrame* filter(Rower& r);

    /**
     * Destructor of this DataFrame.
     */
    ~DataFrame();
};
