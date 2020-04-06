#pragma once

#include "../../utils/object.h"
#include "../row.h"

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
     * Constructor of this Rower that accepts the column index of the column
     * this Rower will iterate through.
     *
     * @param colIndex the column index this Rower will be iterating through
     */
    Rower(size_t colIndex);

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
    virtual void join_delete(Rower *other);
};
