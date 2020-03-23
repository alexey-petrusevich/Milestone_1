#pragma once
#include "object.h"
#include "string.h"
#include "msgkind.h"


class Serializer : public Object {
public:
    // serialize single values
    static byte* serialize_int(int value) {
        size_t num_bytes = sizeof(Headers) + sizeof(int);
        Headers header = Headers::INT;
        byte* data = new byte[num_bytes];
        memcpy(data, &header, sizeof(Headers));
        memcpy(data + sizeof(Headers), &value, sizeof(int));
        return data;
    }

    static byte* serialize_double(double value) {
        size_t num_bytes = sizeof(Headers) + sizeof(double);
        Headers header = Headers::DOUBLE;
        byte* data = new byte[num_bytes];
        memcpy(data, &header, sizeof(Headers));
        memcpy(data + sizeof(Headers), &value, sizeof(double));
        return data;
    }

    static byte* serialize_bool(bool value) {
        size_t num_bytes = sizeof(Headers) + sizeof(bool);
        Headers header = Headers::BOOL;
        byte* data = new byte[num_bytes];
        memcpy(data, &header, sizeof(Headers));
        memcpy(data + sizeof(Headers), &value, sizeof(bool));
        return data;
    }

    static byte* serialize_string(String* value) {
        size_t length = value->size();
        size_t num_bytes = sizeof(Headers) + sizeof(size_t) + length;
        Headers header = Headers::STRING;
        byte* data = new byte[num_bytes];
        size_t displacement = 0;
        memcpy(data + displacement, &header, sizeof(Headers));
        displacement += sizeof(Headers);
        memcpy(data + displacement, &length, sizeof(size_t));
        displacement += sizeof(size_t);
        memcpy(data + displacement, value->cstr_, length);
        return data;
    }


    // serialize values
    static byte* serialize_int_array(int* array, size_t size) {
        size_t num_bytes = sizeof(Headers) + sizeof(size_t) + size * sizeof(int);
        Headers header = Headers::INT_ARRAY;
        byte* data = new byte[num_bytes];
        size_t displacement = 0;
        memcpy(data + displacement, &header, sizeof(Headers));
        displacement += sizeof(Headers);
        memcpy(data + displacement, &size, sizeof(size_t));
        displacement += sizeof(size_t);
        memcpy(data + displacement, array, size * sizeof(int));
        return data;
    }

    static byte* serialize_double_array(double* array, size_t size) {
        size_t num_bytes = sizeof(Headers) + sizeof(size_t) + size * sizeof(double);
        Headers header = Headers::DOUBLE_ARRAY;
        byte* data = new byte[num_bytes];
        size_t displacement = 0;
        memcpy(data + displacement, &header, sizeof(Headers));
        displacement += sizeof(Headers);
        memcpy(data + displacement, &size, sizeof(size_t));
        displacement += sizeof(size_t);
        memcpy(data + displacement, array, size * sizeof(double));
        return data;
    }

    static byte* serialize_bool_array(bool* array, size_t size) {
        size_t num_bytes = sizeof(Headers) + sizeof(size_t) + size * sizeof(bool);
        Headers header = Headers::BOOL_ARRAY;
        byte* data = new byte[num_bytes];
        size_t displacement = 0;
        memcpy(data + displacement, &header, sizeof(Headers));
        displacement += sizeof(Headers);
        memcpy(data + displacement, &size, sizeof(size_t));
        displacement += sizeof(size_t);
        memcpy(data + displacement, array, size * sizeof(bool));
        return data;
    }

    static byte* serialize_string_array(String** array, size_t size) {
        size_t num_bytes = sizeof(Headers) + sizeof(size_t);
        for (size_t i = 0; i < size; i++) {
            num_bytes += sizeof(size_t);
            num_bytes += array[i]->size() * sizeof(char);
        }
        Headers header = Headers::STRING_ARRAY;
        byte* data = new byte[num_bytes];
        size_t displacement = 0;
        memcpy(data + displacement, &header, sizeof(Headers));
        displacement += sizeof(Headers);
        memcpy(data + displacement, &size, sizeof(size_t));
        displacement += sizeof(size_t);
        for (size_t i = 0; i < size; i++) {
            size_t length = array[i]->size();
            memcpy(data + displacement, &length, sizeof(size_t));
            displacement += sizeof(size_t);
            memcpy(data + displacement, array[i]->cstr_, length);
            displacement += length;
        }
        return data;
    }
};
