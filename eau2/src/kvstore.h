#include "object.h"
#include "string.h"
#include "dataframe.h"
#include "map.h"

typedef unsigned char byte;

// represents a key class
class Key : public Object {
public:
    const char* key;
    size_t nodeId;

    Key(const char* key, size_t nodeId) : Object() {
        this->key = key;
        this->nodeId = nodeId;
    }
};

class Value : public Object {
public:
    byte* bytes;
    Value(byte* bytes) {
        this->bytes = bytes;
    }
};


class KVStore : public Object {
public:
    Map map;

    void put(Key* key, byte* value) {
        Value* v = new Value(value);
        map.set(key, v);
    }


    DataFrame* get(Key key) {
        // TODO implement
        return nullptr;
    }


    DataFrame* wait_and_get(Key key) {
        // TODO implement
        return nullptr;
    }
};