#pragma once
#include "helper.h"
#include <cstdlib>

/** Base class for all objects in the system.
 *  author: vitekj@me.com */
class Object : public Sys {
   public:
    size_t hash_;  // every object has a hash, subclasses must implement the
                   // functionality

    Object();

    /** Subclasses may have something to do on finalziation */
    virtual ~Object();

    /** Return the hash value of this object */
    size_t hash();

    /** Subclasses should redefine */
    virtual bool equals(Object* other);

    /** Return a copy of the object; nullptr is considered an error */
    virtual Object* clone();

    /** Compute the hash code (subclass responsibility) */
    virtual size_t hash_me();

    /** Returned c_str is owned by the object, don't modify nor delete. */
    virtual char* c_str();
};
