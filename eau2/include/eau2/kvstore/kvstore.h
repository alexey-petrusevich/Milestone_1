#pragma once
#include "../collections/maps/byte_map.h"
#include "../dataframe/dataframe.h"
#include "../utils/lock.h"
#include "../utils/thread.h"

// represents a fake netowork node
class FakeNode : public Thread {
   public:
    ByteMap* store;
    size_t nodeId;
    Lock* lock;

    FakeNode(size_t nodeId, Lock* lock);

    void run();

    byte* request_data(Key* key);
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
    const size_t num_nodes = 4;
    FakeNode** fake_nodes;
    // Array* network_nodes;
    Lock** locks;  // for simulating network behavior

    /**
     * Constructor of this KVStore.
     */
    KVStore();

    /**
     * Puts a new serialized object into this KVStore.
     *
     * @param key the given Key associated with given serialized object
     * @param value the given serialized object to be stored in this KVStore
     */
    void put(Key* key, byte* value);

    /**
     * Returns a serialized object wrapped in the DataFrame. If key is not
     * found, returns nullptr. Checks local storage only.
     *
     * @param key the key associated with serialized object
     * @return deserialized object represented as DataFrame
     */
    DataFrame* get(Key key);

    /**
     * Returns a serialized object wrapped in the DataFrame. If the key is not
     * found, returns nullptr. Checks neighboring network nodes for chunks of
     * data before returning it.
     *
     * @param key the key associated with serialized value
     */
    DataFrame* wait_and_get(Key key);

    // destructor
    ~KVStore();
};
