#pragma once

#include "../../utils/object.h"
#include "../../utils/string.h"

/**
 * @brief This file represent implementation of Fielder class and its
 * derivatives.
 * @file fielder.h
 * @author Aliaksei Petrusevich <petrusevich.a@husky.neu.edu>
 * @author Megha Rao <rao.m@husky.neu.edu>
 * @date February 15, 2020
 */

/*****************************************************************************
 * Fielder::
 * A field visitor invoked by Row.
 */
class Fielder : public Object {
   public:
    size_t rowIndex;

    /**
     * Default constructor of this Fielder.
     */
    Fielder();

    /** Called before visiting a row, the argument is the row offset in the data
     * frame. */
    /**
     * Sets the start index of the row being iterated through.
     *
     * @param r the index of the row being iterated through
     */
    virtual void start(size_t r);

    /** Called for fields of the argument's type with the value of the field. */
    /**
     * Accepts a boolean value and performs an action defined by
     * the specific implementation of the class extended from this Fielder.
     *
     * @param b boolean being used for the action
     */
    virtual void accept(bool b);

    /**
     * Accepts a double value and performs an action defined by
     * the specific implementation of the class extended from this Fielder.
     *
     * @param d double being used for the action
     */
    virtual void accept(double d);

    /**
     * Accepts an integer value and performs an action defined by
     * the specific implementation of the class extended from this Fielder.
     *
     * @param i integer being used for the action
     */
    virtual void accept(int i);

    /**
     * Accepts a String value and performs an action defined by
     * the specific implementation of the class extended from this Fielder.
     *
     * @param b String being used for the action
     */
    virtual void accept(String *s);

    /** Called when all fields have been seen.
     * Every class extending the rower must define its specific behavior.
     * */
    virtual void done() = 0;

    /**
     * Destructor of this Fielder.
     */
    virtual ~Fielder();
};
