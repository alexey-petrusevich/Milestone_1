#pragma once
#include "fielder.h"

/**
 * A Fielder that prints every value of the given row.
 */
class PrintFielder : public Fielder {
   public:
    /**
     * Default constructor of this PrintFielder.
     */
    PrintFielder();

    // accept method for int
    void accept(int i);

    // accept method for double
    void accept(double d);

    // accept method for bool
    void accept(bool b);

    // accept method for string
    void accept(String *s);

    // method to show that all the values in the row have been looked at. prints
    void done();
};
