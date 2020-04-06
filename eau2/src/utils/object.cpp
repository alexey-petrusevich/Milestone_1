#include "../../include/eau2/utils/object.h"

Object::Object() { hash_ = 0; }

Object::~Object() {}

size_t Object::hash() { return hash_ != 0 ? hash_ : hash_ = hash_me(); }

bool Object::equals(Object* other) { return this == other; }

Object* Object::clone() { return nullptr; }

size_t Object::hash_me() { return 1; };

char* Object::c_str() { return nullptr; }
