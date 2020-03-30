#include "../src/application.h"

void FAIL() { exit(1); }
void OK(const char* m) {
    const char* filename = "[test_application.cpp]";
    printf("%s %s: [passed]\n", filename, m);
}
void t_true(bool p) {
    if (!p) FAIL();
}
void t_false(bool p) {
    if (p) FAIL();
}

void testDemoProducer() {
    Demo* demo = new Demo(0);
    demo->run_();
    DataFrame* df = demo->kv.get(demo->main);
    //DataFrame* df2 = demo->kv.get(demo->check);
    assert(df->columns->get(0)->size() == 100* 1000);
    
    delete demo;
}

void testDemoCounter() {

}

void testDemoSummarize() {

}

void testTrivial() {

}

int main() {
    

    return 0;
}