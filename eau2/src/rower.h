#pragma once

#include "object.h"
#include "columns.h"
#include "array.h"
#include "row.h"
#include "thread.h"


/*******************************************************************************
 *  Rower::
 *  An interface for iterating through each row of a data frame. The intent
 *  is that this class should subclassed and the accept() method be given
 *  a meaningful implementation. Rowers can be cloned for parallel execution.
 */
class Rower : public Object {
public:
    size_t colIndex;


    /**
     * Constructor of this Rower that accepts the column index of the column this Rower
     * will iterate through.
     * 
     * @param colIndex the column index this Rower will be iterating through
     */
    Rower(size_t colIndex) {
        this->colIndex = colIndex;
    }


    /**
     * This method is called once per row. The row object is on loan and
     * should not be retained as it is likely going to be reused in the next
     * call. The return value is used in filters to indicate that a row
     * should be kept.
     * 
     * @param r the row to be accepted as the source of data
     */
    virtual bool accept(Row &r) = 0;


    /**
     * Once traversal of the data frame is complete the rowers that were
     * split off will be joined.  There will be one join per split. The
     * original object will be the last to be called join on. The join method
     * is reponsible for cleaning up memory.
     * 
     * @param rower the other Rower from the other thread
     */
    virtual void join_delete(Rower *other) {
        // empty to be used in the single threaded rower
    }
};


/**
 * Represents a rower that adds all the values in the given column.
 */
class SumRower : public Rower {
public:
    size_t sum = 0;

    /**
     * A constructor that sums all the values in the given column
     *
     * @param colIndex the column index this Rower will be iterating through
     */
    SumRower(size_t colIndex) : Rower(colIndex) {
    }


    virtual bool accept(Row &r) {
        assert(this->colIndex < r.width());
        size_t val = static_cast<size_t>(
            dynamic_cast<IntColumn*>(r.columnArray->get(this->colIndex))->get_int(r.rowIndex));
        sum += val;
        return false;
    }


    /**
     * Destructor of this SumRower.
     */
    virtual ~SumRower() {
    }
};


class MultiplyRower : public Rower {
public:
    size_t product = 1;

    /**
     * A constructor that multiplies all the values in the given column
     *
     * @param colIndex the column index this Rower will be iterating through
     */
    MultiplyRower(size_t colIndex) : Rower(colIndex) {
    }


    virtual bool accept(Row &r) {
        assert(this->colIndex < r.width());
        size_t val = static_cast<size_t>(
            dynamic_cast<IntColumn*>(r.columnArray->get(this->colIndex))->get_int(r.rowIndex));
        product *= val;
        return false;
    }


    /**
     * Destructor of this MultiplyRower.
     */
    virtual ~MultiplyRower() {
    }
};


class ParallelMultiplyRower : public Rower {
public:
    size_t product = 1;
    size_t beginRowIndex;

    /**
     * A constructor that multiplies all the values in the given column
     *
     * @param colIndex the column index this Rower will be iterating through
     */
    ParallelMultiplyRower(size_t colIndex, size_t beginRowIndex) : Rower(colIndex) {
        this->beginRowIndex = beginRowIndex;
    }


    virtual bool accept(Row &r) {
        size_t val = static_cast<size_t>(
            dynamic_cast<IntColumn*>(r.columnArray->get(this->colIndex))->get_int(r.rowIndex));
        product *= val;
        return false;
    }


    Object* clone() {
        return new ParallelMultiplyRower(this->colIndex, this->beginRowIndex);
    }


    virtual void join_delete(Rower *other) {
        ParallelMultiplyRower *multiplyRower = dynamic_cast<ParallelMultiplyRower*>(other);
        if (multiplyRower != nullptr) {
            // multiply to this product and delete given rower
            this->product *= multiplyRower->product;
            delete multiplyRower;
        }
    }


    /**
     * Destructor of this ParallelMultiplyRower.
     */
    virtual ~ParallelMultiplyRower() {
    }
};


/**
 * Represents a rower that adds all the values in the given column.
 */
class ParallelSumRower : public Rower {
public:
    size_t sum = 0;
    size_t beginRowIndex;

    /**
     * A constructor that sums all the values in the given column
     *
     * @param colIndex the column index this Rower will be iterating through
     */
    ParallelSumRower(size_t colIndex, size_t beginRowIndex) : Rower(colIndex) {
        this->beginRowIndex = beginRowIndex;
    }


    virtual bool accept(Row &r) {
        int val = dynamic_cast<IntColumn*>(r.columnArray->get(this->colIndex))->get_int(r.rowIndex);
        sum += val;
        return false;
    }


    Object* clone() {
        return new ParallelSumRower(this->colIndex, this->beginRowIndex);
    }


    virtual void join_delete(Rower *other) {
        ParallelSumRower *sumRower = dynamic_cast<ParallelSumRower*>(other);
        if (sumRower != nullptr) {
            // add to this sum and delete given rower this->sum += 
            size_t otherSum = sumRower->sum;
            this->sum += otherSum;
            delete sumRower;
        }
    }


    /**
     * Destructor of this SumRower.
     */
    virtual ~ParallelSumRower() {
    }
};


/**
 * A thread that uses the given Rower and ColumnArray to partially iterate
 * through the ColumnArray.
 */
class HandleRowerThread : public Thread {
public:
    size_t beginRowIndex;
    size_t endRowIndex;
    Rower* rower;
    ColumnArray* columnArray;


    /**
     * Constructor that accepts a ColumnArray, Rower, begin, and end indices
     * to partially iterate through the ColumnArray.
     * 
     * @param columnArray
     */
    HandleRowerThread(ColumnArray *columnArray, Rower *rower, 
        size_t beginRowIndex, size_t endRowIndex) : Thread() {
        assert(columnArray != nullptr);
        assert(rower != nullptr);
        assert(beginRowIndex <= endRowIndex);
        this->columnArray = columnArray;
        this->rower = rower;
        this->beginRowIndex = beginRowIndex;
        this->endRowIndex = endRowIndex;        
    }


    void run() {
        for (size_t rowIndex = this->beginRowIndex; rowIndex < this->endRowIndex; rowIndex++) {
            Row row = Row (this->columnArray, rowIndex);
            rower->accept(row);
        }
    }

};
