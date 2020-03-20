// lang::CwC

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "coltypes.h"

void affirm(bool test, const char *msg) {
    if (!(test)) {
        fprintf(stderr, "%s\n", msg);
        abort();
    }
}

void check_in_bounds(int argc, int index, int arguments) {
    affirm((index + arguments < argc), "Missing argument");
}

unsigned int check_positive(int i) {
    affirm((i >= 0), "Only positive integers allowed");
    return i;
}

bool is_int(char *c) {
    if (*c == '\0') {
        return false;
    }
    for (int i = 0; c[i] != '\0'; i++) {
        if (i == 0 && (c[i] == '+' || c[i] == '-')) {
            continue;
        } else if (!isdigit(c[i])) {
            return false;
        }
    }
    return true;
}

bool is_float(char *c) {
    if (*c == '\0') {
        return false;
    }
    bool has_decimal = false;
    for (int i = 0; c[i] != '\0'; i++) {
        if (i == 0 && (c[i] == '+' || c[i] == '-')) {
            continue;
        } else if (c[i] == '.' && has_decimal) {
            return false;
        } else if (c[i] == '.') {
            has_decimal = true;
        } else if (!isdigit(c[i])) {
            return false;
        }
    }
    return true;
}

// returns the inferred typing of the char*
ColType infer_type(char* c) {
    // missing values
    if (c == nullptr) {
        return ColType::BOOLEAN;
    }
    // check boolean
    if (strlen(c) == 1) {
        if ((*c == '0') || (*c == '1')) {
            return ColType::BOOLEAN;
        }
    }
    // check int
    if (is_int(c)) {
        return ColType::INTEGER;
    }
    // check float
    if (is_float(c)) {
        return ColType::DOUBLE;
    }
    return ColType::STRING;
}
