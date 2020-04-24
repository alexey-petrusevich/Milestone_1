#pragma once
#include "../columns/bool_column.h"
#include "../columns/double_column.h"
#include "../columns/int_column.h"
#include "../columns/string_column.h"
#include "rower.h"

/**
 * Represents a rower that multiples the values in the given column in parallel
 */
class ParallelMultiplyRower : public Rower {
   public:
    size_t product = 1;
    size_t beginRowIndex;

    /**
     * A constructor that multiplies all the values in the given column
     *
     * @param colIndex the column index this Rower will be iterating through
     */
    ParallelMultiplyRower(size_t colIndex, size_t beginRowIndex);

    // accept method
    virtual bool accept(Row &r);

    // clone method
    Object *clone();

    // join delete
    virtual void join_delete(Rower *other);

    /**
     * Destructor of this ParallelMultiplyRower.
     */
    virtual ~ParallelMultiplyRower();
};