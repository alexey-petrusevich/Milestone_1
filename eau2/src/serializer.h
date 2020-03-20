#pragma once
#include "object.h"
#include "string.h"
#include "msgkind.h"


class Serializer : public Object {
public:
    // serialize single values
    static byte* serialize_int(int value) {

    }

    static byte* serialize_double(double value) {

    }

    static byte* serialize_bool(bool value) {

    }

    static byte* serialize_string(String* value) {

    }


    // serialize values
    static byte* serialize_int_array(int* array, size_t size) {

    }

    static byte* serialize_double_array(double* array, size_t size) {

    }

    static byte* serialize_bool_array(bool* array, size_t size) {

    }

    static byte* serialize_string_array(String** array, size_t size) {
        
    }
};
