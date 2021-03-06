#include "../../include/eau2/application/application.h"

#include <iostream>
#include <cassert>

Application::Application(size_t nodeId) : Object() { this->nodeId = nodeId; }

size_t Application::this_node() { return this->nodeId; }

Application::~Application() {}

/**
 * Represents a demo application. Provided as example code in the assignment
 */
class Demo : public Application {
   public:
    Key main = Key("main", 0);
    Key verify = Key("verif", 0);
    Key check = Key("ck", 0);

    Demo(size_t idx) : Application(idx) {}

    void run_() override {
        switch (this_node()) {
            case 0:
                producer();
                break;
            case 1:
                counter();
                break;
            case 2:
                summarizer();
        }
    }

    void producer() {
        size_t SZ = 100 * 1000;
        double *vals = new double[SZ];
        double sum = 0;
        for (size_t i = 0; i < SZ; ++i) sum += vals[i] = i;
        DataFrame::fromArray(&main, &kv, SZ, vals);
        DataFrame::fromScalar(&check, &kv, sum);
    }

    void counter() {
        DataFrame *v = kv.wait_and_get(main);
        size_t sum = 0;
        for (size_t i = 0; i < 100 * 1000; ++i) sum += v->get_double(0, i);
        p("The sum is  ").pln(sum);
        DataFrame::fromScalar(&verify, &kv, static_cast<double>(sum));
    }

    void summarizer() {
        DataFrame *result = kv.wait_and_get(verify);
        DataFrame *expected = kv.wait_and_get(check);
        pln(expected->get_double(0, 0) == result->get_double(0, 0) ? "SUCCESS"
                                                                   : "FAILURE");
    }
};

/**
 * Represents a trivial application. Code given in assignment.
 */
class Trivial : public Application {
   public:
    // constructor
    Trivial(size_t idx) : Application(idx) {}

    void run_() {
        size_t SZ = 1000 * 1000;
        double *vals = new double[SZ];
        double sum = 0;
        for (size_t i = 0; i < SZ; ++i) sum += vals[i] = i;
        Key key("triv", 0);
        DataFrame *df = DataFrame::fromArray(&key, &kv, SZ, vals);
        assert(df->get_double(0, 1) == 1);
        DataFrame *df2 = kv.get(key);
        for (size_t i = 0; i < SZ; ++i) sum -= df2->get_double(0, i);
        assert(sum == 0);
        delete df;
        delete df2;
    }
};
