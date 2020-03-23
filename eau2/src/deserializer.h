#include "msgkind.h"
#include "object.h"
#include "string.h"

class Deserializer : public Object {
    static int deserialize_int(byte* bytes) {
        Headers header;
        memcpy(&header, bytes, sizeof(Headers));
        assert(header == Headers::INT);
        int value;
        memcpy(&value, bytes + sizeof(Headers), sizeof(int));
        return value;
    }

    static double deserialize_double(byte* bytes) {
        Headers header;
        memcpy(&header, bytes, sizeof(Headers));
        assert(header == Headers::DOUBLE);
        double value;
        memcpy(&value, bytes + sizeof(Headers), sizeof(double));
        return value;
    }

    static bool deserialize_bool(byte* bytes) {
        Headers header;
        memcpy(&header, bytes, sizeof(Headers));
        assert(header == Headers::BOOL);
        bool value;
        memcpy(&value, bytes + sizeof(Headers), sizeof(double));
        return value;
    }

    static String* deserialize_string(byte* bytes) {
        Headers header;
        size_t displacement = 0;
        memcpy(&header, bytes, sizeof(Headers));
        displacement += sizeof(Headers);
        assert(header == Headers::STRING);
        size_t length;
        memcpy(&length, bytes + displacement, sizeof(size_t));
        displacement += sizeof(size_t);
        char* cstr = new char[length + 1];
        memcpy(&cstr, bytes + sizeof(Headers), length);
        cstr[length] = '\0';
        return new String(cstr);
    }

    static int* deserialize_int_array(byte* bytes) {
        Headers header;
        size_t displacement = 0;
        memcpy(&header, bytes, sizeof(Headers));
        displacement += sizeof(Headers);
        assert(header == Headers::INT_ARRAY);
        size_t size;
        memcpy(&size, bytes + displacement, sizeof(size_t));
        displacement += sizeof(size_t);
        int* array = new int[size];
        memcpy(&array, bytes + displacement, size * sizeof(int));
        return array;
    }

    static double* deserialize_double_array(byte* bytes) {
        Headers header;
        size_t displacement = 0;
        memcpy(&header, bytes, sizeof(Headers));
        displacement += sizeof(Headers);
        assert(header == Headers::DOUBLE_ARRAY);
        size_t size;
        memcpy(&size, bytes + displacement, sizeof(size_t));
        displacement += sizeof(size_t);
        double* array = new double[size];
        memcpy(&array, bytes + displacement, size * sizeof(double));
        return array;
    }

    static bool* deserialize_bool_array(byte* bytes) {
        Headers header;
        size_t displacement = 0;
        memcpy(&header, bytes, sizeof(Headers));
        displacement += sizeof(Headers);
        assert(header == Headers::BOOL_ARRAY);
        size_t size;
        memcpy(&size, bytes + displacement, sizeof(size_t));
        displacement += sizeof(size_t);
        bool* array = new bool[size];
        memcpy(&array, bytes + displacement, size * sizeof(bool));
        return array;
    }

    static String** deserialize_string_array(byte* bytes) {
        Headers header;
        size_t displacement = 0;
        memcpy(&header,bytes,  sizeof(Headers));
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
        }
        return array;
    }
};
