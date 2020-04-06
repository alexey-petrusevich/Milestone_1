#pragma once
#include "application.h"

/**
 * Represents a demo application. Provided as example code in the assignment
 */
class Demo : public Application {
   public:
    Key main = Key("main", 0);
    Key verify = Key("verif", 0);
    Key check = Key("ck", 0);

    Demo(size_t idx);

    void run_() override;

    void producer();

    void counter();

    void summarizer();
};