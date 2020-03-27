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
    const size_t num_nodes = 4;
    FakeNode** fake_nodes;
    //Array* network_nodes;
    Lock** locks; // for simulating network behavior

    /**
     * Constructor of this KVStore.
     */
    KVStore() {
        this->map = map;
        // init network here; or fake KVStores
        
        this->fake_nodes = new FakeNode*[this->num_nodes];
        //this->network_nodes = new Array();

        this->locks = new Lock*[this->num_nodes];
        for (size_t i = 0; i < this->num_nodes; i++) {
            this->locks[i] = new Lock();
            FakeNode* newNode = new FakeNode(i + 1, locks[i]);
            this->fake_nodes[i] = newNode;
            //this->fake_nodes->append(newNode);
            newNode->start();
        }
    }

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
        byte* local_bytes = this->map->get(&key);
        byte** remote_bytes = new byte*[num_nodes];
        // 1. check every node for serialized objects with the given key
        for (size_t i = 0; i < this->num_nodes; i++) {
            remote_bytes[i] = this->fake_nodes[i]->request_data(&key);
            this->locks[i]->wait();
        }
        // 1.1 wait for all nodes to reply
        for (int i = 0; i < this->num_nodes; i++) {
            
        }
        
        // 2. merge all objects in one DataFrame and return
        return DataFrame::merge(local_bytes, remote_bytes);
    }

    ~KVStore() { delete this->map; }
};


// represents a fake netowork node
class FakeNode : public Thread {
public:
    ByteMap* store;
    size_t nodeId;
    Lock* lock;

    FakeNode(size_t nodeId, Lock* lock) {
        this->nodeId = nodeId;
        this->lock = lock;
    }

    void run() {
        // listen for information on the channel
        
    }

    byte* request_data(Key* key) {
        byte* data = this->store->get(key);
        this->lock->notify_all(); // notify the node waiting for this data that data has been retrieved
        return data;
    }
};
