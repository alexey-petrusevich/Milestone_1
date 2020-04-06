#pragma once
#include "array.h"

/**
 * Represents an array of doubles. Does not allow null pointers.
 */
class DoubleArray : public Object {
   public:
    double* array;
    int elementsInserted;
    int capacity;
    int currentPosition;

    /**
     * Default constructor for the array.
     */
    DoubleArray();

    /**
     * Array with custom capacity.
     *
     * @param size the capacity of the array
     */
    DoubleArray(int size);

    /**
     * Appends the given element to the end of this array.
     *
     * @param input the element being appended to the end of this DoubleArray.
     */
    void append(double input);

    /**
     * Returns the element at the given index.
     *
     * @param index the index of the element in this DoubleArray.
     * @return the element at the given index
     */
    double get(int index);

    /**
     * Returns the size of this DoubleArray.
     *
     * @return the size of this DoubleArray
     */
    int size();

    /**
     * Returns the index of the first element with the given value. Returns
     * -1 if value is not found.
     *
     * @param input the value of the element being searched for
     * @return the index of the element in this DoubleArray
     */
    int index(double input);

    /**
     * Sets the value of the element at the given index with
     * the given value.
     *
     * @param index the index of the item being set
     * @param input new element being inserted at the given position
     * @return the element displaced by the given element
     */
    double set(int index, double input);

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
     * of this DoubleArray. Increases the size if required capacity is larger
     * then the existing capacity.
     *
     * @param required the required capacity
     */
    void _ensure_size(int required);

    /**
     * The destructor of this DoubleArray.
     */
    ~DoubleArray();
};