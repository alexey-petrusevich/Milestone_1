#include "../../../include/eau2/kvstore/key.h"

Key::Key(const char *key, size_t nodeId) : Object() {
    this->key = key;
    this->nodeId = nodeId;
}

Key::~Key() {}