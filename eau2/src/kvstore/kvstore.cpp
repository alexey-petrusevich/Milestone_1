#include "../../include/eau2/kvstore/kvstore.h"

FakeNode::FakeNode(size_t nodeId, Lock* lock) {
    this->nodeId = nodeId;
    this->lock = lock;
}

void FakeNode::run() {}

byte* FakeNode::request_data(Key* key) {
    byte* data = this->store->get(key);
    this->lock->notify_all();  // notify the node waiting for this data that
                               // data has been retrieved
    return data;
}

KVStore::KVStore() {
    this->map = map;
    // init network here; or fake KVStores

    this->fake_nodes = new FakeNode*[this->num_nodes];
    // this->network_nodes = new Array();

    this->locks = new Lock*[this->num_nodes];
    for (size_t i = 0; i < this->num_nodes; i++) {
        this->locks[i] = new Lock();
        FakeNode* newNode = new FakeNode(i + 1, locks[i]);
        this->fake_nodes[i] = newNode;
        // this->fake_nodes->append(newNode);
        newNode->start();
    }
}

void KVStore::put(Key* key, byte* value) { this->map->set(key, value); }

DataFrame* KVStore::get(Key key) {
    byte* bytes = this->map->get(&key);
    return DataFrame::fromBytes(bytes);
}

DataFrame* KVStore::wait_and_get(Key key) {
    byte* local_bytes = this->map->get(&key);
    byte** remote_bytes = new byte*[num_nodes];
    // 1. check every node for serialized objects with the given key
    for (size_t i = 0; i < this->num_nodes; i++) {
        remote_bytes[i] = this->fake_nodes[i]->request_data(&key);
    }
    // 1.1 wait for all nodes to reply
    for (int i = 0; i < this->num_nodes; i++) {
        this->locks[i]->wait();
    }

    // 2. merge all objects in one DataFrame and return
    return DataFrame::merge(local_bytes, remote_bytes, num_nodes);
}

// destructor
KVStore::~KVStore() { delete this->map; }
