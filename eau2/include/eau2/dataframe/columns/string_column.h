#pragma once
#include "../../collections/arrays/array.h"
#include "column.h"

/**
 * @brief Represents a Column that holds string pointers. The strings are
 * external.  Nullptr is a valid val.
 * @file columns.h
 * @author Aliaksei Petrusevich <petrusevich.a@husky.neu.edu>
 * @author Megha Rao <rao.m@husky.neu.edu>
 * @date March 30, 2020
 */
class StringColumn : public Column {
   public:
    Array* array;

    /**
     * Default constructor of this column that uses DEFAULT_COL_SIZE
     * as default size of the array.
     */
    StringColumn();

    /**
     * Constructor of this StringColumn that accepts a pointer to an array of
     * Strings, and the size of the array of Strings.
     * @param array the pointer to the array of Strings
     * @param size number of items in the array
     */
    StringColumn(String** array, size_t size);

    Object* clone();

    void set_string(size_t idx, String* val);

    String* get_string(size_t idx);

    void push_back(String* val);

    void push_nullptr();

    void push_back(char* c);

    char* get_char(size_t index);

    void acceptVisitor(IVisitor* visitor);

    void accept(Fielder* f);

    StringColumn* as_string();

    /**
     * Destructor of this StringColumn.
     */
    ~StringColumn();
};
