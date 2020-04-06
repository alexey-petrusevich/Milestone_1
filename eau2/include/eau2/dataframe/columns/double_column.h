#pragma once
#include "../../collections/arrays/double_array.h"
#include "column.h"

class IVisitor;

/**
 * @brief Represents a Column that holds primitive double values, unwrapped.
 * @file columns.h
 * @author Aliaksei Petrusevich <petrusevich.a@husky.neu.edu>
 * @author Megha Rao <rao.m@husky.neu.edu>
 * @date March 30, 2020
 */
class DoubleColumn : public Column {
   public:
    DoubleArray* array;
    double null_double = 0.0;

    /**
     * Default constructor of this DoubleColumn.
     */
    DoubleColumn();

    /**
     * Constructor of this DoubleColumn that accepts a pointer to an array of
     * doubles, and the size of the array of doubles.
     * @param array the pointer to the array of doubles
     * @param size number of items in the array
     */
    DoubleColumn(double* array, size_t size);

    Object* clone();

    void set_double(size_t idx, double val);

    double get_double(size_t idx);

    void push_back(double val);

    void push_nullptr();

    void push_back(char* c);

    char* get_char(size_t index);

    void acceptVisitor(IVisitor* visitor);

    void accept(Fielder* f);

    DoubleColumn* as_double();

    /**
     * Destructor of this column.
     */
    ~DoubleColumn();
};
