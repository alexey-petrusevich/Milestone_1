#include "../../include/eau2/application/demo.h"

Demo::Demo(size_t idx) : Application(idx) {}

void Demo::run_() {
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

void Demo::producer() {
    size_t SZ = 100 * 1000;
    double *vals = new double[SZ];
    double sum = 0;
    for (size_t i = 0; i < SZ; ++i) sum += vals[i] = i;
    DataFrame::fromArray(&main, &kv, SZ, vals);
    DataFrame::fromScalar(&check, &kv, sum);
}

void Demo::counter() {
    DataFrame *v = kv.wait_and_get(main);
    size_t sum = 0;
    for (size_t i = 0; i < 100 * 1000; ++i) sum += v->get_double(0, i);
    p("The sum is  ").pln(sum);
    DataFrame::fromScalar(&verify, &kv, static_cast<double>(sum));
}

void Demo::summarizer() {
    DataFrame *result = kv.wait_and_get(verify);
    DataFrame *expected = kv.wait_and_get(check);
    pln(expected->get_double(0, 0) == result->get_double(0, 0) ? "SUCCESS"
                                                               : "FAILURE");
}
