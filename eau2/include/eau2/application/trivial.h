#pragma once
#include "application.h"

/**
 * Represents a trivial application. Code given in assignment.
 */
class Trivial : public Application {
   public:
    // constructor
    Trivial(size_t idx);

    void run_();
};
