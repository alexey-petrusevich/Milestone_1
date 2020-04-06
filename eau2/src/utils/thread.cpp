#include "../../include/eau2/utils/thread.h"

#include <cassert>
#include <cstdlib>
#include <sstream>

void Thread::start() {
    thread_ = std::thread([this] { this->run(); });
}

void Thread::join() { thread_.join(); }

void Thread::yield() { std::this_thread::yield(); }

void Thread::sleep(size_t millis) {
    std::this_thread::sleep_for(std::chrono::milliseconds(millis));
}

void Thread::run() { assert(false); }

String* Thread::thread_id() {
    std::stringstream buf;
    buf << std::this_thread::get_id();
    std::string buffer(buf.str());
    return new String(buffer.c_str(), buffer.size());
}
