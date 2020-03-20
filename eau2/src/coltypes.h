// lang::CwC
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
enum ColType {
    INTEGER = 'I',
    DOUBLE = 'D',
    BOOLEAN = 'B',
    STRING = 'S',
    UNKNOWN = 'U'
};
