#pragma once

//#pragma warning(disable : 4996)

typedef unsigned char byte;

/** Helper class providing some C++ functionality and convenience
 *  functions. This class has no data, constructors, destructors or
 *  virtual functions. Inheriting from it is zero cost.
 */
class Sys {
   public:
    // Printing functions
    Sys& p(char* c);
    Sys& p(bool c);
    Sys& p(float c);
    Sys& p(int i);
    Sys& p(size_t i);
    Sys& p(const char* c);
    Sys& p(char c);
    Sys& pln();
    Sys& pln(int i);
    Sys& pln(char* c);
    Sys& pln(bool c);
    Sys& pln(char c);
    Sys& pln(float x);
    Sys& pln(size_t x);
    Sys& pln(const char* c);

    // Copying strings
    char* duplicate(const char* s);
    char* duplicate(char* s);

    // Function to terminate execution with a message
    void exit_if_not(bool b, char* c);

    // Definitely fail
    //  void FAIL() {
    void myfail();

    // Some utilities for lightweight testing
    void OK(const char* m);
    void t_true(bool p);
    void t_false(bool p);
};
