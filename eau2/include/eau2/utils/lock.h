#pragma once
#include <condition_variable>
#include <mutex>

#include "object.h"

/** A convenient lock and condition variable wrapper. */
class Lock : public Object {
   public:
    std::mutex mtx_;
    std::condition_variable_any cv_;

    /** Request ownership of this lock.
     *
     *  Note: This operation will block the current thread until the lock can
     *  be acquired.
     */
    void lock();

    /** Release this lock (relinquish ownership). */
    void unlock();

    /** Sleep and wait for a notification on this lock.
     *
     *  Note: After waking up, the lock is owned by the current thread and
     *  needs released by an explicit invocation of unlock().
     */
    void wait();

    // Notify all threads waiting on this lock
    void notify_all();
};