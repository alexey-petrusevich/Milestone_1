#pragma once
#include "array.h"
#include "../../dataframe/columns/column.h"
#include "../../dataframe/schema.h"

/**
 * @brief Represents an array of Column.
 * @file columns.h
 * @author Aliaksei Petrusevich <petrusevich.a@husky.neu.edu>
 * @author Megha Rao <rao.m@husky.neu.edu>
 * @date March 30, 2020
 */
class ColumnArray : public Object {
   public:
    Column** array;
    int elementsInserted;
    int capacity;
    int currentPosition;

    /**
     * Default constructor for the array.
     */
    ColumnArray();

    /**
     * Array with custom capacity.
     *
     * @param size the capacity of the array
     */
    ColumnArray(int size);

    /**
     * Appends the given element to the end of this array.
     *
     * @param input the element being appended to the end of this ColumnArray.
     */
    void append(Column* input);

    /**
     * Returns the element at the given index.
     *
     * @param index the index of the element in this ColumnArray.
     * @return the element at the given index
     */
    Column* get(int index);

    /**
     * Returns the size of this ColumnArray.
     *
     * @return the size of this ColumnArray
     */
    int size();

    /**
     * Returns the index of the first element with the given value. Returns
     * -1 if value is not found.
     *
     * @param input the value of the element being searched for
     * @return the index of the element in this ColumnArray
     */
    int index(Column* input);

    /**
     * Sets the value of the element at the given index with
     * the given value.
     *
     * @param index the index of the item being set
     * @param input new element being inserted at the given position
     * @return the element displaced by the given element
     */
    Column* set(int index, Column* input);

    /**
     * Checks quality of two objects
     *
     * @param Object* - object to be checked for equality
     * @return bool - true or false
     */
    bool equals(Object* o);

    // hash method
    size_t hash();

    /**
     * Checks whether the given capacity is larger than the capacity
     * of this ColumnArray. Increases the size if required capacity is larger
     * then the existing capacity.
     *
     * @param required the required capacity
     */
    void _ensure_size(int required);

    /**
     * Returns a Schema of this ColumnArray.
     *
     * @return the Schema of this ColumnArray
     */
    Schema* getSchema();

    /**
     * The destructor of this Column array.
     */
    ~ColumnArray();
};
