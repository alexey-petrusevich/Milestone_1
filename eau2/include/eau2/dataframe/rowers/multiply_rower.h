#pragma once
#include "rower.h"

/**
 * Represents a rower that adds multiplies the values in the given column.
 */
class MultiplyRower : public Rower {
   public:
    size_t product = 1;

    /**
     * A constructor that multiplies all the values in the given column
     *
     * @param colIndex the column index this Rower will be iterating through
     */
    MultiplyRower(size_t colIndex);

    // accept method for multiply rower
    virtual bool accept(Row &r);

    /**
     * Destructor of this MultiplyRower.
     */
    virtual ~MultiplyRower();
};
