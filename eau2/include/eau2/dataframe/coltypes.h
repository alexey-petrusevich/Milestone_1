#pragma once

/**
 * @brief This file represent implementation of ColType enumerator
 * storing four types of columns and its ASCII values as actual enum values.
 * @file coltypes.h
 * @author Aliaksei Petrusevich <petrusevich.a@husky.neu.edu>
 * @author Megha Rao <rao.m@husky.neu.edu>
 * @date February 15, 2020
 */

/**
 * Enumerator that represents types of columns.
 */
enum class ColType {
    INTEGER = 'I',
    DOUBLE = 'D',
    BOOLEAN = 'B',
    STRING = 'S',
    UNKNOWN = 'U'
};

/**
 * Returns the column type of the given sequence of characters. Used in accord
 * with the parser from sorer.h.
 *
 * @param c the sequence of characters representing sorer-type value
 * @return the type of the column as ColType
 */
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
