#pragma once

#include <cstdarg>
#include <iostream>

#include "array.h"
#include "coltypes.h"
#include "columns.h"
#include "deserializer.h"
#include "kvstore.h"
#include "object.h"
#include "rower.h"
#include "schema.h"
#include "serializer.h"
#include "string.h"
#include "thread.h"
#include "visitors_implementaiton.h"

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
    DataFrame(DataFrame& df) {
        this->schema = new Schema(*(df.schema));
        this->schema->numRows = 0;
        this->initColumns();
    }

    /** Create a data frame from a schema and columns. Results are undefined if
     * the columns do not match the schema.
     *
     * @param schema the schema being used for creating this dataframe
     */
    DataFrame(Schema& schema) {
        this->schema = new Schema(schema);
        this->schema->numRows = 0;
        this->initColumns();
    }

    static DataFrame* fromColumns(ColumnArray* columnArray) {
        Schema* schema = columnArray->getSchema();
        DataFrame* df = new DataFrame(*schema);
        for (int i = 0; i < columnArray->size(); i++) {
            Column* oldCol = columnArray->get(i);
            Column* col = dynamic_cast<Column*>(oldCol->clone());
            Column* removable = df->columns->set(i, col);
            if (col->numElements > df->schema->numRows) {
                df->schema->numRows = col->numElements;
            }
            delete removable;
        }
        delete schema;
        return df;
    }

    // prints this DataFrame to STDOUT as a table
    void print() {
        for (size_t rowIndex = 0; rowIndex < this->schema->numRows;
             rowIndex++) {
            for (size_t colIndex = 0; colIndex < this->schema->numCols;
                 colIndex++) {
                Column* col = this->columns->get(colIndex);
                switch (col->get_type()) {
                    case ColType::INTEGER:
                        printf("<%d> ", dynamic_cast<IntColumn*>(col)->get_int(
                                            rowIndex));
                        break;
                    case ColType::DOUBLE:
                        printf("<%.3f> ",
                               dynamic_cast<DoubleColumn*>(col)->get_double(
                                   rowIndex));
                        break;
                    case ColType::BOOLEAN:
                        printf(
                            "<%d> ",
                            dynamic_cast<BoolColumn*>(col)->get_bool(rowIndex)
                                ? 1
                                : 0);
                        break;
                    case ColType::STRING:
                        printf("<\"%s\"> ", dynamic_cast<StringColumn*>(col)
                                                ->get_string(rowIndex)
                                                ->cstr_);
                        break;
                    default:
                        break;
                }
            }
            printf("\n");
        }
    }

    static DataFrame* fromArray(Key* key, KVStore* kv, size_t size, int* vals) {
        byte* serialized = Serializer::serialize_int_array(vals, size);
        kv->put(key, serialized);
        IntColumn* col = new IntColumn(vals, size);
        ColumnArray* columnArray = new ColumnArray();
        columnArray->append(col);
        DataFrame* df = DataFrame::fromColumns(columnArray);
        return df;
    }

    static DataFrame* fromArray(Key* key, KVStore* kv, size_t size,
                                double* vals) {
        byte* serialized = Serializer::serialize_double_array(vals, size);
        kv->put(key, serialized);
        DoubleColumn* col = new DoubleColumn(vals, size);
        ColumnArray* columnArray = new ColumnArray();
        columnArray->append(col);
        DataFrame* df = DataFrame::fromColumns(columnArray);
        return df;
    }

    static DataFrame* fromArray(Key* key, KVStore* kv, size_t size,
                                bool* vals) {
        byte* serialized = Serializer::serialize_bool_array(vals, size);
        kv->put(key, serialized);
        BoolColumn* col = new BoolColumn(vals, size);
        ColumnArray* columnArray = new ColumnArray();
        columnArray->append(col);
        DataFrame* df = DataFrame::fromColumns(columnArray);
        return df;
    }

    static DataFrame* fromArray(Key* key, KVStore* kv, size_t size,
                                String** vals) {
        byte* serialized = Serializer::serialize_string_array(vals, size);
        kv->put(key, serialized);
        StringColumn* col = new StringColumn(vals, size);
        ColumnArray* columnArray = new ColumnArray();
        columnArray->append(col);
        DataFrame* df = DataFrame::fromColumns(columnArray);
        return df;
    }

    static DataFrame* fromScalar(Key* key, KVStore* kv, int value) {
        byte* serialized = Serializer::serialize_int(value);
        kv->put(key, serialized);
        IntColumn* col = new IntColumn();
        col->push_back(value);
        ColumnArray* columnArray = new ColumnArray();
        columnArray->append(col);
        DataFrame* df = DataFrame::fromColumns(columnArray);
        return df;
    }

    static DataFrame* fromScalar(Key* key, KVStore* kv, double value) {
        byte* serialized = Serializer::serialize_double(value);
        kv->put(key, serialized);
        DoubleColumn* col = new DoubleColumn();
        col->push_back(value);
        ColumnArray* columnArray = new ColumnArray();
        columnArray->append(col);
        DataFrame* df = DataFrame::fromColumns(columnArray);
        return df;
    }

    static DataFrame* fromScalar(Key* key, KVStore* kv, bool value) {
        byte* serialized = Serializer::serialize_bool(value);
        kv->put(key, serialized);
        BoolColumn* col = new BoolColumn();
        col->push_back(value);
        ColumnArray* columnArray = new ColumnArray();
        columnArray->append(col);
        DataFrame* df = DataFrame::fromColumns(columnArray);
        return df;
    }

    static DataFrame* fromScalar(Key* key, KVStore* kv, String* value) {
        byte* serialized = Serializer::serialize_string(value);
        kv->put(key, serialized);
        StringColumn* col = new StringColumn();
        col->push_back(value);
        ColumnArray* columnArray = new ColumnArray();
        columnArray->append(col);
        DataFrame* df = DataFrame::fromColumns(columnArray);
        return df;
    }

    static DataFrame* from_single_int(int value) {
        IntColumn* column = new IntColumn();
        column->push_back(value);
        ColumnArray* colArray = new ColumnArray();
        colArray->append(column);
        return DataFrame::fromColumns(colArray);
    }

    static DataFrame* from_single_double(double value) {
        DoubleColumn* column = new DoubleColumn();
        column->push_back(value);
        ColumnArray* colArray = new ColumnArray();
        colArray->append(column);
        return DataFrame::fromColumns(colArray);
    }

    static DataFrame* from_single_bool(bool value) {
        BoolColumn* column = new BoolColumn();
        column->push_back(value);
        ColumnArray* colArray = new ColumnArray();
        colArray->append(column);
        return DataFrame::fromColumns(colArray);
    }

    static DataFrame* from_single_string(String* value) {
        StringColumn* column = new StringColumn();
        column->push_back(value);
        ColumnArray* colArray = new ColumnArray();
        colArray->append(column);
        return DataFrame::fromColumns(colArray);
    }

    static DataFrame* from_int_array(int* array, size_t size) {
        IntColumn* column = new IntColumn(array, size);
        ColumnArray* colArray = new ColumnArray();
        colArray->append(column);
        return DataFrame::fromColumns(colArray);
    }

    static DataFrame* from_double_array(double* array, size_t size) {
        DoubleColumn* column = new DoubleColumn(array, size);
        ColumnArray* colArray = new ColumnArray();
        colArray->append(column);
        return DataFrame::fromColumns(colArray);
    }

    static DataFrame* from_bool_array(bool* array, size_t size) {
        BoolColumn* column = new BoolColumn(array, size);
        ColumnArray* colArray = new ColumnArray();
        colArray->append(column);
        return DataFrame::fromColumns(colArray);
    }

    static DataFrame* from_string_array(String** array, size_t size) {
        StringColumn* column = new StringColumn(array, size);
        ColumnArray* colArray = new ColumnArray();
        colArray->append(column);
        return DataFrame::fromColumns(colArray);
    }

    static DataFrame* fromBytes(byte* bytes) {
        Headers header;
        size_t size;
        memcpy(&header, bytes, sizeof(Headers));
        switch (header) {
            case Headers::INT: {
                int val = Deserializer::deserialize_int(bytes);
                return DataFrame::from_single_int(val);
            }

            case Headers::DOUBLE: {
                double val = Deserializer::deserialize_double(bytes);
                return DataFrame::from_single_double(val);
            }

            case Headers::BOOL: {
                bool val = Deserializer::deserialize_bool(bytes);
                return DataFrame::from_single_bool(val);
            }

            case Headers::STRING: {
                String* val = Deserializer::deserialize_string(bytes);
                return DataFrame::from_single_string(val);
            }

            case Headers::INT_ARRAY: {
                int* array = Deserializer::deserialize_int_array(bytes);
                size = Deserializer::array_size(bytes);
                return DataFrame::from_int_array(array, size);
            }

            case Headers::DOUBLE_ARRAY: {
                double* array = Deserializer::deserialize_double_array(bytes);
                size = Deserializer::array_size(bytes);
                return DataFrame::from_double_array(array, size);
            }

            case Headers::BOOL_ARRAY: {
                bool* array = Deserializer::deserialize_bool_array(bytes);
                size = Deserializer::array_size(bytes);
                return DataFrame::from_bool_array(array, size);
            }

            case Headers::STRING_ARRAY: {
                String** array = Deserializer::deserialize_string_array(bytes);
                size = Deserializer::array_size(bytes);
                return DataFrame::from_string_array(array, size);
            }

            default: {
                return nullptr;
            }
        }
    }

    /**
     * Accepts a pointer to the object sored locally and a pointer to the
     * collection of remote object. Pointer to remote serialized object can be
     * nullptr. If that is the case, the serialized object is skipped. That is, if out of 4 remote nodes, only 3 contain the data,
     * only those 3 columns will be added to the dataframe.
     * 
     * @param local pointer to the local storage
     * @param remote pointer to the collection of remote bytes
     * @param num_nodes number of nodes in the network
     * @return the data from local and remote storages merged as a DataFrame
     */
    static DataFrame* merge(byte* local, byte** remote, size_t num_nodes) {
        DataFrame* df = DataFrame::fromBytes(local);
        for (size_t index = 0; index < num_nodes; index++) {
            if (remote[index] == nullptr) {
                continue;
            }
            Column* col;
            Headers header = Deserializer::get_header(remote[index]);
            switch (header) {
                case Headers::INT: {
                    int value = Deserializer::deserialize_int(remote[index]);
                    col = new IntColumn();
                    col->push_back(value);
                    break;
                }
                case Headers::DOUBLE: {
                    double value =
                        Deserializer::deserialize_double(remote[index]);
                    col = new DoubleColumn();
                    col->push_back(value);
                    break;
                }
                case Headers::BOOL: {
                    bool value = Deserializer::deserialize_bool(remote[index]);
                    col = new BoolColumn();
                    col->push_back(value);
                    break;
                }
                case Headers::STRING: {
                    String* value =
                        Deserializer::deserialize_string(remote[index]);
                    col = new StringColumn();
                    col->push_back(value);
                    break;
                }
                case Headers::INT_ARRAY: {
                    int* array =
                        Deserializer::deserialize_int_array(remote[index]);
                    size_t size = Deserializer::num_bytes(remote[index]);
                    col = new IntColumn();
                    for (size_t i = 0; i < size; i++) {
                        col->push_back(array[i]);
                    }
                    break;
                }
                case Headers::DOUBLE_ARRAY: {
                    double* array =
                        Deserializer::deserialize_double_array(remote[index]);
                    size_t size = Deserializer::num_bytes(remote[index]);
                    col = new DoubleColumn();
                    for (size_t i = 0; i < size; i++) {
                        col->push_back(array[i]);
                    }
                    break;
                }
                case Headers::BOOL_ARRAY: {
                    bool* array =
                        Deserializer::deserialize_bool_array(remote[index]);
                    size_t size = Deserializer::num_bytes(remote[index]);
                    col = new BoolColumn();
                    for (size_t i = 0; i < size; i++) {
                        col->push_back(array[i]);
                    }
                    break;
                }
                case Headers::STRING_ARRAY: {
                    String** array =
                        Deserializer::deserialize_string_array(remote[index]);
                    size_t size = Deserializer::num_bytes(remote[index]);
                    col = new StringColumn();
                    for (size_t i = 0; i < size; i++) {
                        col->push_back(array[i]);
                    }
                    break;
                }
                default:
                    col = nullptr;
                    break;
            }

            df->add_column(col);
        }
        return df;
    }

    // initializes columns of this DataFrame
    void initColumns() {
        this->columns = new ColumnArray(this->schema->numCols);
        for (size_t colIndex = 0; colIndex < this->schema->numCols;
             colIndex++) {
            switch (static_cast<ColType>(this->schema->col_type(colIndex))) {
                case ColType::INTEGER:
                    this->columns->append(new IntColumn());
                    break;
                case ColType::DOUBLE:
                    this->columns->append(new DoubleColumn());
                    break;
                case ColType::BOOLEAN:
                    this->columns->append(new BoolColumn());
                    break;
                case ColType::STRING:
                    this->columns->append(new StringColumn());
                    break;
                default:
                    assert(false);
            }
        }
    }

    /** Returns the data frame's schema. Modifying the schema after a data frame
     * has been created in undefined. */
    Schema& get_schema() { return *(this->schema); }

    /** Adds a column this data frame, updates the schema, the new column
     * is external, and appears as the last column of the data frame, the
     * name is optional and external. A nullptr column is undefined. */
    void add_column(Column* col) {
        assert(col != nullptr);
        // append new column to the array of columns
        this->columns->append(col);
        // update schema
        this->schema->add_column(static_cast<char>(col->get_type()));
    }

    /** Return the value at the given column and row. Accessing rows or
     *  columns out of bounds, or request the wrong type is undefined.*/
    /**
     * Returns the integer value of the given column and row index.
     *
     * @param col the column index of the requested element
     * @param row the row index of the requested element
     * @return the integer value of the requested element
     */
    int get_int(size_t col, size_t row) {
        assert(col < this->schema->numCols);
        assert(row < this->schema->numRows);
        assert(static_cast<ColType>(this->schema->col_type(col)) ==
               ColType::INTEGER);
        IntColumn* intColumn = this->columns->get(col)->as_int();
        return intColumn->get_int(row);
    }

    /**
     * Returns the boolean value of the given column and row index.
     *
     * @param col the column index of the requested element
     * @param row the row index of the requested element
     * @return the boolean value of the requested element
     */
    bool get_bool(size_t col, size_t row) {
        assert(col < this->schema->numCols);
        assert(row < this->schema->numRows);
        assert(static_cast<ColType>(this->schema->col_type(col)) ==
               ColType::BOOLEAN);
        BoolColumn* boolColumn = this->columns->get(col)->as_bool();
        return boolColumn->get_bool(row);
    }

    /**
     * Returns the double value of the given column and row index.
     *
     * @param col the column index of the requested element
     * @param row the row index of the requested element
     * @return the double value of the requested element
     */
    double get_double(size_t col, size_t row) {
        assert(col < this->schema->numCols);
        assert(row < this->schema->numRows);
        assert(static_cast<ColType>(this->schema->col_type(col)) ==
               ColType::DOUBLE);
        DoubleColumn* doubleColumn = this->columns->get(col)->as_double();
        return doubleColumn->get_double(row);
    }

    /**
     * Returns the String value of the given column and row index.
     *
     * @param col the column index of the requested element
     * @param row the row index of the requested element
     * @return the String value of the requested element
     */
    String* get_string(size_t col, size_t row) {
        assert(col < this->schema->numCols);
        assert(row < this->schema->numRows);
        assert(this->schema->col_type(col) == STRING);
        StringColumn* stringColumn = this->columns->get(col)->as_string();
        return stringColumn->get_string(row);
    }

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
    void set(size_t col, size_t row, int val) {
        assert(col < this->schema->numCols);
        assert(row < this->schema->numRows);
        assert(static_cast<ColType>(this->schema->col_type(col)) ==
               ColType::INTEGER);
        IntColumn* intColumn = this->columns->get(col)->as_int();
        intColumn->set_int(row, val);
    }

    /**
     * Sets the value of the element at the given column and row index
     * with the given boolean.
     *
     * @param col the column index of the element
     * @param row the row index of the element
     * @param val the boolean value of the element
     */
    void set(size_t col, size_t row, bool val) {
        assert(col < this->schema->numCols);
        assert(row < this->schema->numRows);
        assert(static_cast<ColType>(this->schema->col_type(col)) ==
               ColType::BOOLEAN);
        BoolColumn* boolColumn = this->columns->get(col)->as_bool();
        boolColumn->set_bool(row, val);
    }

    /**
     * Sets the value of the element at the given column and row index
     * with the given double.
     *
     * @param col the column index of the element
     * @param row the row index of the element
     * @param val the double value of the element
     */
    void set(size_t col, size_t row, double val) {
        assert(col < this->schema->numCols);
        assert(row < this->schema->numRows);
        assert(static_cast<ColType>(this->schema->col_type(col)) ==
               ColType::DOUBLE);
        DoubleColumn* doubleColumn = this->columns->get(col)->as_double();
        doubleColumn->set_double(row, val);
    }

    /**
     * Sets the value of the element at the given column and row index
     * with the given String.
     *
     * @param col the column index of the element
     * @param row the row index of the element
     * @param val the String value of the element
     */
    void set(size_t col, size_t row, String* val) {
        assert(col < this->schema->numCols);
        assert(row < this->schema->numRows);
        assert(static_cast<ColType>(this->schema->col_type(col)) ==
               ColType::STRING);
        StringColumn* stringColumn = this->columns->get(col)->as_string();
        stringColumn->set_string(row, val);
    }

    /** Set the fields of the given row object with values from the columns at
     * the given offset.  If the row is not form the same schema as the
     * data frame, results are undefined.
     *
     * @param idx the row index which values are being filled
     * @param the row that is being used as a source of values
     */
    void fill_row(size_t idx, Row& row) {
        assert(idx < this->schema->numRows);
        assert(row.schema->equals(this->schema));

        // new visitor that takes the pointer of the given Row and sets this row
        // at the given index
        IVisitor* visitor = new FillRowVisitor(&row);

        for (int colIndex = 0; colIndex < this->columns->size(); colIndex++) {
            // have visitor visit every column and set its values with the
            // values of the given row
            this->columns->get(colIndex)->acceptVisitor(visitor);
        }
        delete visitor;
    }

    /** Add a row at the end of this data frame. The row is expected to have
     *  the right schema and be filled with values, otherwise undefined.
     *
     *  @param row the new row being added to this data frame
     */
    void add_row(Row& row) {
        assert(this->schema->equals(row.schema));

        // visitor that appends values from the row to the end of every column
        // in this DataFrame
        IVisitor* visitor = new AddRowVisitor(&row);

        for (int colIndex = 0; colIndex < this->columns->size(); colIndex++) {
            // visit every row and append new value
            this->columns->get(colIndex)->acceptVisitor(visitor);
        }
        delete visitor;

        // update schema
        this->schema->numRows++;
        row.schema->numRows++;
        row.rowIndex++;
    }

    /** The number of rows in the data frame.
     *
     * @return the number of rows in this data frame
     */
    size_t nrows() { return this->schema->numRows; }

    /** The number of columns in the data frame.
     *
     * @return the number of columns in this data frame
     */
    size_t ncols() { return this->schema->numCols; }

    /** Visit rows in order. Cannot modify the structure of this DataFrame.
     *
     * @param r the rower used for iterating over rows of this data frame
     */
    void map(Rower& r) {
        for (size_t rowIndex = 0; rowIndex < this->schema->numRows;
             rowIndex++) {
            Row row = Row(this->columns, rowIndex);
            r.accept(row);
        }
    }

    void sumValues(int* sum, size_t beginIndex, size_t endIndex) {
        for (size_t rowIndex = beginIndex; rowIndex < endIndex; rowIndex++) {
            *sum += ((IntColumn*)this->columns->get(0))->get_int(0);
        }
    }

    /**
     * Uses map with multithreading. Sums the values of the given column.
     *
     * @param rower
     */
    void pmap(Rower& rower) {
        // create threads
        size_t numThreads = 4;
        Thread** threads = new Thread*[numThreads];
        Rower** rowerClones = new Rower*[numThreads];

        for (size_t i = 0; i < numThreads; i++) {
            rowerClones[i] = dynamic_cast<Rower*>(rower.clone());
        }

        // 0. initialize threads
        for (size_t i = 0; i < numThreads; i++) {
            int beginRowIndex = i * this->schema->numRows / numThreads;
            int endRowIndex = (i + 1) * this->schema->numRows / numThreads;
            threads[i] = new HandleRowerThread(this->columns, rowerClones[i],
                                               beginRowIndex, endRowIndex);

            /*
            if (i == 0) {
                    threads[i] = new HandleRowerThread(this->columns,
            rowerClones[i], i * this->schema->numRows / numThreads, (i + 1) *
            this->schema->numRows / numThreads); } else { threads[i] = new
            HandleRowerThread(this->columns, rowerClones[i], i *
            this->schema->numRows / numThreads + 1, (i + 1) *
            this->schema->numRows / numThreads);
            }
            */
        }

        // 1. start threads
        for (size_t i = 0; i < numThreads; i++) {
            threads[i]->start();
        }

        // 2. join threads (wait until all threads are finished)
        for (size_t i = 0; i < numThreads; i++) {
            threads[i]->join();
        }

        // 3. join results
        for (size_t i = 0; i < numThreads - 1; i++) {
            rowerClones[0]->join_delete(rowerClones[i + 1]);
        }

        // 4. join results of the clone threads with the main rower
        rower.join_delete(rowerClones[0]);

        // 5. delete memory of threads
        delete[] threads;
    }

    /** Create a new dataframe, constructed from rows for which the given Rower
     * returned true from its accept method.
     *
     * @param r rowers used for iterating over rows of this data frame
     * @return the new dataframe created using the rower
     */
    DataFrame* filter(Rower& r) {
        // create new data frame
        DataFrame* newDataFrame = new DataFrame(*this);

        // traverse through each row and if given Rower returns true,
        // add it to the new DataFrame.
        // The true/false value is determined by implementation of
        // the specific rower.
        for (size_t rowIndex = 0; this->schema->numRows; rowIndex++) {
            Row row = Row(this->columns, rowIndex);
            if (r.accept(row)) {
                newDataFrame->add_row(row);
            }
        }

        return newDataFrame;
    }

    /**
     * Destructor of this DataFrame.
     */
    ~DataFrame() {
        delete this->schema;
        delete this->columns;
    }
};
