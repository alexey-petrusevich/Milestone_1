#pragma once

#include "object.h"

/** An immutable string class that wraps a character array.
 * The character array is zero terminated. The size() of the
 * String does count the terminator character. Most operations
 * work by copy, but there are exceptions (this is mostly to support
 * large strings and avoid them being copied).
 *  author: vitekj@me.com */
class String : public Object {
   public:
    size_t size_;  // number of characters excluding terminate (\0)
    char* cstr_;   // owned; char array

    /** Build a string from a string constant */
    String(char const* cstr, size_t len);

    /** Builds a string from a char*, steal must be true, we do not copy!
     *  cstr must be allocated for len+1 and must be zero terminated. */
    String(bool steal, char* cstr, size_t len);

    String(char const* cstr);

    /** Build a string from another String */
    String(String& from);

    /** Delete the string */
    ~String();

    /** Return the number characters in the string (does not count the
     * terminator) */
    size_t size();

    /** Return the raw char*. The result should not be modified or freed. */
    char* c_str();

    /** Returns the character at index */
    char at(size_t index);

    /** Compare two strings. */
    bool equals(Object* other);

    /** Deep copy of this string */
    String* clone();

    /** This consumes cstr_, the String must be deleted next */
    char* steal();

    /** Compute a hash for this string. */
    size_t hash_me();
};
