#include <cassert>
#include <iostream>

#include "../src/deserializer.h"
#include "../src/serializer.h"

void FAIL() { exit(1); }
void OK(const char* m) {
    const char* filename = "[test_serialization.cpp]";
    printf("%s %s: [passed]\n", filename, m);
}
void t_true(bool p) {
    if (!p) FAIL();
}
void t_false(bool p) {
    if (p) FAIL();
}

void testSerializeInt() {
    int value1 = 5;
    int value2 = 12;
    byte* serialized1 = Serializer::serialize_int(value1);
    byte* serialized2 = Serializer::serialize_int(value2);
    int deserialized1 = Deserializer::deserialize_int(serialized1);
    int deserialized2 = Deserializer::deserialize_int(serialized2);
    assert(value1 == deserialized1);
    assert(value2 == deserialized2);
    delete[] serialized1;
    delete[] serialized2;
    OK("serialize/deserialize int");
}

void testSerializeDouble() {
    double value1 = 2.72;
    double value2 = 3.14159;
    byte* serialized1 = Serializer::serialize_double(value1);
    byte* serialized2 = Serializer::serialize_double(value2);
    double deserialized1 = Deserializer::deserialize_double(serialized1);
    double deserialized2 = Deserializer::deserialize_double(serialized2);
    assert(value1 - deserialized1 < 1E-14);
    assert(value2 - deserialized2 < 1E-14);
    delete[] serialized1;
    delete[] serialized2;
    OK("serialize/deserialize double");
}

void testSerializeBool() {
    bool value1 = false;
    bool value2 = true;
    byte* serialized1 = Serializer::serialize_bool(value1);
    byte* serialized2 = Serializer::serialize_bool(value2);
    bool deserialized1 = Deserializer::deserialize_bool(serialized1);
    bool deserialized2 = Deserializer::deserialize_bool(serialized2);
    assert(value1 == deserialized1);
    assert(value2 == deserialized2);
    delete[] serialized1;
    delete[] serialized2;
    OK("serialize/deserialize bool");
}

void testSerializeString() {
    String* value1 = new String("Hello");
    String* value2 = new String(" World!");
    byte* serialized1 = Serializer::serialize_string(value1);
    byte* serialized2 = Serializer::serialize_string(value2);
    String* deserialized1 = Deserializer::deserialize_string(serialized1);
    String* deserialized2 = Deserializer::deserialize_string(serialized2);
    assert(value1->equals(deserialized1));
    assert(value2->equals(deserialized2));
    delete value1;
    delete value2;
    delete[] serialized1;
    delete[] serialized2;
    delete deserialized1;
    delete deserialized2;
    OK("serialize/deserialize string");
}

void testSerializeIntArray(size_t size) {
    int* array1 = new int[size];
    int* array2 = new int[size];
    for (size_t i = 0; i < size; i++) {
        array1[i] = i;
        array2[i] = size - i - 1;
    }
    byte* serialized1 = Serializer::serialize_int_array(array1, size);
    byte* serialized2 = Serializer::serialize_int_array(array2, size);
    int* deserialized1 = Deserializer::deserialize_int_array(serialized1);
    int* deserialized2 = Deserializer::deserialize_int_array(serialized2);
    for (size_t i = 0; i < size; i++) {
        assert(array1[i] == deserialized1[i]);
        assert(array2[i] == deserialized2[i]);
    }
    delete[] array1;
    delete[] array2;
    delete[] serialized1;
    delete[] serialized2;
    delete[] deserialized1;
    delete[] deserialized2;
    OK("serialize/deserialize integer array");
}

void testSerializeDoubleArray(size_t size) {
    double* array1 = new double[size];
    double* array2 = new double[size];
    for (size_t i = 0; i < size; i++) {
        array1[i] = i * 0.1;
        array2[i] = (size - i - 1) * 0.1;
    }
    byte* serialized1 = Serializer::serialize_double_array(array1, size);
    byte* serialized2 = Serializer::serialize_double_array(array2, size);
    double* deserialized1 = Deserializer::deserialize_double_array(serialized1);
    double* deserialized2 = Deserializer::deserialize_double_array(serialized2);
    for (size_t i = 0; i < size; i++) {
        assert(array1[i] - deserialized1[i] < 1E-14);
        assert(array2[i] - deserialized2[i] < 1E-14);
    }
    delete[] array1;
    delete[] array2;
    delete[] serialized1;
    delete[] serialized2;
    delete[] deserialized1;
    delete[] deserialized2;
    OK("serialize/deserialize double array");
}

void testSerializeBoolArray(size_t size) {
    bool* array1 = new bool[size];
    bool* array2 = new bool[size];
    for (size_t i = 0; i < size; i++) {
        array1[i] = i % 2;
        array2[i] = (i + 1) % 2;
    }
    byte* serialized1 = Serializer::serialize_bool_array(array1, size);
    byte* serialized2 = Serializer::serialize_bool_array(array2, size);
    bool* deserialized1 = Deserializer::deserialize_bool_array(serialized1);
    bool* deserialized2 = Deserializer::deserialize_bool_array(serialized2);
    for (size_t i = 0; i < size; i++) {
        assert(array1[i] == deserialized1[i]);
        assert(array2[i] == deserialized2[i]);
    }
    delete[] array1;
    delete[] array2;
    delete[] serialized1;
    delete[] serialized2;
    delete[] deserialized1;
    delete[] deserialized2;
    OK("serialize/deserialize bool array");
}

void testSerializeStringArray(size_t size) {
    String** array1 = new String*[size];
    String** array2 = new String*[size];
    char buff[16];
    for (size_t i = 0; i < size; i++) {
        sprintf(buff, "%zu", i);
        array1[i] = new String(buff);
        sprintf(buff, "%zu", size - i - 1);
        array2[i] = new String(buff);
    }
    byte* serialized1 = Serializer::serialize_string_array(array1, size);
    byte* serialized2 = Serializer::serialize_string_array(array2, size);
    String** deserialized1 =
        Deserializer::deserialize_string_array(serialized1);
    String** deserialized2 =
        Deserializer::deserialize_string_array(serialized2);
    for (size_t i = 0; i < size; i++) {
        assert(array1[i]->equals(deserialized1[i]));
        assert(array2[i]->equals(deserialized2[i]));
    }
    for (size_t i = 0; i < size; i++) {
        delete array1[i];
        delete array2[i];
        delete deserialized1[i];
        delete deserialized2[i];
    }
    delete[] array1;
    delete[] array2;
    delete[] serialized1;
    delete[] serialized2;
    delete[] deserialized1;
    delete[] deserialized2;
    OK("serialize/deserialize string array");
}

void testArraySize(size_t size) {
    int* int_array = new int[size];
    double* double_array = new double[size];
    bool* bool_array = new bool[size];
    String** string_array = new String*[size];
    char buff[16];
    for (size_t i = 0; i < size; i++) {
        int_array[i] = static_cast<int>(i);
        double_array[i] = i;
        bool_array[i] = i % 2;
        sprintf(buff, "%zu", i);
        string_array[i] = new String(buff);
    }
    byte* bytes_int_array = Serializer::serialize_int_array(int_array, size);
    byte* bytes_double_array =
        Serializer::serialize_double_array(double_array, size);
    byte* bytes_bool_array = Serializer::serialize_bool_array(bool_array, size);
    byte* bytes_string_array =
        Serializer::serialize_string_array(string_array, size);

    assert(size == Deserializer::array_size(bytes_int_array));
    assert(size == Deserializer::array_size(bytes_double_array));
    assert(size == Deserializer::array_size(bytes_bool_array));
    assert(size == Deserializer::array_size(bytes_string_array));
    delete[] int_array;
    delete[] double_array;
    delete[] bool_array;
    for (size_t i = 0; i < size; i++) {
        delete string_array[i];
    }
    delete[] string_array;
    delete[] bytes_int_array;
    delete[] bytes_double_array;
    delete[] bytes_bool_array;
    delete[] bytes_string_array;
    OK("array size");
}

void testNumBytes(size_t size) {
    int int_value = 5;
    double double_value = 3.14;
    bool bool_value = false;
    String* string_value = new String("hello");
    int* int_array = new int[size];
    double* double_array = new double[size];
    bool* bool_array = new bool[size];
    String** string_array = new String*[size];
    char buff[16];
    for (size_t i = 0; i < size; i++) {
        int_array[i] = static_cast<int>(i);
        double_array[i] = i;
        bool_array[i] = i % 2;
        sprintf(buff, "%zu", i);
        string_array[i] = new String(buff);
    }
    byte* serialized_int = Serializer::serialize_int(int_value);
    byte* serialized_double = Serializer::serialize_double(double_value);
    byte* serialized_bool = Serializer::serialize_bool(bool_value);
    byte* serialized_string = Serializer::serialize_string(string_value);
    byte* bytes_int_array = Serializer::serialize_int_array(int_array, size);
    byte* bytes_double_array =
        Serializer::serialize_double_array(double_array, size);
    byte* bytes_bool_array = Serializer::serialize_bool_array(bool_array, size);
    byte* bytes_string_array =
        Serializer::serialize_string_array(string_array, size);

    assert(Deserializer::num_bytes(serialized_int) ==
           sizeof(size_t) + sizeof(Headers) + sizeof(int));
    assert(Deserializer::num_bytes(serialized_double) ==
           sizeof(size_t) + sizeof(Headers) + sizeof(double));
    assert(Deserializer::num_bytes(serialized_bool) ==
           sizeof(size_t) + sizeof(Headers) + sizeof(bool));
    assert(Deserializer::num_bytes(serialized_string) ==
           sizeof(size_t) + sizeof(Headers) + sizeof(size_t) +
               strlen(string_value->cstr_));
    assert(Deserializer::num_bytes(bytes_int_array) ==
           sizeof(size_t) + sizeof(Headers) + sizeof(size_t) +
               sizeof(int) * size);
    assert(Deserializer::num_bytes(bytes_double_array) ==
           sizeof(size_t) + sizeof(Headers) + sizeof(size_t) +
               sizeof(double) * size);
    assert(Deserializer::num_bytes(bytes_bool_array) ==
           sizeof(size_t) + sizeof(Headers) + sizeof(size_t) +
               sizeof(bool) * size);
    size_t str_arr_bytes = 0;
    for (size_t i = 0; i < size; i++) {
        sprintf(buff, "%zu", i);
        str_arr_bytes += sizeof(size_t);
        str_arr_bytes += strlen(buff);
    }
    assert(Deserializer::num_bytes(bytes_string_array) ==
           sizeof(size_t) + sizeof(Headers) + sizeof(size_t) + str_arr_bytes);

    delete string_value;
    delete[] int_array;
    delete[] double_array;
    delete[] bool_array;
    for (size_t i = 0; i < size; i++) {
        delete string_array[i];
    }
    delete[] string_array;
    delete[] serialized_int;
    delete[] serialized_double;
    delete[] serialized_bool;
    delete[] serialized_string;
    delete[] bytes_int_array;
    delete[] bytes_double_array;
    delete[] bytes_bool_array;
    delete[] bytes_string_array;
    OK("number of bytes");
}

void testGetHeader(size_t size) {
    int int_value = 5;
    double double_value = 3.14;
    bool bool_value = false;
    String* string_value = new String("hello");
    int* int_array = new int[size];
    double* double_array = new double[size];
    bool* bool_array = new bool[size];
    String** string_array = new String*[size];
    char buff[16];
    for (size_t i = 0; i < size; i++) {
        int_array[i] = static_cast<int>(i);
        double_array[i] = i;
        bool_array[i] = i % 2;
        sprintf(buff, "%zu", i);
        string_array[i] = new String(buff);
    }
    byte* serialized_int = Serializer::serialize_int(int_value);
    byte* serialized_double = Serializer::serialize_double(double_value);
    byte* serialized_bool = Serializer::serialize_bool(bool_value);
    byte* serialized_string = Serializer::serialize_string(string_value);
    byte* bytes_int_array = Serializer::serialize_int_array(int_array, size);
    byte* bytes_double_array =
        Serializer::serialize_double_array(double_array, size);
    byte* bytes_bool_array = Serializer::serialize_bool_array(bool_array, size);
    byte* bytes_string_array =
        Serializer::serialize_string_array(string_array, size);

    assert(Deserializer::get_header(serialized_int) == Headers::INT);
    assert(Deserializer::get_header(serialized_double) == Headers::DOUBLE);
    assert(Deserializer::get_header(serialized_bool) == Headers::BOOL);
    assert(Deserializer::get_header(serialized_string) == Headers::STRING);
    assert(Deserializer::get_header(bytes_int_array) == Headers::INT_ARRAY);
    assert(Deserializer::get_header(bytes_double_array) == Headers::DOUBLE_ARRAY);
    assert(Deserializer::get_header(bytes_bool_array) == Headers::BOOL_ARRAY);
    assert(Deserializer::get_header(bytes_string_array) == Headers::STRING_ARRAY);

    delete string_value;
    delete[] int_array;
    delete[] double_array;
    delete[] bool_array;
    for (size_t i = 0; i < size; i++) {
        delete string_array[i];
    }
    delete[] string_array;
    delete[] serialized_int;
    delete[] serialized_double;
    delete[] serialized_bool;
    delete[] serialized_string;
    delete[] bytes_int_array;
    delete[] bytes_double_array;
    delete[] bytes_bool_array;
    delete[] bytes_string_array;
    OK("get header");
}

int main() {
    const size_t array_size = 100;
    testSerializeInt();
    testSerializeDouble();
    testSerializeBool();
    testSerializeString();
    testSerializeIntArray(array_size);
    testSerializeDoubleArray(array_size);
    testSerializeBoolArray(array_size);
    testSerializeStringArray(array_size);
    testArraySize(array_size);
    testNumBytes(array_size);
    testGetHeader(array_size);
    return 0;
}