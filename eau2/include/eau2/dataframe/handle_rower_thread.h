#pragma once
#include "../utils/thread.h"
#include "rowers/rower.h"

/**
 * A thread that uses the given Rower and ColumnArray to partially iterate
 * through the ColumnArray.
 */
class HandleRowerThread : public Thread {
   public:
    size_t beginRowIndex;
    size_t endRowIndex;
    Rower *rower;
    ColumnArray *columnArray;

    /**
     * Constructor that accepts a ColumnArray, Rower, begin, and end indices
     * to partially iterate through the ColumnArray.
     *
     * @param columnArray
     */
    HandleRowerThread(ColumnArray *columnArray, Rower *rower,
                      size_t beginRowIndex, size_t endRowIndex);

    // calls the accept method after going through each row
    void run();
};
