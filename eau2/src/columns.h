//lang::CwC
#pragma once

#include <cstdarg>
#include "object.h"
#include "string.h"
#include "array.h"
#include "fielder.h"
#include "schema.h"
#include "visitors.h"

/**
 * @brief This file represent implementation of Column class and its derivatives.
 * @file columns.h
 * @author Aliaksei Petrusevich <petrusevich.a@husky.neu.edu>
 * @author Megha Rao <rao.m@husky.neu.edu>
 * @date February 15, 2020
 */


class IntColumn;
class DoubleColumn;
class BoolColumn;
class StringColumn;


/**
 * Represents a visitor class that visits various implementations of Column class.
 */
class IVisitor : public Object {
public:

	/**
	 * Visits the IntColumn.
	 *
	 * @param intColumn the given IntColumn
	 */
	virtual void visitIntColumn(IntColumn* intColumn) {
		assert(false);
	}


	/**
	 * Visits the DoubleColumn.
	 *
	 * @param doubleColumn the given DoubleColumn
	 */
	virtual void visitDoubleColumn(DoubleColumn* doubleColumn) {
		assert(false);
	}

	/**
	 * Visits the BooleanColumn.
	 *
	 * @param booleanColumn the given BooleanColumn
	 */
	virtual void visitBoolColumn(BoolColumn* booleanColumn) {
		assert(false);
	}

	/**
	 * Visits the StringColumn.
	 *
	 * @param stringColumn the given StringColumn
	 */
	virtual void visitStringColumn(StringColumn* stringColumn) {
		assert(false);
	}
};



/**************************************************************************
 * Column ::
 *
 * Represents one column of a data frame which holds values of a single type.
 * This abstract class defines methods overriden in subclasses. There is
 * one subclass per element type. Columns are mutable, equality is pointer
 * equality. */
class Column : public Object {
public:
	size_t numElements;
	ColType colType;


	/**
	 * Default constructor of the column.
	 */
	Column(ColType colType) : Object() {
		this->colType = colType;
		this->numElements = 0;
	}


	/** Type converters: Return the same column under its actual type, or
	 *  nullptr if of the wrong type.  */
	 /**
	  * Returns this column as IntColumn.
	  *
	  * @return this column as IntColumn
	  */
	virtual IntColumn* as_int() {
		return nullptr;
	}


	/**
	 * Returns this column as BoolColumn.
	 *
	 * @return this column as BoolColumn
	 */
	virtual BoolColumn* as_bool() {
		return nullptr;
	}


	/**
	 * Returns this column as DoubleColumn.
	 *
	 * @return this column as DoubleColumn
	 */
	virtual DoubleColumn* as_double() {
		return nullptr;
	}


	/**
	 * Returns this column as StringColumn.
	 *
	 * @return this column as StringColumn
	 */
	virtual StringColumn* as_string() {
		return nullptr;
	}


	/** Type appropriate push_back methods. Calling the wrong method is
	  * undefined behavior. **/
	  /**
	   * Pushes the given integer value to the bottom of this column.
	   *
	   * @param val the integer value being pushed to the bottom of this column
	   */
	virtual void push_back(int val) {
		assert(false);
	}


	/**
	 * Pushes the given boolean value to the bottom of this column.
	 *
	 * @param val the boolean value being pushed to the bottom of this column
	 */
	virtual void push_back(bool val) {
		assert(false);
	}


	/**
	 * Pushes the given double value to the bottom of this column.
	 *
	 * @param val the double value being pushed to the bottom of this column
	 */
	virtual void push_back(double val) {
		assert(false);
	}


	/**
	 * Pushes the given String value to the bottom of this column.
	 *
	 * @param val the String value being pushed to the bottom of this column
	 */
	virtual void push_back(String* val) {
		assert(false);
	}


	/** Returns the number of elements in the column.
	 * @return the number of elements in this column
	 */
	virtual size_t size() {
		return this->numElements;
	}


	/**
	 * Return the type of this column as a char: 'S', 'B', 'I' and 'F'.
	 *
	 * @return the type of this column
	 */
	char get_type() {
		return this->colType;
	}

	/**
	 * Accepts a visitor and call the corresponding accept
	 * method based on the type of the column.
	 *
	 * @param f fielder being used for traversal
	 */
	virtual void acceptVisitor(IVisitor* visitor) = 0;


	/**
	 * Accepts a Fielder and calls 'accept' method of the corresponding
	 * column.
	 *
	 * @param f the given Fielder
	 */
	virtual void accept(Fielder* f) = 0;


	/**
	 * Destructor of this column.
	 */
	virtual ~Column() {
	}

};


/*************************************************************************
 * IntColumn::
 * Holds primitive int values, unwrapped.
 */
class IntColumn : public Column {
public:
	IntArray* array;


	/**
	 * Default constructor for this IntColumn.
	 */
	IntColumn() : Column(INTEGER) {
		this->array = new IntArray();
	}


	/**
	 * Constructor that accepts the number of parameters, a list of values,
	 * and stores this list of values in this IntColumn.
	 *
	 * @param n the number of values in the list
	 * @param ... the list of values to be stored in this IntColumn
	 */
	IntColumn(int n, ...) : Column(INTEGER) {
		this->array = new IntArray(n);
		va_list list;
		va_start(list, n);
		for (int i = 0; i < n; i++) {
			int val = va_arg(list, int);
			this->array->append(val);
		}
	}


	/**
	 * Returns the element at the given index.
	 *
	 * @param idx the index of the element in the IntArray
	 * @return the value of the element at the given index
	 */
	int get(size_t idx) {
		assert(idx < this->numElements);
		return this->array->get(idx);
	}


	IntColumn* as_int() {
		return this;
	}


	/**
	 * Sets the value of the element at the given element with the new value.
	 *
	 * @param idx the index of the element being set with the new value
	 * @param val the value of the new element
	 */
	void set(size_t idx, int val) {
		assert(idx < this->numElements);
		this->array->set(idx, val);
	}


	void push_back(int val) {
		this->array->append(val);
		this->numElements++;
	}


	void acceptVisitor(IVisitor* visitor) {
		assert(visitor != nullptr);
		visitor->visitIntColumn(this);
	}


	void accept(Fielder* f) {
		assert(f != nullptr);
		f->accept(this->array->get(f->rowIndex));
	}


	/**
	 * Destructor of IntColumn.
	 */
	~IntColumn() {
		delete this->array;
	}
};


/**
 * Represents a column of double type.
 */
class DoubleColumn : public Column {
public:
	DoubleArray* array;


	/**
	 * Default constructor of this DoubleColumn.
	 */
	DoubleColumn() : Column(DOUBLE) {
		this->array = new DoubleArray();
	}


	/**
	 * Constructor that accepts the number of elements and the list of elements
	 * to be stored in this column.
	 *
	 * @param n the number of parameters
	 * @param ... the list of elements to be stored in this column
	 */
	DoubleColumn(int n, ...) : Column(DOUBLE) {
		this->array = new DoubleArray(n);
		va_list list;
		va_start(list, n);
		for (int i = 0; i < n; i++) {
			double val = va_arg(list, double);
			this->array->append(val);
		}
	}


	/**
	 * Returns the element at the given index.
	 *
	 * @param idx the index of the element being returned
	 * @return the value of the element at the given index
	 */
	double get(size_t idx) {
		assert(idx < this->numElements);
		return this->array->get(idx);
	}


	DoubleColumn* as_double() {
		return this;
	}


	/**
	 * Sets the element at the given index with the new value.
	 *
	 * @param idx the index of the value being set
	 * @param val the new value of the element at the given index
	 */
	void set(size_t idx, double val) {
		assert(idx < this->numElements);
		this->array->set(idx, val);
	}


	void push_back(double val) {
		this->array->append(val);
		this->numElements++;
	}


	void acceptVisitor(IVisitor* visitor) {
		assert(visitor != nullptr);
		visitor->visitDoubleColumn(this);
	}


	void accept(Fielder* f) {
		assert(f != nullptr);
		f->accept(this->array->get(f->rowIndex));
	}


	/**
	 * Destructor of this column.
	 */
	~DoubleColumn() {
		delete[] this->array;
	}
};


/**
 * Represents a column of bool type.
 */
class BoolColumn : public Column {
public:
	BoolArray* array;


	/**
	 * Default constructor of this BoolColumn.
	 */
	BoolColumn() : Column(BOOLEAN) {
		this->array = new BoolArray();
	}


	/**
	 * Constructor that accepts the number of elements and the list of elements
	 * to be stored in this column.
	 *
	 * @param n the number of parameters
	 * @param ... the list of elements to be stored in this column
	 */
	BoolColumn(int n, ...) : Column(BOOLEAN) {
		this->array = new BoolArray(n);
		va_list list;
		va_start(list, n);
		for (int i = 0; i < n; i++) {
			bool val = va_arg(list, int);
			this->array->append(val);
		}
	}


	/**
	 * Returns the element at the given index.
	 *
	 * @param idx the index of the element being returned
	 * @return the value of the element at the given index
	 */
	bool get(size_t idx) {
		assert(idx < this->numElements);
		return this->array->get(idx);
	}


	BoolColumn* as_bool() {
		return this;
	}


	/**
	 * Sets the element at the given index with the new value.
	 *
	 * @param idx the index of the value being set
	 * @param val the new value of the element at the given index
	 */
	void set(size_t idx, bool val) {
		assert(idx < this->numElements);
		this->array->set(idx, val);
	}


	void push_back(bool val) {
		this->array->append(val);
		this->numElements++;
	}


	void acceptVisitor(IVisitor* visitor) {
		assert(visitor != nullptr);
		visitor->visitBoolColumn(this);
	}


	void accept(Fielder* f) {
		assert(f != nullptr);
		f->accept(this->array->get(f->rowIndex));
	}


	/**
	 * Destructor of this column.
	 */
	~BoolColumn() {
		delete[] this->array;
	}
};


/*************************************************************************
 * StringColumn::
 * Holds string pointers. The strings are external.  Nullptr is a valid
 * val.
 */
class StringColumn : public Column {
public:
	Array* array;


	/**
	 * Default constructor of this column that uses DEFAULT_COL_SIZE
	 * as default size of the array.
	 */
	StringColumn() : Column(STRING) {
		this->array = new Array();
	}


	/**
	 * Constructor that accepts the number of values, a list of values,
	 * and stored the given values in this column.
	 *
	 * @param n number of elements to be inserted
	 * @param ... the list of values to be inserted
	 */
	StringColumn(int n, ...) : Column(STRING) {
		this->array = new Array(n);
		va_list list;
		va_start(list, n);
		for (int i = 0; i < n; i++) {
			this->array->append(va_arg(list, String*));
		}
	}


	/**
	 * Returns the element at the given index.
	 *
	 * @param idx the index of the element to be returned
	 * @return the value of the element at the given index
	 */
	String* get(size_t idx) {
		assert(idx < this->numElements);
		return dynamic_cast<String*>(this->array->get(idx));
	}


	StringColumn* as_string() {
		return this;
	}


	/**
	 * Sets the value of the element at the given index with the new value.
	 * Acquires ownership of the given String.
	 *
	 * @param idx the index of the element being set
	 * @param val the new value of the element at the given index
	 */
	void set(size_t idx, String* val) {
		assert(idx < this->numElements);
		this->array->set(idx, val);
	}


	void push_back(String* val) {
		this->array->append(val);
		this->numElements++;
	}


	void acceptVisitor(IVisitor* visitor) {
		assert(visitor != nullptr);
		visitor->visitStringColumn(this);
	}


	void accept(Fielder* f) {
		assert(f != nullptr);
		f->accept(this->array->get(f->rowIndex));
	}


	/**
	 * Destructor of this StringColumn.
	 */
	~StringColumn() {
		delete[] this->array;
	}
};



/**
 * Represents an array of Columns.
 */
class ColumnArray : public Object {
public:
	Column** array;
	int elementsInserted;
	int capacity;
	int currentPosition;


	/**
	 * Default constructor for the array.
	 */
	ColumnArray() : Object() {
		this->array = new Column * [DEFAULT_SIZE];
		this->capacity = DEFAULT_SIZE;
		this->elementsInserted = 0;
		this->currentPosition = 0;
	}


	/**
	 * Array with custom capacity.
	 *
	 * @param size the capacity of the array
	 */
	ColumnArray(int size) : Object() {
		assert(size > 0);
		this->array = new Column * [size];
		this->capacity = size;
		this->elementsInserted = 0;
		this->currentPosition = 0;
	}


	/**
	 * Appends the given element to the end of this array.
	 *
	 * @param input the element being appended to the end of this ColumnArray.
	 */
	void append(Column* input) {
		assert(input != nullptr);
		this->_ensure_size(this->elementsInserted + 1);
		this->array[currentPosition] = input;
		this->currentPosition++;
		this->elementsInserted++;
	}


	/**
	 * Returns the element at the given index.
	 *
	 * @param index the index of the element in this ColumnArray.
	 * @return the element at the given index
	 */
	Column* get(int index) {
		assert(index < this->elementsInserted);
		return this->array[index];
	}


	/**
	 * Returns the size of this ColumnArray.
	 *
	 * @return the size of this ColumnArray
	 */
	int size() {
		return this->elementsInserted;
	}


	/**
	 * Returns the index of the first element with the given value. Returns
	 * -1 if value is not found.
	 *
	 * @param input the value of the element being searched for
	 * @return the index of the element in this ColumnArray
	 */
	int index(Column* input) {
		assert(input != nullptr);
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
	Column* set(int index, Column* input) {
		assert(index < this->elementsInserted);
		assert(input != nullptr);
		Column* temp = this->array[index];
		this->array[index] = input;
		return temp;
	}


	bool equals(Object* o) {
		assert(o != nullptr);
		ColumnArray* otherArray = dynamic_cast<ColumnArray*>(o);
		if (otherArray == nullptr) {
			return false;
		}
		// check if sizes are the same
		if (this->size() != otherArray->size()) {
			return false;
		}
		// check every element
		for (int index = 0; index < this->size(); index++) {
			if (!(this->array[index]->equals(otherArray->array[index]))) {
				return false;
			}
		}
		return true;
	}


	size_t hash() {
		size_t thisHash = 0;
		for (int i = 0; i < this->elementsInserted; i++) {
			thisHash += this->array[i]->hash();
		}
		return thisHash;
	}


	/**
	 * Checks whether the given capacity is larger than the capacity
	 * of this ColumnArray. Increases the size if required capacity is larger
	 * then the existing capacity.
	 *
	 * @param required the required capacity
	 */
	void _ensure_size(int required) {
		assert(required > 0);
		if (required > this->capacity) {
			int newCapacity = required * 2;
			Column** newArray = new Column * [newCapacity];
			Column** oldArray = this->array;
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
	 * Returns a Schema of this ColumnArray.
	 *
	 * @return the Schema of this ColumnArray
	 */
	Schema* getSchema() {
		Schema* schema = new Schema();
		for (int colIndex = 0; colIndex < this->elementsInserted; colIndex++) {
			schema->add_col_type(this->array[colIndex]->colType);
		}
		return schema;
	}


	/**
	 * The destructor of this Column array.
	 */
	~ColumnArray() {
		delete[] this->array;
	}
};
