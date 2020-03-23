#include "dataframe.h"
#include "map.h"
#include "object.h"
#include "string.h"

/**
 * Represents Key class to be used in KV-store.
 */
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

    Value(byte* bytes) { this->bytes = bytes; }
};

class KVStore : public Object {
   public:
    Map* map;

    KVStore() { this->map = map; }

    void put(Key* key, byte* value) {
        Value* v = new Value(value);
        this->map->set(key, v);
    }

    DataFrame* get(Key key) {
        Value* value = dynamic_cast<Value*>(this->map->get(&key));
        DataFrame* df = DataFrame::fromBytes(value->bytes);
        return df;
    }

    // TODO: add network layer
    DataFrame* wait_and_get(Key key) {  // same as get for now
        Value* value = dynamic_cast<Value*>(this->map->get(&key));
        DataFrame* df = DataFrame::fromBytes(value->bytes);
        return df;
    }

    ~KVStore() { delete this->map; }
};