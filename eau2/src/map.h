// lang: CwC

#pragma once
#include "object.h"
#include "keyvalue.h"
#include <cmath>
#include <cfloat>
#include <cstdlib>
#include <assert.h>

const static double LOAD_FACTOR = 0.75;
const static size_t DEFAULT_SIZE = 100;

/**
 * @brief Represents a map with keys and values.
 * @file map.h
 * @author Aliaksei Petrusevich and Megha Rao
 * @date January 28, 2020
 */
class Map: public Object {
	public:
		KeyValue** map; // owned

		size_t tableSize;
		size_t elementsInserted;
		

		/**
		 * Default constructor.
		 */
		Map() {
			this->createMap();
		}


		/**
		 * Default destructor.
		 */
		~Map() {
			this->clear();
			delete[] this->map;
		}

		
		/**
		 * Returns the number of elements inserted in this map.
		 *
		 * @return number of elements inserted in this map
		 */
		size_t length() {
			return this->elementsInserted;
		}


		/**
		 * Removes all entries from this map.
		 */
		void clear() {
			for (size_t index = 0; index < tableSize; index++) {
				if (this->map[index] != nullptr) {
					delete this->map[index];
					this->map[index] = nullptr;
				}
			}
			this->elementsInserted = 0;
		}


		/**
		 * Returns a value stored at the given key. If value is not found,
		 * return null.
		 *
		 * @param key the key used for searching the value
		 * @return the value stored at the given key
		 */
		Object* get(Object* key) {
			assert(key != nullptr);
			size_t position = this->findPosition(key);
			KeyValue* kv = this->map[position];
			return kv == nullptr ? kv : kv->getValue();
		}


		/**
		 * Sets the value at the given key. If value is not present, 
		 * adds the new value to the map.
		 *
		 * @param key the key used for searching the given vaue
		 * @param value the value being inserted into this map
		 */
		void set(Object* key, Object* value) {
			assert(key != nullptr);
			assert(value != nullptr);
			size_t position = this->findPosition(key);
			if (!this->containsKey(key)) {
				this->map[position] = new KeyValue(key, value);
				this->elementsInserted++;
				// check if rehashing required
				if (this->getLoadFactor() > LOAD_FACTOR) {
					this->rehash();
				}
			} else {
				this->map[position]->value = value;
			}
		}
		

		/**
		 * Removes the value from this map given the key associated
		 * with the value. If the key is not found, returns null.
		 *
		 * @param key the key being used for searching
		 * @return the value removed from this map
		 */
		Object* remove(Object* key) {
			assert(key != nullptr);
			if (this->containsKey(key)) {
				size_t position = this->findPosition(key);
				Object* value = this->map[position]->getValue();
				delete this->map[position];
				this->map[position] = nullptr;
				this->elementsInserted--;
				return value;
			}
			return nullptr;
		}


		/**
		 * Returns a collection of all keys in this map.
		 *
		 * @return the array of keys of this map
		 */
		Object** getKeys() {
			Object** keys = new Object*[this->elementsInserted];
			for (size_t index = 0, keyIndex = 0; index < this->tableSize; index++) {
				if (!this->isEmpty(index)) {
					keys[keyIndex] = this->map[index]->getKey();
					keyIndex++;
				}
			}
			return keys;
		}


		/**
		 * Returns all values stored in this map as an array.
		 *
		 * @return the array of all values of this map
		 */
		Object** getValues() {
			Object** values = new Object*[this->elementsInserted];
			for (size_t index = 0, valueIndex = 0; index < this->tableSize; index++) {
				if (!this->isEmpty(index)) {
					values[valueIndex] = this->map[index]->getValue();
					valueIndex++;
				}
			}
			return values;
		}


		/**
		 * Returns all the items stored in this map as an array
		 * of KeyValue objects.
		 *
		 * @return an array of all KeyValue objects stored in this array
		 */
		KeyValue** getItems() {
			KeyValue** items = new KeyValue*[elementsInserted];
			for (size_t index = 0, keyIndex = 0; index < this->tableSize; index++) {
				if (!this->isEmpty(index)) {
					items[keyIndex] = this->map[index];
					keyIndex++;
				}
			}
			return items;
		}


		bool equals(Object* o) {
			assert(o != nullptr);
			Map* otherMap = dynamic_cast<Map*>(o);
			if (otherMap == nullptr) {
				return false;
			}
			// if number of elements is different, maps are not equal
			bool result = this->length() == otherMap->length();
			if (!result) {
				return false;
			}
			// compare each non-empty element in the map
			for (size_t index = 0; index < this->tableSize; index++) {
				if (!this->isEmpty(index)) {
					Object* otherValue = otherMap->get(this->map[index]->getKey());
					if (!otherValue) {
						return false;
					}
					result = this->map[index]->getValue()->equals(otherValue);
					if (!result) {
						return false;
					}
				}
			}
			return true;
		}
		

		size_t hash() {
			size_t hashValue = 0;
			for (size_t index = 0; index < this->tableSize; index++) {
				if (!this->isEmpty(index)) {
					hashValue += this->map[index]->hash();
				}
			}
			return hashValue;
		}
		

		/**
		 * Returns a position of the given key in this map.
		 *
		 * @param the key being used for calculating the position in this map
		 * @return the position in this map
		 */
		size_t findPosition(Object* key) {
			assert(key != nullptr);
			size_t currentPosition = key->hash() % this->tableSize;
			return currentPosition;
		}

		
		/**
		 * Returns a load factor of this map.
		 *
		 * @return the load factor of this map
		 */
		double getLoadFactor() {
			return static_cast<double>(this->elementsInserted) / this->tableSize;
		}

		
		/**
		 * Rehashes this map if the load factor gets over threshold.
		 */
		void rehash() {
			double loadFactor = this->getLoadFactor();
			if (loadFactor > LOAD_FACTOR) {
				// double the size
				this->rehashHelp(this->tableSize * 2);
			}
		}
	

		/**
		 * A helper function for rehash() that rehashes all the values in
		 * this map given the size of the new map.
		 *
		 * @param newSize the size of the new map
		 */
		void rehashHelp(size_t newSize) {
			KeyValue** newKV = new KeyValue*[newSize];
			initMap(newKV, newSize);
			KeyValue** oldKV = this->map;
			size_t oldSize = this->tableSize;
			this->map = newKV;
			this->tableSize = newSize;
			// rehash indices of the elements
			for (size_t index = 0; index < oldSize; index++) {
				if (oldKV[index] != nullptr) {
					size_t newPosition = this->findPosition(oldKV[index]->getKey());
					this->map[newPosition] = oldKV[index];
				}
			}
			delete[] oldKV;
		}


		/**
		 * Returns if the given key is present in this map.
		 *
		 * @param key the key being checked
		 * @return bool true if the key is in this map and false otherwise
		 */
		bool containsKey(Object* key) {
			assert(key != nullptr);
			size_t position = this->findPosition(key);
			return this->map[position] != nullptr;
		}
		
		
		/**
		 * Returns true if the element at the given position is empty
		 * and false otherwise.
		 *
		 * @param the position in this map
		 * @return true if the position doesn't have an entry and false otherwise
		 */
		bool isEmpty(size_t pos) {
			assert(pos < this->tableSize);
			return this->map[pos] == nullptr;
		}


		/**
		 * Sets all the values of the given map to nullptr.
		 *
		 * @param map the given map
		 * @param tableSize the size of the given map
		 */
		void initMap(KeyValue** map, size_t tableSize) {
			assert(map != nullptr);
			for (size_t index = 0; index < tableSize; index++) {
				map[index] = nullptr;
			}
		}


		/**
		 * Creates this map with the default capacity and all empty
		 * entries set to nullptr.
		 */
		void createMap() {
			this->map = new KeyValue*[DEFAULT_SIZE];
			this->tableSize = DEFAULT_SIZE;
			this->initMap(this->map, this->tableSize);
			this->elementsInserted = 0;
		}
};