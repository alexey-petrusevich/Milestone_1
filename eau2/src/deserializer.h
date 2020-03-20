#include "object.h"
#include "string.h"
class Deserializer : public Object {
    static int deserialize_int(byte* bytes) {
        // TODO implement
        return 0;
    }

    static double deserialize_double(byte* bytes) {
        // TODO implement
        return 0;
    }

    static bool deserialize_bool(byte* bytes) {
        // TODO implement
        return false;
    }

    static String* deserialize_string(byte* bytes) {
        // TODO implement
        return nullptr;
    }

    static int* deserialize_int_array(byte* bytes) {
        // TODO implement
        return nullptr;
    }

    static double* deserialize_double_array(byte* bytes) {
        // TODO implement
        return nullptr;
    }

    static bool* deserialize_bool_array(byte* bytes) {
        // TODO implement
        return nullptr;
    }

    static String** deserialize_string_array(byte* bytes) {
        // TODO implement
        return nullptr;
    }
};
