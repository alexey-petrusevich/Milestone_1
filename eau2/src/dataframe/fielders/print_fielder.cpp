#include "../../../include/eau2/dataframe/fielders/print_fielder.h"

#include <iostream>

PrintFielder::PrintFielder() : Fielder() {}

void PrintFielderaccept(int i) { printf("%d\n", i); }

void PrintFielder::accept(double d) { printf("%f\n", d); }

void PrintFielder::accept(bool b) {
    if (!b) {
        printf("false\n");
    } else {
        printf("true\n");
    }
}

void PrintFielder::accept(String *s) {
    if (s == nullptr) {
        printf("null\n");
    } else {
        printf("%s\n", s->cstr_);
    }
}

void PrintFielder::done() { printf("End of row\n"); }
