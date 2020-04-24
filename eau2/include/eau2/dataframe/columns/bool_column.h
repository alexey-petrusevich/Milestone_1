#pragma once
#include "../../collections/arrays/bool_array.h"
#include "column.h"

class IVisitor;

/**
 * @brief Represents a Column that holds primitive boolean values, unwrapped.
 * @file columns.h
 * @author Aliaksei Petrusevich <petrusevich.a@husky.neu.edu>
 * @author Megha Rao <rao.m@husky.neu.edu>
 * @date March 30, 2020
 */
class BoolColumn : public Column {
   public:
    BoolArray* array;
    bool null_bool = false;

    /**
     * Default constructor of this BoolColumn.
     */
    BoolColumn();

    /**
     * Constructor of this BoolColumn that accepts a pointer to an array of
     * booleans, and the size of the array of booleans.
     * @param array the pointer to the array of booleans
     * @param size number of items in the array
     */
    BoolColumn(bool* array, size_t size);

    Object* clone();

    void set_bool(size_t idx, bool val);

    bool get_bool(size_t idx);

    void push_back(bool val);

    void push_nullptr();

    void push_back(char* c);

    char* get_char(size_t index);

    void acceptVisitor(IVisitor* visitor);

    void accept(Fielder* f);

    BoolColumn* as_bool();

    /**
     * Destructor of this column.
     */
    ~BoolColumn();
};
