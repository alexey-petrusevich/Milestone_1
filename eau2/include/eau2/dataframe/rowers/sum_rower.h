#pragma once
#include "rower.h"

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
    SumRower(size_t colIndex);

    // accept method for sum rower
    virtual bool accept(Row &r);

    /**
     * Destructor of this SumRower.
     */
    virtual ~SumRower();
};