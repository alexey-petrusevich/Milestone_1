#pragma once
#include "rower.h"

/**
 * Represents a rower that adds all the values in the given column in parallel
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
    ParallelSumRower(size_t colIndex, size_t beginRowIndex);

    // accept method
    virtual bool accept(Row &r);

    // clone method
    Object *clone();

    // join and then delete
    virtual void join_delete(Rower *other);

    /**
     * Destructor of this SumRower.
     */
    virtual ~ParallelSumRower();
};