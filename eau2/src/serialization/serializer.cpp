#include "../../../include/eau2/serialization/serializer.h"

#include <cstring>

byte* Serializer::serialize_int(int value) {
    size_t num_bytes = sizeof(size_t) + sizeof(Headers) + sizeof(int);
    size_t displacement = 0;
    Headers header = Headers::INT;
    byte* data = new byte[num_bytes];
    memcpy(data + displacement, &num_bytes, sizeof(size_t));
    displacement += sizeof(size_t);
    memcpy(data + displacement, &header, sizeof(Headers));
    displacement += sizeof(Headers);
    memcpy(data + displacement, &value, sizeof(int));
    return data;
}

byte* Serializer::serialize_double(double value) {
    size_t num_bytes = sizeof(size_t) + sizeof(Headers) + sizeof(double);
    size_t displacement = 0;
    Headers header = Headers::DOUBLE;
    byte* data = new byte[num_bytes];
    memcpy(data + displacement, &num_bytes, sizeof(size_t));
    displacement += sizeof(size_t);
    memcpy(data + displacement, &header, sizeof(Headers));
    displacement += sizeof(Headers);
    memcpy(data + displacement, &value, sizeof(double));
    return data;
}

byte* Serializer::serialize_bool(bool value) {
    size_t num_bytes = sizeof(size_t) + sizeof(Headers) + sizeof(bool);
    size_t displacement = 0;
    Headers header = Headers::BOOL;
    byte* data = new byte[num_bytes];
    memcpy(data + displacement, &num_bytes, sizeof(size_t));
    displacement += sizeof(size_t);
    memcpy(data + displacement, &header, sizeof(Headers));
    displacement += sizeof(Headers);
    memcpy(data + displacement, &value, sizeof(bool));
    return data;
}

byte* Serializer::serialize_string(String* value) {
    size_t length = value->size();
    size_t num_bytes =
        sizeof(size_t) + sizeof(Headers) + sizeof(size_t) + length;
    size_t displacement = 0;
    Headers header = Headers::STRING;
    byte* data = new byte[num_bytes];
    memcpy(data + displacement, &num_bytes, sizeof(size_t));
    displacement += sizeof(size_t);
    memcpy(data + displacement, &header, sizeof(Headers));
    displacement += sizeof(Headers);
    memcpy(data + displacement, &length, sizeof(size_t));
    displacement += sizeof(size_t);
    memcpy(data + displacement, value->cstr_, length);
    return data;
}

byte* Serializer::serialize_int_array(int* array, size_t size) {
    size_t num_bytes =
        sizeof(size_t) + sizeof(Headers) + sizeof(size_t) + size * sizeof(int);
    size_t displacement = 0;
    Headers header = Headers::INT_ARRAY;
    byte* data = new byte[num_bytes];
    memcpy(data + displacement, &num_bytes, sizeof(size_t));
    displacement += sizeof(size_t);
    memcpy(data + displacement, &header, sizeof(Headers));
    displacement += sizeof(Headers);
    memcpy(data + displacement, &size, sizeof(size_t));
    displacement += sizeof(size_t);
    memcpy(data + displacement, array, size * sizeof(int));
    return data;
}

byte* Serializer::serialize_double_array(double* array, size_t size) {
    size_t num_bytes = sizeof(size_t) + sizeof(Headers) + sizeof(size_t) +
                       size * sizeof(double);
    size_t displacement = 0;
    Headers header = Headers::DOUBLE_ARRAY;
    byte* data = new byte[num_bytes];
    memcpy(data + displacement, &num_bytes, sizeof(size_t));
    displacement += sizeof(size_t);
    memcpy(data + displacement, &header, sizeof(Headers));
    displacement += sizeof(Headers);
    memcpy(data + displacement, &size, sizeof(size_t));
    displacement += sizeof(size_t);
    memcpy(data + displacement, array, size * sizeof(double));
    return data;
}

byte* Serializer::serialize_bool_array(bool* array, size_t size) {
    size_t num_bytes =
        sizeof(size_t) + sizeof(Headers) + sizeof(size_t) + size * sizeof(bool);
    size_t displacement = 0;
    Headers header = Headers::BOOL_ARRAY;
    byte* data = new byte[num_bytes];
    memcpy(data + displacement, &num_bytes, sizeof(size_t));
    displacement += sizeof(size_t);
    memcpy(data + displacement, &header, sizeof(Headers));
    displacement += sizeof(Headers);
    memcpy(data + displacement, &size, sizeof(size_t));
    displacement += sizeof(size_t);
    memcpy(data + displacement, array, size * sizeof(bool));
    return data;
}

byte* Serializer::serialize_string_array(String** array, size_t size) {
    size_t num_bytes = sizeof(size_t) + sizeof(Headers) + sizeof(size_t);
    size_t displacement = 0;
    for (size_t i = 0; i < size; i++) {
        num_bytes += sizeof(size_t);
        num_bytes += array[i]->size() * sizeof(char);
    }
    Headers header = Headers::STRING_ARRAY;
    byte* data = new byte[num_bytes];
    memcpy(data + displacement, &num_bytes, sizeof(size_t));
    displacement += sizeof(size_t);
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