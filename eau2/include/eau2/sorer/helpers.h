#pragma once


/**
 * @brief Represents a helper class being used by sorer.h. The class contains
 * various methods to be used multiple times by sorer.h. The original file was
 * performed by icicle.
 * @file helpers.h
 * @author icicle
 * @author Aliaksei Petrusevich <petrusevich.a@husky.neu.edu>
 * @author Megha Rao <rao.m@husky.neu.edu>
 * @date March 30, 2020
 */

/**
 * Checks if the given value is true. If false, exits the program.
 * @param test the value being tested for falseness
 * @param msg the message being printed to STDOUT if the given test is false
 */
void affirm(bool test, const char *msg);


/**
 * Checks if the sum of the given index and arguments is less than the value of
 * argc. All numbers are represented as integers.
 * @param argc the upper boundary
 * @param index the begininig index
 * @param arguments the ending index
 */
void check_in_bounds(int argc, int index, int arguments);

/**
 * Checks if the given integer value is positive. Returns itself as unsigned
 * integer of test passes.
 * @param i the integer value being tested for being positive
 * @return the given value as unsigned integer
 */
unsigned int check_positive(int i);

/**
 * Returns true if the given c-string is a integer type. Used by sorer.
 * @param c the c-string representing the sorer-type value
 * @return true of the given c-string is of integer type and false otherwise
 */
bool is_int(char *c);

/**
 * Returns true if the given c-string is a float (double) type. Used by sorer.
 * @param c the c-string representing the sorer-type value
 * @return true of the given c-string is of float (double) type and false
 * otherwise
 */
bool is_float(char *c);
