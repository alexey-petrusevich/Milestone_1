#pragma once

#include <cstdarg>

#include "../coltypes.h"
#include "../fielders/fielder.h"
#include "../utils/object.h"
#include "../utils/string.h"
#include "../visitors/visitor.h"
#include "bool_column.h"
#include "double_column.h"
#include "int_column.h"
#include "string_column.h"

/**
 * @brief This file represent implementation of Column class and its
 * derivatives.
 * @file columns.h
 * @author Aliaksei Petrusevich <petrusevich.a@husky.neu.edu>
 * @author Megha Rao <rao.m@husky.neu.edu>
 * @date February 15, 2020
 */

/**
 * Represents one column of a data frame which holds values of a single
 * type. This abstract class defines methods overriden in subclasses. There is
 * one subclass per element type. Columns are mutable, equality is pointer
 * equality.
 */
class Column : public Object {
   public:
    size_t numElements;
    ColType colType;

    /**
     * Default constructor of the column.
     */
    Column(ColType colType);

    /** Type converters: Return the same column under its actual type, or
     *  nullptr if of the wrong type.  */
    /**
     * Returns this column as IntColumn.
     *
     * @return this column as IntColumn
     */
    virtual IntColumn* as_int();

    /**
     * Returns this column as DoubleColumn.
     *
     * @return this column as DoubleColumn
     */
    virtual DoubleColumn* as_double();

    /**
     * Returns this column as BoolColumn.
     *
     * @return this column as BoolColumn
     */
    virtual BoolColumn* as_bool();

    /**
     * Returns this column as StringColumn.
     *
     * @return this column as StringColumn
     */
    virtual StringColumn* as_string();

    /** Type appropriate push_back methods. Calling the wrong method is
     * undefined behavior. **/
    /**
     * Pushes the given integer value to the bottom of this column.
     *
     * @param val the integer value being pushed to the bottom of this column
     */
    virtual void push_back(int val);

    /**
     * Pushes the given double value to the bottom of this column.
     *
     * @param val the double value being pushed to the bottom of this column
     */
    virtual void push_back(double val);

    /**
     * Pushes the given boolean value to the bottom of this column.
     *
     * @param val the boolean value being pushed to the bottom of this column
     */
    virtual void push_back(bool val);

    /**
     * Pushes the given String value to the bottom of this column.
     *
     * @param val the String value being pushed to the bottom of this column
     */
    virtual void push_back(String* val);

    /**
     * Pushes a value represented by the sequence of characters to this Column.
     * @param val the c-string representation of the value being pushed to the
     * bottom of this column
     */
    virtual void push_back(char* val);

    /**
     * Pushes the null character to the bottom of this column. The null value
     * depends on the type of column.
     */
    virtual void push_nullptr();

    /** Returns the number of elements in the column.
     * @return the number of elements in this column
     */
    virtual size_t size();

    /**
     * Sets the value of this column with the given integer. If the column is
     * not IntColumn, throws assertion error.
     * @param index the column index
     * @param value the value of the integer being set
     */
    virtual void set_int(size_t index, int value);

    /**
     * Sets the value of this column with the given double. If the column is
     * not DoubleColumn, throws assertion error.
     * @param index the column index
     * @param value the value of the double being set
     */
    virtual void set_double(size_t index, double value);

    /**
     * Sets the value of this column with the given boolean. If the column is
     * not BoolColumn, throws assertion error.
     * @param index the column index
     * @param value the value of the boolean being set
     */
    virtual void set_bool(size_t index, bool value);

    /**
     * Sets the value of this column with the given String. If the column is
     * not StringColumn, throws assertion error.
     * @param index the column index
     * @param value the value of the String being set
     */
    virtual void set_string(size_t index, String* value);

    /**
     * Returns the integer value at the given index. If the column is not of
     * IntColumn type, throws assertion error.
     * @param index the index of the requested integer
     * @return the integer value at the given index
     */
    virtual int get_int(size_t index);

    /**
     * Returns the double value at the given index. If the column is not of
     * DoubleColumn type, throws assertion error.
     * @param index the index of the requested double
     * @return the double value at the given index
     */
    virtual double get_double(size_t index);

    /**
     * Returns the boolean value at the given index. If the column is not of
     * BoolColumn type, throws assertion error.
     * @param index the index of the requested boolean
     * @return the boolean value at the given index
     */
    virtual bool get_bool(size_t index);

    /**
     * Returns the String value at the given index. If the column is not of
     * StringColumn type, throws assertion error.
     * @param index the index of the requested String
     * @return the String value at the given index
     */
    virtual String* get_string(size_t index);

    /**
     * Returns true if the given sequence of characters can be added to this
     * column.
     * @param c the sequence of characters as value of sorer type
     * @return true of the given c-string can be added to this column and false
     * otherwise
     */
    virtual bool can_add(char* c);

    /**
     * Return the type of this column as a char: 'S', 'B', 'I' and 'F'.
     *
     * @return the type of this column
     */
    char get_type_char();

    /**
     * Return the type of this column as a one of ColType enum values.
     *
     * @return the type of this column as ColType
     */
    ColType get_type();

    /**
     * Accepts a visitor and call the corresponding accept
     * method based on the type of the column.
     *
     * @param f fielder being used for traversal
     */
    virtual void acceptVisitor(IVisitor* visitor) = 0;

    /**
     * Accepts a Fielder and calls 'accept' method of the corresponding
     * column.
     *
     * @param f the given Fielder
     */
    virtual void accept(Fielder* f) = 0;

    /**
     * Returns the object at the given index as c-string. Returns the string
     representation of the object at the ith index
     * Returns the string representation of the object at the ith index

     * @param i index of the object being requested as c-string
     * @return the c-string representation of the object at the given index
     */
    virtual char* get_char(size_t i);

    /**
     * clone method
     */
    virtual Object* clone() = 0;

    /**
     * Destructor of this column.
     */
    virtual ~Column();
};
