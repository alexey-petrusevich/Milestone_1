#pragma once
#include <cstdlib>

#include "../utils/object.h"
#include "../utils/string.h"
#include "headers.h"

/**
 * @brief Represents a class that contains various method for serializaing
 * various objects, primarily primitives and array of int, double, bool, String
 * types. Serialized objects are represented by byte (unsigned char) type.
 * Primitive objects are represnted by the followig serialization pattern:
 * [number of bytes][header/type of object][serialized data]
 * number of bytes - the size of block of data; includes its own size (size_t)
 * header/type - the type of object represented by Headers enum
 * serialized data - actual data represented as bytes
 * Arrays are represented similarly:
 * [number of bytes][header/type of object][number of elements][serialized data]
 * number of bytes - the size of block of data; includes its own size (size_t)
 * header/type - the type of object represented by Headers enum
 * number of elements - the number of elements in the array
 * serialized data - actual data represented as bytes
 * @file serializer.h
 * @author Aliaksei Petrusevich <petrusevich.a@husky.neu.edu>
 * @author Megha Rao <rao.m@husky.neu.edu>
 * @date March 23, 2020
 */
class Serializer : public Object {
   public:
    /**
     * Returns serialized integer.
     *
     * @param value integer value to be serialized
     * @return serialized integer value
     */
    static byte* serialize_int(int value);

    /**
     * Returns serialized double.
     *
     * @param value double value to be serialized
     * @return serialized double value
     */
    static byte* serialize_double(double value);

    /**
     * Returns serialized boolean.
     *
     * @param value boolean value to be serialized
     * @return serialized boolean value
     */
    static byte* serialize_bool(bool value);

    /**
     * Returns serialized value of String* type.
     *
     * @param value String value to be serialized
     * @return serialized String value
     */
    static byte* serialize_string(String* value);

    /**
     * Returns serialized array of integers.
     *
     * @param value array of integers to be serialized
     * @return serialized array of integers
     */
    static byte* serialize_int_array(int* array, size_t size);

    /**
     * Returns serialized array of double.
     *
     * @param value array of double to be serialized
     * @return serialized array of double
     */
    static byte* serialize_double_array(double* array, size_t size);

    /**
     * Returns serialized array of booleans.
     *
     * @param value array of booleans to be serialized
     * @return serialized array of booleans
     */
    static byte* serialize_bool_array(bool* array, size_t size);

    /**
     * Returns serialized array of Strings.
     *
     * @param value array of Strings to be serialized
     * @return serialized array of Strings
     */
    static byte* serialize_string_array(String** array, size_t size);
};
