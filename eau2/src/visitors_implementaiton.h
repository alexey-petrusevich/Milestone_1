//lang::CwC
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
		intColumn->set(colIndex, row->get_int(colIndex));
		colIndex++;
	}


	virtual void visitFloatColumn(FloatColumn* floatColumn) {
		assert(floatColumn != nullptr);
		floatColumn->set(colIndex, row->get_float(colIndex));
		colIndex++;
	}


	virtual void visitBoolColumn(BoolColumn* booleanColumn) {
		assert(booleanColumn != nullptr);
		booleanColumn->set(colIndex, row->get_bool(colIndex));
		colIndex++;
	}


	virtual void visitStringColumn(StringColumn* stringColumn) {
		assert(stringColumn != nullptr);
		stringColumn->set(colIndex, row->get_string(colIndex));
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


	virtual void visitFloatColumn(FloatColumn* floatColumn) {
		assert(floatColumn != nullptr);
		floatColumn->push_back(row->get_float(colIndex));
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
