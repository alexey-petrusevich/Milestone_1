// A1: Part 2
// lang: CwC

#pragma once
#include "object.h"
#include <assert.h>

/**
 * Represents a key value pair for a map.
 */
class KeyValue: public Object {
	public:
		Object* key;
		Object* value;

		KeyValue(Object* k, Object* v) : Object() {
			// Constructor for KeyValue pair
			this->key = k;
			this->value = v;
		}

		~KeyValue() {
			// Destructor for KeyValue pair
		}

		// Gets the key of the pair
		Object* getKey() {
			return this->key;
		}

		// Gets the value of the pair
		Object* getValue() {
			return this->value;
		}

		bool equals(Object* o) {
			assert(o != nullptr);
			KeyValue* otherKV = dynamic_cast<KeyValue*>(o);
			if (otherKV == nullptr) {
				return false;
			}
			return this->key->equals(otherKV->getKey())
								&& this->value->equals(otherKV->getValue());
		}

		size_t hash() {
			return this->key->hash() + this->value->hash();
		}
};
