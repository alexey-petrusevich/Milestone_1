#include "../../include/eau2/serialization/deserializer.h"

#include <cassert>
#include <cstdlib>
#include <cstring>

int Deserializer::deserialize_int(byte* bytes) {
    Headers header;
    size_t displacement = sizeof(size_t);
    memcpy(&header, bytes + displacement, sizeof(Headers));
    displacement += sizeof(Headers);
    assert(header == Headers::INT);
    int value;
    memcpy(&value, bytes + displacement, sizeof(int));
    return value;
}

double Deserializer::deserialize_double(byte* bytes) {
    Headers header;
    size_t displacement = sizeof(size_t);
    memcpy(&header, bytes + displacement, sizeof(Headers));
    displacement += sizeof(Headers);
    assert(header == Headers::DOUBLE);
    double value;
    memcpy(&value, bytes + displacement, sizeof(double));
    return value;
}

bool Deserializer::deserialize_bool(byte* bytes) {
    Headers header;
    size_t displacement = sizeof(size_t);
    memcpy(&header, bytes + displacement, sizeof(Headers));
    displacement += sizeof(Headers);
    assert(header == Headers::BOOL);
    bool value;
    memcpy(&value, bytes + displacement, sizeof(bool));
    return value;
}

String* Deserializer::deserialize_string(byte* bytes) {
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

int* Deserializer::deserialize_int_array(byte* bytes) {
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

double* Deserializer::deserialize_double_array(byte* bytes) {
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

bool* Deserializer::deserialize_bool_array(byte* bytes) {
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

String** Deserializer::deserialize_string_array(byte* bytes) {
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

size_t Deserializer::array_size(byte* bytes) {
    size_t size;
    memcpy(&size, bytes + sizeof(size_t) + sizeof(Headers), sizeof(size_t));
    return size;
}

size_t Deserializer::num_bytes(byte* bytes) {
    size_t num_bytes;
    memcpy(&num_bytes, bytes, sizeof(size_t));
    return num_bytes;
}

Headers Deserializer::get_header(byte* bytes) {
    Headers header;
    memcpy(&header, bytes + sizeof(size_t), sizeof(Headers));
    return header;
}
