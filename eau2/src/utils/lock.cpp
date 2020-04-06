#include "../../include/eau2/utils/lock.h"

void Lock::lock() { mtx_.lock(); }

void Lock::unlock() { mtx_.unlock(); }

void Lock::wait() { cv_.wait(mtx_); }

void Lock::notify_all() { cv_.notify_all(); }
