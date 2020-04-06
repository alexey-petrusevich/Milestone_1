#pragma once
#include "array.h"

/**
 * Represents an array of Integers. Does not allow null pointers.
 */
class IntArray : public Object {
   public:
    int* array;
    int elementsInserted;
    int capacity;
    int currentPosition;

    /**
     * Default constructor for the array.
     */
    IntArray();

    /**
     * Array with custom capacity.
     *
     * @param size the capacity of the array
     */
    IntArray(int size);

    /**
     * Appends the given element to the end of this array.
     *
     * @param input the element being appended to the end of this IntArray.
     */
    void append(int& input);

    /**
     * Returns the element at the given index.
     *
     * @param index the index of the element in this IntArray.
     * @return the element at the given index
     */
    int get(int index);

    /**
     * Returns the size of this IntArray.
     *
     * @return the size of this IntArray
     */
    int size();

    /**
     * Returns the index of the first element with the given value. Returns
     * -1 if value is not found.
     *
     * @param input the value of the element being searched for
     * @return the index of the element in this IntArray
     */
    int index(int& input);

    /**
     * Sets the value of the element at the given index with
     * the given value.
     *
     * @param index the index of the item being set
     * @param input new element being inserted at the given position
     * @return the element displaced by the given element
     */
    int set(int index, int& input);

    /**
     * Method to check equality of two objects
     *
     * @param Object* - The object to be checked for equality against this array
     * Object
     * @return bool - True or false
     */
    bool equals(Object* o);

    /**
     * Hash method
     */
    size_t hash();

    /**
     * Checks whether the given capacity is larger than the capacity
     * of this IntArray. Increases the size if required capacity is larger
     * then the existing capacity.
     *
     * @param required the required capacity
     */
    void _ensure_size(int required);

    /**
     * The destructor of this IntArray.
     */
    ~IntArray();
};
