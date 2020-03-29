//lang::CwC
#pragma once
#include "visitors.h"
#include "row.h"

/**
 * Represents implementation of IVisitor that visits Columns and sets them
 * with values stored in the given Row.
 */
class FillRowVisitor : public IVisitor {
public:
	Row* row;
	int colIndex; // int to comply with idx data type of IntCol set() method


	/**
	 * Constructor of this FillRowVisitor that accepts a given Row with data.
	 *
	 * @param row the Row containing data to be used for setting to various Columns
	 */
	FillRowVisitor(Row* row) {
		assert(row != nullptr);
		this->row = row;
		this->colIndex = 0;
	}


	virtual void visitIntColumn(IntColumn* intColumn) {
		assert(intColumn != nullptr);
		intColumn->set_int(colIndex, row->get_int(colIndex));
		colIndex++;
	}


	virtual void visitDoubleColumn(DoubleColumn* doubleColumn) {
		assert(doubleColumn != nullptr);
		doubleColumn->set_double(colIndex, row->get_double(colIndex));
		colIndex++;
	}


	virtual void visitBoolColumn(BoolColumn* booleanColumn) {
		assert(booleanColumn != nullptr);
		booleanColumn->set_bool(colIndex, row->get_bool(colIndex));
		colIndex++;
	}


	virtual void visitStringColumn(StringColumn* stringColumn) {
		assert(stringColumn != nullptr);
		stringColumn->set_string(colIndex, row->get_string(colIndex));
		colIndex++;
	}
};


/**
 * Represents a visitor that adds an extra entry to the given column.
 */
class AddRowVisitor : public IVisitor {
public:
	Row* row;
	int colIndex; // int to comply with idx data type of IntCol set() method


	/**
	 * Constructor of this AddRowVisitor that accepts a given Row with data.
	 *
	 * @param row the Row containing data to be used for setting to various Columns
	 */
	AddRowVisitor(Row* row) {
		assert(row != nullptr);
		this->row = row;
		this->colIndex = 0;
	}


	virtual void visitIntColumn(IntColumn* intColumn) {
		assert(intColumn != nullptr);
		intColumn->push_back(row->get_int(colIndex));
		colIndex++;
	}


	virtual void visitDoubleColumn(DoubleColumn* doubleColumn) {
		assert(doubleColumn != nullptr);
		doubleColumn->push_back(row->get_double(colIndex));
		colIndex++;
	}


	virtual void visitBoolColumn(BoolColumn* booleanColumn) {
		assert(booleanColumn != nullptr);
		booleanColumn->push_back(row->get_bool(colIndex));
		colIndex++;
	}


	virtual void visitStringColumn(StringColumn* stringColumn) {
		assert(stringColumn != nullptr);
		stringColumn->push_back(row->get_string(colIndex));
		colIndex++;
	}
};
