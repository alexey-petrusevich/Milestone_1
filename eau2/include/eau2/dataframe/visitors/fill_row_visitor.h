#pragma once
#include "visitor.h"
#include "../row.h"

/**
 * @brief Represents implementation of IVisitor that visits Columns and sets
 * them with values stored in the given Row.
 * @file visitors_implementation.h
 * @author Aliaksei Petrusevich <petrusevich.a@husky.neu.edu>
 * @author Megha Rao <rao.m@husky.neu.edu>
 * @date March 30, 2020
 */
class FillRowVisitor : public IVisitor {
   public:
    Row* row;
    int colIndex;  // int to comply with idx data type of IntCol set() method

    /**
     * Constructor of this FillRowVisitor that accepts a given Row with data.
     *
     * @param row the Row containing data to be used for setting to various
     * Columns
     */
    FillRowVisitor(Row* row);

    /**
     * Visits the IntColumn
     *
     * @param intColumn - the column of int to be visited
     */
    virtual void visitIntColumn(IntColumn* intColumn);

    /**
     * Visits the DoubleColumn
     *
     * @param doubleColumn - the column of double to be visited
     */
    virtual void visitDoubleColumn(DoubleColumn* doubleColumn);

    /**
     * Visits the BoolColumn
     *
     * @param boolColumn - the column of bool to be visited
     */
    virtual void visitBoolColumn(BoolColumn* booleanColumn);

    /**
     * Visits the StringColumn
     *
     * @param stringColumn - the column of string to be visited
     */
    virtual void visitStringColumn(StringColumn* stringColumn);
};