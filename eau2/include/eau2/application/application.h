
#pragma once
#include <iostream>

#include "../kvstore/kvstore.h"
#include "../utils/object.h"

/**
 * @brief Represents an application class that starts the KV-store application.
 * Along with creating a local storage, creates remote storage using network.
 * For Milestone 3, network nodes are replaced with threads represented by
 * Thread class.
 * @file application.h
 * @author Aliaksei Petrusevich <petrusevich.a@husky.neu.edu>
 * @author Megha Rao <rao.m@husky.neu.edu>
 * @date March 30, 2020
 */
class Application : public Object {
   public:
    size_t nodeId;
    KVStore kv;

    /**
     * Constructor of this application.
     *
     * @param nodeId the id of the base node
     */
    Application(size_t nodeId);

    /**
     * Starts the application.
     */
    virtual void run_() = 0;

    /**
     * Returns the id of this node.
     *
     * @return the id of this node as size_t
     */
    size_t this_node();

    /**
     * Destructor of this class.
     */
    ~Application();
};


