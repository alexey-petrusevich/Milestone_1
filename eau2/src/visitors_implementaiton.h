#pragma once
#include "row.h"

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
    FillRowVisitor(Row* row) {
        assert(row != nullptr);
        this->row = row;
        this->colIndex = 0;
    }

    /**
     * Visits the IntColumn 
     * 
     * @param intColumn - the column of int to be visited
     */
    virtual void visitIntColumn(IntColumn* intColumn) {
        assert(intColumn != nullptr);
        intColumn->set_int(colIndex, row->get_int(colIndex));
        colIndex++;
    }

    /**
     * Visits the DoubleColumn 
     * 
     * @param doubleColumn - the column of double to be visited
     */
    virtual void visitDoubleColumn(DoubleColumn* doubleColumn) {
        assert(doubleColumn != nullptr);
        doubleColumn->set_double(colIndex, row->get_double(colIndex));
        colIndex++;
    }

    /**
     * Visits the BoolColumn 
     * 
     * @param boolColumn - the column of bool to be visited
     */
    virtual void visitBoolColumn(BoolColumn* booleanColumn) {
        assert(booleanColumn != nullptr);
        booleanColumn->set_bool(colIndex, row->get_bool(colIndex));
        colIndex++;
    }

    /**
     * Visits the StringColumn 
     * 
     * @param stringColumn - the column of string to be visited
     */
    virtual void visitStringColumn(StringColumn* stringColumn) {
        assert(stringColumn != nullptr);
        stringColumn->set_string(colIndex, row->get_string(colIndex));
        colIndex++;
    }
};

/**
 * @brief Represents a visitor that adds an extra entry to the given column.
 * @file visitors_implementation.h
 * @author Aliaksei Petrusevich <petrusevich.a@husky.neu.edu>
 * @author Megha Rao <rao.m@husky.neu.edu>
 * @date March 30, 2020
 */
class AddRowVisitor : public IVisitor {
   public:
    Row* row;
    int colIndex;  // int to comply with idx data type of IntCol set() method

    /**
     * Constructor of this AddRowVisitor that accepts a given Row with data.
     *
     * @param row the Row containing data to be used for setting to various
     * Columns
     */
    AddRowVisitor(Row* row) {
        assert(row != nullptr);
        this->row = row;
        this->colIndex = 0;
    }

     /**
     * Visits the IntColumn 
     * 
     * @param intColumn - the column of int to be visited
     */
    virtual void visitIntColumn(IntColumn* intColumn) {
        assert(intColumn != nullptr);
        intColumn->push_back(row->get_int(colIndex));
        colIndex++;
    }

     /**
     * Visits the DoubleColumn 
     * 
     * @param doubleColumn - the column of double to be visited
     */
    virtual void visitDoubleColumn(DoubleColumn* doubleColumn) {
        assert(doubleColumn != nullptr);
        doubleColumn->push_back(row->get_double(colIndex));
        colIndex++;
    }

    /**
     * Visits the BoolColumn 
     * 
     * @param boolColumn - the column of bool to be visited
     */
    virtual void visitBoolColumn(BoolColumn* booleanColumn) {
        assert(booleanColumn != nullptr);
        booleanColumn->push_back(row->get_bool(colIndex));
        colIndex++;
    }

    /**
     * Visits the StringColumn 
     * 
     * @param stringColumn - the column of string to be visited
     */
    virtual void visitStringColumn(StringColumn* stringColumn) {
        assert(stringColumn != nullptr);
        stringColumn->push_back(row->get_string(colIndex));
        colIndex++;
    }
};
