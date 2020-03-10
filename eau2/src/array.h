//lang::CwC
#pragma once

#include "object.h"
#include "string.h"
#include "coltypes.h"
#include <assert.h>


/**
 * @brief This file implements Array and its derivatives as ArrayLists.
 * @file array.h
 * @author Aliaksei Petrusevich <petrusevich.a@husky.neu.edu>
 * @author Megha Rao <rao.m@husky.neu.edu>
 * @date February 15, 2020
 */


const static int DEFAULT_SIZE = 100;


/**
 * Represents an array of Objects. Allows insertion of null pointers as values.
 */
class Array : public Object {
public:
	Object** array;
	int elementsInserted;
	int capacity;
	int currentPosition;


	/**
	 * Default constructor for the array.
	 */
	Array() : Object() {
		this->array = new Object * [DEFAULT_SIZE];
		this->capacity = DEFAULT_SIZE;
		this->elementsInserted = 0;
		this->currentPosition = 0;
	}


	/**
	 * Array with custom capacity.
	 *
	 * @param size the capacity of the array
	 */
	Array(int size) : Object() {
		assert(size > 0);
		this->array = new Object * [size];
		this->capacity = size;
		this->elementsInserted = 0;
		this->currentPosition = 0;
	}


	/**
	 * Appends the given element to the end of this array.
	 *
	 * @param input the element being appended to the end of this Array.
	 */
	void append(Object* input) {
		this->_ensure_size(this->elementsInserted + 1);
		this->array[currentPosition] = input;
		this->currentPosition++;
		this->elementsInserted++;
	}


	/**
	 * Returns the element at the given index.
	 *
	 * @param index the index of the element in this Array.
	 * @return the element at the given index
	 */
	Object* get(int index) {
		assert(index < this->elementsInserted);
		return this->array[index];
	}


	/**
	 * Returns the size of this Array.
	 *
	 * @return the size of this Array
	 */
	int size() {
		return this->elementsInserted;
	}


	/**
	 * Returns the index of the first element with the given value. Returns
	 * -1 if value is not found.
	 *
	 * @param input the value of the element being searched for
	 * @return the index of the element in this Array
	 */
	int index(Object* input) {
		for (int index = 0; index < this->elementsInserted; index++) {
			// if both are null pointers
			if (this->array[index] == nullptr && input == nullptr) {
				return index;
			} // if neither are null pointers and they are equal
			if (this->array[index] != nullptr && input != nullptr
				&& this->array[index]->equals(input)) {
				return index;
			}
		}
		return -1;
	}


	/**
	 * Sets the value of the element at the given index with
	 * the given value.
	 *
	 * @param index the index of the item being set
	 * @param input new element being inserted at the given position
	 * @return the element displaced by the given element
	 */
	Object* set(int index, Object* input) {
		assert(index < this->elementsInserted);
		Object* current = this->array[index];
		this->array[index] = input;
		return current;
	}


	bool equals(Object* o) {
		Array* otherArray = dynamic_cast<Array*>(o);
		if (otherArray == nullptr) {
			return false;
		}
		// check if sizes are the same
		if (this->size() != otherArray->size()) {
			return false;
		}
		// check every element
		for (int index = 0; index < this->size(); index++) {
			// if any of elements is null but not both (XOR), elements are not the same
			if ((this->array[index] != nullptr) != (otherArray->array[index] != nullptr)) {
				return false;
			}
			// if both are not null pointers and are equal
			if (this->array[index] != nullptr && otherArray->array[index] != nullptr
				&& !(this->array[index]->equals(otherArray->array[index]))) {
				return false;
			}
			// otherwise both are whether null pointers or equal
		}
		return true;
	}


	size_t hash() {
		size_t thisHash = 0;
		for (int i = 0; i < this->elementsInserted; i++) {
			if (this->array[i] != nullptr) {
				thisHash += this->array[i]->hash();
			}
		}
		return thisHash;
	}


	/**
	 * Checks whether the given capacity is larger than the capacity
	 * of this Array. Increases the size if required capacity is larger
	 * then the existing capacity.
	 *
	 * @param required the required capacity
	 */
	void _ensure_size(int required) {
		assert(required > 0);
		if (required > this->capacity) {
			int newCapacity = required * 2;
			Object** newArray = new Object * [newCapacity];
			Object** oldArray = this->array;
			// copy array
			for (int index = 0; index < this->capacity; index++) {
				newArray[index] = oldArray[index];
			}
			this->array = newArray;
			this->capacity = newCapacity;
			delete[] oldArray;
		}
	}


	/**
	* The destructor of this Array.
	*/
	~Array() {
		for (int index = 0; index < this->elementsInserted; index++) {
			delete this->array[index];
		}
		delete[] this->array;
	}
};


/**
 * Represents an array of Integers. Does not allow null pointers.
 */
class IntArray : public Object {
public:
	int* array;
	int elementsInserted;
	int capacity;
	int currentPosition;


	/**
	 * Default constructor for the array.
	 */
	IntArray() : Object() {
		this->array = new int[DEFAULT_SIZE];
		this->capacity = DEFAULT_SIZE;
		this->elementsInserted = 0;
		this->currentPosition = 0;
	}


	/**
	 * Array with custom capacity.
	 *
	 * @param size the capacity of the array
	 */
	IntArray(int size) : Object() {
		assert(size > 0);
		this->array = new int[size];
		this->capacity = size;
		this->elementsInserted = 0;
		this->currentPosition = 0;
	}


	/**
	 * Appends the given element to the end of this array.
	 *
	 * @param input the element being appended to the end of this IntArray.
	 */
	void append(int &input) {
		this->_ensure_size(this->elementsInserted + 1);
		this->array[currentPosition] = input;
		this->currentPosition++;
		this->elementsInserted++;
	}


	/**
	 * Returns the element at the given index.
	 *
	 * @param index the index of the element in this IntArray.
	 * @return the element at the given index
	 */
	int get(int index) {
		assert(index < this->elementsInserted);
		return this->array[index];
	}


	/**
	 * Returns the size of this IntArray.
	 *
	 * @return the size of this IntArray
	 */
	int size() {
		return this->elementsInserted;
	}


	/**
	 * Returns the index of the first element with the given value. Returns
	 * -1 if value is not found.
	 *
	 * @param input the value of the element being searched for
	 * @return the index of the element in this IntArray
	 */
	int index(int &input) {
		for (int index = 0; index < this->elementsInserted; index++) {
			if (this->array[index] == input) {
				return index;
			}
		}
		return -1;
	}


	/**
	 * Sets the value of the element at the given index with
	 * the given value.
	 *
	 * @param index the index of the item being set
	 * @param input new element being inserted at the given position
	 * @return the element displaced by the given element
	 */
	int set(int index, int &input) {
		assert(index < this->elementsInserted);
		int current = this->array[index];
		this->array[index] = input;
		return current;
	}


	bool equals(Object* o) {
		IntArray* otherArray = dynamic_cast<IntArray*>(o);
		if (otherArray == nullptr) {
			return false;
		}
		if (this->size() != otherArray->size()) {
			return false;
		}
		for (int index = 0; index < this->size(); index++) {
			if (this->array[index] != otherArray->array[index]) {
				return false;
			}
		}
		return true;
	}


	size_t hash() {
		size_t thisHash = 0;
		for (int i = 0; i < this->elementsInserted; i++) {
			thisHash += this->array[i];
		}
		return thisHash;
	}


	/**
	 * Checks whether the given capacity is larger than the capacity
	 * of this IntArray. Increases the size if required capacity is larger
	 * then the existing capacity.
	 *
	 * @param required the required capacity
	 */
	void _ensure_size(int required) {
		assert(required > 0);
		if (required > this->capacity) {
			int newCapacity = required * 2;
			int* newArray = new int[newCapacity];
			int* oldArray = this->array;
			// copy array
			for (int index = 0; index < this->capacity; index++) {
				newArray[index] = oldArray[index];
			}
			this->array = newArray;
			this->capacity = newCapacity;

			delete[] oldArray;
		}
	}


	/**
	 * The destructor of this IntArray.
	 */
	~IntArray() {
		delete[] this->array;
	}
};


/**
 * Represents an array of floats. Does not allow null pointers.
 */
class FloatArray : public Object {
public:
	float* array;
	int elementsInserted;
	int capacity;
	int currentPosition;


	/**
	 * Default constructor for the array.
	 */
	FloatArray() : Object() {
		this->array = new float [DEFAULT_SIZE];
		this->capacity = DEFAULT_SIZE;
		this->elementsInserted = 0;
		this->currentPosition = 0;
	}


	/**
	 * Array with custom capacity.
	 *
	 * @param size the capacity of the array
	 */
	FloatArray(int size) : Object() {
		assert(size > 0);
		this->array = new float [size];
		this->capacity = size;
		this->elementsInserted = 0;
		this->currentPosition = 0;
	}


	/**
	 * Appends the given element to the end of this array.
	 *
	 * @param input the element being appended to the end of this FloatArray.
	 */
	void append(float input) {
		this->_ensure_size(this->elementsInserted + 1);
		this->array[currentPosition] = input;
		this->currentPosition++;
		this->elementsInserted++;
	}


	/**
	 * Returns the element at the given index.
	 *
	 * @param index the index of the element in this FloatArray.
	 * @return the element at the given index
	 */
	float get(int index) {
		assert(index < this->elementsInserted);
		return this->array[index];
	}


	/**
	 * Returns the size of this FloatArray.
	 *
	 * @return the size of this FloatArray
	 */
	int size() {
		return this->elementsInserted;
	}


	/**
	 * Returns the index of the first element with the given value. Returns
	 * -1 if value is not found.
	 *
	 * @param input the value of the element being searched for
	 * @return the index of the element in this FloatArray
	 */
	int index(float input) {
		for (int index = 0; index < this->elementsInserted; index++) {
			if (std::abs(this->array[index] - input) < 1E-14) {
				return index;
			}
		}
		return -1;
	}


	/**
	 * Sets the value of the element at the given index with
	 * the given value.
	 *
	 * @param index the index of the item being set
	 * @param input new element being inserted at the given position
	 * @return the element displaced by the given element
	 */
	float set(int index, float input) {
		assert(index < this->elementsInserted);
		float current = this->array[index];
		this->array[index] = input;
		return current;
	}


	bool equals(Object* o) {
		FloatArray* otherArray = dynamic_cast<FloatArray*>(o);
		if (otherArray == nullptr) {
			return false;
		}
		// check if sizes are the same
		if (this->size() != otherArray->size()) {
			return false;
		}
		// check every element
		for (int index = 0; index < this->size(); index++) {
			if (this->array[index] != otherArray->array[index]) {
				return false;
			}
		}
		return true;
	}


	size_t hash() {
		size_t thisHash = 0;
		for (int i = 0; i < this->elementsInserted; i++) {
			thisHash += static_cast<size_t>(this->array[i]);
		}
		return thisHash;
	}


	/**
	 * Checks whether the given capacity is larger than the capacity
	 * of this FloatArray. Increases the size if required capacity is larger
	 * then the existing capacity.
	 *
	 * @param required the required capacity
	 */
	void _ensure_size(int required) {
		assert(required > 0);
		if (required > this->capacity) {
			int newCapacity = required * 2;
			float* newArray = new float [newCapacity];
			float* oldArray = this->array;
			// copy array
			for (int index = 0; index < this->capacity; index++) {
				newArray[index] = oldArray[index];
			}
			this->array = newArray;
			this->capacity = newCapacity;
			this->capacity *= 2;
			delete[] oldArray;
		}
	}


	/**
	* The destructor of this FloatArray.
	*/
	~FloatArray() {
		delete[] this->array;
	}
};


/**
 * Represents an array of booleans. Does not allow null pointers.
 */
class BoolArray : public Object {
public:
	bool* array;
	int elementsInserted;
	int capacity;
	int currentPosition;


	/**
	 * Default constructor for the array.
	 */
	BoolArray() : Object() {
		this->array = new bool [DEFAULT_SIZE];
		this->capacity = DEFAULT_SIZE;
		this->elementsInserted = 0;
		this->currentPosition = 0;
	}


	/**
	 * Array with custom capacity.
	 *
	 * @param size the capacity of the array
	 */
	BoolArray(int size) : Object() {
		assert(size > 0);
		this->array = new bool [size];
		this->capacity = size;
		this->elementsInserted = 0;
		this->currentPosition = 0;
	}


	/**
	 * Appends the given element to the end of this array.
	 *
	 * @param input the element being appended to the end of this BoolArray.
	 */
	void append(bool input) {
		this->_ensure_size(this->elementsInserted + 1);
		this->array[currentPosition] = input;
		this->currentPosition++;
		this->elementsInserted++;
	}


	/**
	 * Returns the element at the given index.
	 *
	 * @param index the index of the element in this BoolArray.
	 * @return the element at the given index
	 */
	bool get(int index) {
		assert(index < this->elementsInserted);
		return this->array[index];
	}


	/**
	 * Returns the size of this BoolArray.
	 *
	 * @return the size of this BoolArray
	 */
	int size() {
		return this->elementsInserted;
	}


	/**
	 * Returns the index of the first element with the given value. Returns
	 * false if value is not found.
	 *
	 * @param input the value of the element being searched for
	 * @return the index of the element in this BoolArray
	 */
	int index(bool input) {
		for (int index = 0; index < this->elementsInserted; index++) {
			if (this->array[index] == input && index < this->currentPosition) {
				return index;
			}
		}
		return -1;
	}


	/**
	 * Sets the value of the element at the given index with
	 * the given value.
	 *
	 * @param index the index of the item being set
	 * @param input new element being inserted at the given position
	 * @return the element displaced by the given element
	 */
	bool set(int index, bool input) {
		assert(index < this->elementsInserted);
		bool current = this->array[index];
		this->array[index] = input;
		return current;
	}


	bool equals(Object* o) {
		BoolArray* otherArray = dynamic_cast<BoolArray*>(o);
		if (otherArray == nullptr) {
			return false;
		}
		// check if sizes are the same
		if (this->size() != otherArray->size()) {
			return false;
		}
		// check every element
		for (int index = 0; index < this->size(); index++) {
			if (this->array[index] != otherArray->array[index]) {
				return false;
			}
		}
		return true;
	}


	size_t hash() {
		size_t thisHash = 0;
		for (int i = 0; i < this->elementsInserted; i++) {
			thisHash += this->array[i] ? 1 : 0;
		}
		return thisHash;
	}


	/**
	 * Checks whether the given capacity is larger than the capacity
	 * of this BoolArray. Increases the size if required capacity is larger
	 * then the existing capacity.
	 *
	 * @param required the required capacity
	 */
	void _ensure_size(int required) {
		assert(required > 0);
		if (required > this->capacity) {
			int newCapacity = required * 2;
			bool* newArray = new bool [newCapacity];
			bool* oldArray = this->array;
			// copy array
			for (int index = 0; index < this->capacity; index++) {
				newArray[index] = oldArray[index];
			}
			this->array = newArray;
			this->capacity = newCapacity;
			delete[] oldArray;
		}
	}


	/**
	* The destructor of this BoolArray.
	*/
	~BoolArray() {
		delete[] this->array;
	}
};


/**
 * Represents an array of ColType enumerators.
 */
class ColTypeArray : public Object {
public:
	ColType* array;
	int elementsInserted;
	int capacity;
	int currentPosition;


	/**
	 * Default constructor for the array.
	 */
	ColTypeArray() : Object() {
		this->array = new ColType[DEFAULT_SIZE];
		this->capacity = DEFAULT_SIZE;
		this->elementsInserted = 0;
		this->currentPosition = 0;
	}


	/**
	 * Array with custom capacity.
	 *
	 * @param size the capacity of the array
	 */
	ColTypeArray(int size) : Object() {
		assert(size > 0);
		this->array = new ColType[size];
		this->capacity = size;
		this->elementsInserted = 0;
		this->currentPosition = 0;
	}


	/**
	 * Appends the given element to the end of this array.
	 *
	 * @param input the element being appended to the end of this ColTypeArray.
	 */
	void append(ColType input) {
		this->_ensure_size(this->elementsInserted + 1);
		this->array[currentPosition] = input;
		this->currentPosition++;
		this->elementsInserted++;
	}


	/**
	 * Appends the given element to the end of this array.
	 *
	 * @param input the element being appended to the end of this ColTypeArray.
	 */
	void append(char input) {
		this->_ensure_size(this->elementsInserted + 1);
		switch (input) {
		case INTEGER:
			this->append(INTEGER);
			break;
		case FLOAT:
			this->append(FLOAT);
			break;
		case BOOLEAN:
			this->append(BOOLEAN);
			break;
		case STRING:
			this->append(STRING);
			break;
		default:
			// unknown type
			assert(false);
		}
	}


	/**
	 * Returns the element at the given index.
	 *
	 * @param index the index of the element in this ColTypeArray.
	 * @return the element at the given index
	 */
	ColType get(int index) {
		assert(index < this->elementsInserted);
		return this->array[index];
	}


	/**
	 * Returns the size of this ColTypeArray.
	 *
	 * @return the size of this ColTypeArray
	 */
	int size() {
		return this->elementsInserted;
	}


	/**
	 * Returns the index of the first element with the given value. Returns
	 * -1 if value is not found.
	 *
	 * @param input the value of the element being searched for
	 * @return the index of the element in this array
	 */
	int index(ColType input) {
		for (int index = 0; index < this->elementsInserted; index++) {
			if (this->array[index] == input) {
				return index;
			}
		}
		return -1;
	}


	/**
	 * Returns the index of the first element with the given value. Returns
	 * -1 if value is not found.
	 *
	 * @param input the value of the element being searched for
	 * @return the index of the element in this ColTypeArray
	 */
	int index(char input) {
		switch (input) {
		case INTEGER:
			return this->index(INTEGER);
		case FLOAT:
			return this->index(FLOAT);
		case BOOLEAN:
			return this->index(BOOLEAN);
		case STRING:
			return this->index(STRING);
		default:
			// unknown type
			return -1;
		}
	}


	/**
	 * Sets the value of the element at the given index with
	 * the given value.
	 *
	 * @param index the index of the item being set
	 * @param input new element being inserted at the given position
	 * @return the element displaced by the given element
	 */
	ColType set(int index, ColType input) {
		assert(index < this->elementsInserted);
		ColType colType = this->get(index);
		this->array[index] = input;
		return colType;
	}


	bool equals(Object* o) {
		assert(o != nullptr);
		ColTypeArray* otherArray = dynamic_cast<ColTypeArray*>(o);
		if (otherArray == nullptr) {
			return false;
		}
		// check if sizes are the same
		if (this->size() != otherArray->size()) {
			return false;
		}
		// check every element
		for (int index = 0; index < this->size(); index++) {
			if (!(this->array[index] == otherArray->array[index])) {
				return false;
			}
		}
		return true;
	}


	size_t hash() {
		size_t thisHash = 0;
		for (int i = 0; i < this->elementsInserted; i++) {
			thisHash += static_cast<size_t>(this->array[i]);
		}
		return thisHash;
	}


	/**
	 * Checks whether the given capacity is larger than the capacity
	 * of this ColTypeArray. Increases the size if required capacity is larger
	 * then the existing capacity.
	 *
	 * @param required the required capacity
	 */
	void _ensure_size(int required) {
		assert(required > 0);
		if (required > this->capacity) {
			int newCapacity = required * 2;
			ColType* newArray = new ColType[newCapacity];
			ColType* oldArray = this->array;
			// copy array
			for (int index = 0; index < this->capacity; index++) {
				newArray[index] = oldArray[index];
			}
			this->array = newArray;
			this->capacity = newCapacity;
			delete[] oldArray;
		}
	}


	/**
	* The destructor of this ColTypeArray.
	*/
	~ColTypeArray() {
		delete[] this->array;
	}
};
