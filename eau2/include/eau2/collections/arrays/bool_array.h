#pragma once
#include "array.h"

/**
 * Represents an array of booleans. Does not allow null pointers.
 */
class BoolArray : public Object {
   public:
    bool* array;
    int elementsInserted;
    int capacity;
    int currentPosition;

    /**
     * Default constructor for the array.
     */
    BoolArray();

    /**
     * Array with custom capacity.
     *
     * @param size the capacity of the array
     */
    BoolArray(int size);

    /**
     * Appends the given element to the end of this array.
     *
     * @param input the element being appended to the end of this BoolArray.
     */
    void append(bool input);

    /**
     * Returns the element at the given index.
     *
     * @param index the index of the element in this BoolArray.
     * @return the element at the given index
     */
    bool get(int index);

    /**
     * Returns the size of this BoolArray.
     *
     * @return the size of this BoolArray
     */
    int size();

    /**
     * Returns the index of the first element with the given value. Returns
     * false if value is not found.
     *
     * @param input the value of the element being searched for
     * @return the index of the element in this BoolArray
     */
    int index(bool input);

    /**
     * Sets the value of the element at the given index with
     * the given value.
     *
     * @param index the index of the item being set
     * @param input new element being inserted at the given position
     * @return the element displaced by the given element
     */
    bool set(int index, bool input);

    /**
     * Method to check equality of two objects
     *
     * @param Object* - object to be compared for equality
     * @return bool - true or false
     */
    bool equals(Object* o);

    /**
     * Hash method
     */
    size_t hash();

    /**
     * Checks whether the given capacity is larger than the capacity
     * of this BoolArray. Increases the size if required capacity is larger
     * then the existing capacity.
     *
     * @param required the required capacity
     */
    void _ensure_size(int required);

    /**
     * The destructor of this BoolArray.
     */
    ~BoolArray();
};