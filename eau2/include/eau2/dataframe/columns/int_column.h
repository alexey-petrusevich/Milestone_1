#pragma once
#include "../../collections/arrays/int_array.h"
#include "column.h"

class IVisitor;

/**
 * @brief Represents a Column that holds primitive int values, unwrapped.
 * @file columns.h
 * @author Aliaksei Petrusevich <petrusevich.a@husky.neu.edu>
 * @author Megha Rao <rao.m@husky.neu.edu>
 * @date March 30, 2020
 */
class IntColumn : public Column {
   public:
    IntArray* array;
    int null_int = 0;

    /**
     * Default constructor for this IntColumn.
     */
    IntColumn();

    /**
     * Constructor of this IntColumn that accepts a pointer to an array of
     * integers, and the size of the array of integers.
     * @param array the pointer to the array of integers
     * @param size number of items in the array
     */
    IntColumn(int* array, size_t size);

    Object* clone();

    void set_int(size_t index, int val);

    int get_int(size_t idx);

    void push_back(int val);

    void push_nullptr();

    void push_back(char* c);

    char* get_char(size_t index);

    void acceptVisitor(IVisitor* visitor);

    void accept(Fielder* f);

    /**
     * Destructor of IntColumn.
     */
    ~IntColumn();
};
