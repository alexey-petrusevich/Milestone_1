#pragma once

#include <thread>

#include "object.h"
#include "string.h"

/** A Thread wraps the thread operations in the standard library.
 *  author: vitekj@me.com */
class Thread : public Object {
   public:
    std::thread thread_;

    /** Starts running the thread, invoked the run() method. */
    void start();

    /** Wait on this thread to terminate. */
    void join();

    /** Yield execution to another thread. */
    static void yield();

    /** Sleep for millis milliseconds. */
    static void sleep(size_t millis);

    /** Subclass responsibility, the body of the run method */
    virtual void run();

    // there's a better way to get an CwC value out of a threadid, but this'll
    // do for now
    /** Return the id of the current thread */
    static String* thread_id();
};
