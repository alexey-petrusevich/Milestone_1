#pragma once
#include "../columns/bool_column.h"
#include "../columns/double_column.h"
#include "../columns/int_column.h"
#include "../columns/string_column.h"

/**
 * @brief This file represents various implementations of IVisitor class.
 * Although it was originally placed here, due to circular dependency the
 * interface was moved to row.h and actual implementation was left here.
 * @file visitors_implementation.h
 * @author Aliaksei Petrusevich <petrusevich.a@husky.neu.edu>
 * @author Megha Rao <rao.m@husky.neu.edu>
 * @date March 30, 2020
 */

/**
 * Represents a visitor class that visits various implementations of Column
 * class.
 */
class IVisitor : public Object {
   public:
    /**
     * Visits the IntColumn.
     *
     * @param intColumn the given IntColumn
     */
    virtual void visitIntColumn(IntColumn* intColumn);

    /**
     * Visits the DoubleColumn.
     *
     * @param doubleColumn the given DoubleColumn
     */
    virtual void visitDoubleColumn(DoubleColumn* doubleColumn);

    /**
     * Visits the BooleanColumn.
     *
     * @param booleanColumn the given BooleanColumn
     */
    virtual void visitBoolColumn(BoolColumn* booleanColumn);

    /**
     * Visits the StringColumn.
     *
     * @param stringColumn the given StringColumn
     */
    virtual void visitStringColumn(StringColumn* stringColumn);
};
