#pragma once

#include "msgkind.h"
#include "object.h"
#include "string.h"

/**
 * @brief Represents a class that contains various method for deserializaing
 * various objects, primarily primitives and array of int, double, bool, String
 * types. Works in accord with Serializer class, which could be found in
 * serializer.h. Serialized objects are represented by byte (unsigned char)
 * type. Primitive objects are represnted by the followig serialization pattern:
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
 * @file deserializer.h
 * @author Aliaksei Petrusevich <petrusevich.a@husky.neu.edu>
 * @author Megha Rao <rao.m@husky.neu.edu>
 * @date March 23, 2020
 */
class Deserializer : public Object {
   public:
    /**
     * Returns deserialized integer given its serialized representation.
     *
     * @param bytes serialized integer
     * @return deserialized integer
     */
    static int deserialize_int(byte* bytes) {
        Headers header;
        size_t displacement = sizeof(size_t);
        memcpy(&header, bytes + displacement, sizeof(Headers));
        displacement += sizeof(Headers);
        assert(header == Headers::INT);
        int value;
        memcpy(&value, bytes + displacement, sizeof(int));
        return value;
    }

    /**
     * Returns deserialized double given its serialized representation.
     *
     * @param bytes serialized double
     * @return deserialized double
     */
    static double deserialize_double(byte* bytes) {
        Headers header;
        size_t displacement = sizeof(size_t);
        memcpy(&header, bytes + displacement, sizeof(Headers));
        displacement += sizeof(Headers);
        assert(header == Headers::DOUBLE);
        double value;
        memcpy(&value, bytes + displacement, sizeof(double));
        return value;
    }

    /**
     * Returns deserialized boolean given its serialized representation.
     *
     * @param bytes serialized boolean
     * @return deserialized boolean
     */
    static bool deserialize_bool(byte* bytes) {
        Headers header;
        size_t displacement = sizeof(size_t);
        memcpy(&header, bytes + displacement, sizeof(Headers));
        displacement += sizeof(Headers);
        assert(header == Headers::BOOL);
        bool value;
        memcpy(&value, bytes + displacement, sizeof(bool));
        return value;
    }

    /**
     * Returns a pointer to deserialized String given its serialized
     * representation.
     *
     * @param bytes serialized String
     * @return pointer to deserialized String
     */
    static String* deserialize_string(byte* bytes) {
        Headers header;
        size_t displacement = sizeof(size_t);
        memcpy(&header, bytes + displacement, sizeof(Headers));
        displacement += sizeof(Headers);
        assert(header == Headers::STRING);
        size_t length;
        memcpy(&length, bytes + displacement, sizeof(size_t));
        displacement += sizeof(size_t);
        char* cstr = new char[length + 1];
        memcpy(cstr, bytes + displacement, length);
        cstr[length] = '\0';
        String* value = new String(cstr);
        delete[] cstr;
        return value;
    }

    /**
     * Returns deserialized array of integers given its serialized
     * representation.
     *
     * @param bytes serialized array of integers
     * @return deserialized array of integers
     */
    static int* deserialize_int_array(byte* bytes) {
        Headers header;
        size_t displacement = sizeof(size_t);
        memcpy(&header, bytes + displacement, sizeof(Headers));
        displacement += sizeof(Headers);
        assert(header == Headers::INT_ARRAY);
        size_t size;
        memcpy(&size, bytes + displacement, sizeof(size_t));
        displacement += sizeof(size_t);
        int* array = new int[size];
        memcpy(array, bytes + displacement, size * sizeof(int));
        return array;
    }

    /**
     * Returns deserialized array of doubles given its serialized
     * representation.
     *
     * @param bytes serialized array of doubles
     * @return deserialized array of doubles
     */
    static double* deserialize_double_array(byte* bytes) {
        Headers header;
        size_t displacement = sizeof(size_t);
        memcpy(&header, bytes + displacement, sizeof(Headers));
        displacement += sizeof(Headers);
        assert(header == Headers::DOUBLE_ARRAY);
        size_t size;
        memcpy(&size, bytes + displacement, sizeof(size_t));
        displacement += sizeof(size_t);
        double* array = new double[size];
        memcpy(array, bytes + displacement, size * sizeof(double));
        return array;
    }

    /**
     * Returns deserialized array of booleans given its serialized
     * representation.
     *
     * @param bytes serialized array of boolean
     * @return deserialized array of boolean
     */
    static bool* deserialize_bool_array(byte* bytes) {
        Headers header;
        size_t displacement = sizeof(size_t);
        memcpy(&header, bytes + displacement, sizeof(Headers));
        displacement += sizeof(Headers);
        assert(header == Headers::BOOL_ARRAY);
        size_t size;
        memcpy(&size, bytes + displacement, sizeof(size_t));
        displacement += sizeof(size_t);
        bool* array = new bool[size];
        memcpy(array, bytes + displacement, size * sizeof(bool));
        return array;
    }

    /**
     * Returns deserialized array of Strings given its serialized
     * representation.
     *
     * @param bytes serialized array of Strings
     * @return deserialized array of Strings
     */
    static String** deserialize_string_array(byte* bytes) {
        Headers header;
        size_t displacement = sizeof(size_t);
        memcpy(&header, bytes + displacement, sizeof(Headers));
        displacement += sizeof(Headers);
        assert(header == Headers::STRING_ARRAY);
        size_t size;
        memcpy(&size, bytes + displacement, sizeof(size_t));
        displacement += sizeof(size_t);
        String** array = new String*[size];
        for (size_t i = 0; i < size; i++) {
            size_t length;
            memcpy(&length, bytes + displacement, sizeof(size_t));
            displacement += sizeof(size_t);
            char* cstr = new char[length + 1];
            memcpy(cstr, bytes + displacement, length);
            displacement += length;
            cstr[length] = '\0';
            array[i] = new String(cstr);
            delete[] cstr;
        }
        return array;
    }

    /**
     * Returns the size of the serialized array. Does not depend on the type
     * of the array.
     *
     * @param bytes pointer to serialized array
     * @return the size of the serialized array
     */
    static size_t array_size(byte* bytes) {
        size_t size;
        memcpy(&size, bytes + sizeof(size_t) + sizeof(Headers), sizeof(size_t));
        return size;
    }

    /**
     * Retruns the number of bytes given the pointer to the serialized block of
     * memory.
     *
     * @param pointer to serialized block of memory
     * @return the number of bytes associated with the block of memory
     */
    static size_t num_bytes(byte* bytes) {
        size_t num_bytes;
        memcpy(&num_bytes, bytes, sizeof(size_t));
        return num_bytes;
    }

    /**
     * Returns the header type of serialized object.
     * 
     * @param bytes serialized objects
     * @return the header of the serialized object of Header enum type
     */
    static Headers get_header(byte* bytes) {
        Headers header;
        memcpy(&header, bytes + sizeof(size_t), sizeof(Headers));
        return header;
    }
};
