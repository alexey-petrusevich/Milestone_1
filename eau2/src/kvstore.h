#include "dataframe.h"
#include "map.h"
#include "object.h"
#include "string.h"

/**
 * @brief Represents Key class to be used in KV-store.
 * @file kvstore.h
 * @author Aliaksei Petrusevich <petrusevich.a@husky.neu.edu>
 * @author Megha Rao <rao.m@husky.neu.edu>
 * @date March 23, 2020
 */
class Key : public Object {
   public:
    const char* key;
    size_t nodeId;

    /**
     * Constructor of this Key object.
     *
     * @param key the key represented as const char (cstring) type
     * @param nodeId the id of the node this key is associated with
     */
    Key(const char* key, size_t nodeId) : Object() {
        this->key = key;
        this->nodeId = nodeId;
    }

    /**
     * Desturctor of this Key object.
     */
    ~Key() {}
};

/**
 * @brief Represens a KV-store class that stores keys as a pair of cstring
 * (const char) and a node id associated with the value represented by
 * byte (unsigned char) type of serialized object.
 * @file kvstore.h
 * @author Aliaksei Petrusevich <petrusevich.a@husky.neu.edu>
 * @author Megha Rao <rao.m@husky.neu.edu>
 * @date March 23, 2020
 */
class KVStore : public Object {
   public:
    ByteMap* map;

    /**
     * Constructor of this KVStore.
     */
    KVStore() { this->map = map; }

    /**
     * Puts a new serialized object into this KVStore.
     *
     * @param key the given Key associated with given serialized object
     * @param value the given serialized object to be stored in this KVStore
     */
    void put(Key* key, byte* value) { this->map->set(key, value); }

    /**
     * Returns a serialized object wrapped in the DataFrame. If key is not
     * found, returns nullptr. Checks local storage only.
     *
     * @param key the key associated with serialized object
     * @return deserialized object represented as DataFrame
     */
    DataFrame* get(Key key) {
        byte* bytes = this->map->get(&key);
        return DataFrame::fromBytes(bytes);
    }

    /**
     * Returns a serialized object wrapped in the DataFrame. If the key is not
     * found, returns nullptr. Checks neighboring network nodes for chunks of
     * data before returning it.
     *
     * @param key the key associated with serialized value
     */
    DataFrame* wait_and_get(Key key) {  // same as get for now
        byte* bytes = this->map->get(&key);
        return DataFrame::fromBytes(bytes);
    }

    ~KVStore() { delete this->map; }
};
