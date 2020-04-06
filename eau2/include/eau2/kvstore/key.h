#pragma once
#include "../utils/object.h"
/**
 * @brief Represents Key class to be used in KV-store.
 * @file key.h
 * @author Aliaksei Petrusevich <petrusevich.a@husky.neu.edu>
 * @author Megha Rao <rao.m@husky.neu.edu>
 * @date March 23, 2020
 */
class Key : public Object {
   public:
    const char *key;
    size_t nodeId;

    /**
     * Constructor of this Key object.
     *
     * @param key the key represented as const char (cstring) type
     * @param nodeId the id of the node this key is associated with
     */
    Key(const char *key, size_t nodeId);

    /**
     * Desturctor of this Key object.
     */
    ~Key();
};