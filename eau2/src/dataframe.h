//lang::CwC
#pragma once

#include <cstdarg>
#include <iostream>
#include "visitors.h"
#include "visitors_implementaiton.h"
#include "columns.h"
#include "coltypes.h"
#include "object.h"
#include "string.h"
#include "fielder.h"
#include "array.h"
#include "schema.h"
#include "rower.h"
#include "thread.h"


/****************************************************************************
 * DataFrame::
 *
 * A DataFrame is table composed of columns of equal length. Each column
 * holds values of the same type (I, S, B, F). A dataframe has a schema that
 * describes it.
 */
class DataFrame : public Object {
public:
	Schema* schema; // owned
	ColumnArray* columns; // owned


	/** Create a data frame with the same columns as the give df but no rows.
	 *
	 * @param df data frame which schema is being used for creating
	 * this data frame
	 */
	DataFrame(DataFrame& df) {
		this->schema = new Schema(*(df.schema));
		this->schema->numRows = 0;
		this->initColumns();
	}


	/** Create a data frame from a schema and columns. Results are undefined if
	  * the columns do not match the schema.
	  *
	  * @param schema the schema being used for creating this dataframe
	  */
	DataFrame(Schema& schema) {
		this->schema = new Schema(schema);
		this->schema->numRows = 0;
		this->initColumns();
	}


	void initColumns() {
		this->columns = new ColumnArray(this->schema->numCols);
		for (size_t colIndex = 0; colIndex < this->schema->numCols; colIndex++) {
			switch (this->schema->col_type(colIndex)) {
			case INTEGER:
				this->columns->append(new IntColumn());
				break;
			case FLOAT:
				this->columns->append(new FloatColumn());
				break;
			case BOOLEAN:
				this->columns->append(new BoolColumn());
				break;
			case STRING:
				this->columns->append(new StringColumn());
				break;
			default:
				assert(false);
			}
		}
	}



	/** Returns the data frame's schema. Modifying the schema after a data frame
	  * has been created in undefined. */
	Schema& get_schema() {
		return *(this->schema);
	}


	/** Adds a column this data frame, updates the schema, the new column
	  * is external, and appears as the last column of the data frame, the
	  * name is optional and external. A nullptr column is undefined. */
	void add_column(Column* col, String* name) {
		assert(col != nullptr);
		// append new column to the array of columns
		this->columns->append(col);
		// update schema
		if (name != nullptr) {
			this->schema->add_column(col->get_type(), name);
		}
		else {
			this->schema->add_column(col->get_type(), nullptr);
		}
	}


	/** Return the value at the given column and row. Accessing rows or
	 *  columns out of bounds, or request the wrong type is undefined.*/
	 /**
	  * Returns the integer value of the given column and row index.
	  *
	  * @param col the column index of the requested element
	  * @param row the row index of the requested element
	  * @return the integer value of the requested element
	  */
	int get_int(size_t col, size_t row) {
		assert(col < this->schema->numCols);
		assert(row < this->schema->numRows);
		assert(this->schema->col_type(col) == INTEGER);
		IntColumn* intColumn = this->columns->get(col)->as_int();
		return intColumn->get(row);
	}


	/**
	 * Returns the boolean value of the given column and row index.
	 *
	 * @param col the column index of the requested element
	 * @param row the row index of the requested element
	 * @return the boolean value of the requested element
	 */
	bool get_bool(size_t col, size_t row) {
		assert(col < this->schema->numCols);
		assert(row < this->schema->numRows);
		assert(this->schema->col_type(col) == BOOLEAN);
		BoolColumn* boolColumn = this->columns->get(col)->as_bool();
		return boolColumn->get(row);
	}


	/**
	 * Returns the float value of the given column and row index.
	 *
	 * @param col the column index of the requested element
	 * @param row the row index of the requested element
	 * @return the float value of the requested element
	 */
	float get_float(size_t col, size_t row) {
		assert(col < this->schema->numCols);
		assert(row < this->schema->numRows);
		assert(this->schema->col_type(col) == FLOAT);
		FloatColumn* floatColumn = this->columns->get(col)->as_float();
		return floatColumn->get(row);
	}


	/**
	 * Returns the String value of the given column and row index.
	 *
	 * @param col the column index of the requested element
	 * @param row the row index of the requested element
	 * @return the String value of the requested element
	 */
	String* get_string(size_t col, size_t row) {
		assert(col < this->schema->numCols);
		assert(row < this->schema->numRows);
		assert(this->schema->col_type(col) == STRING);
		StringColumn* stringColumn = this->columns->get(col)->as_string();
		return stringColumn->get(row);
	}


	/** Return the offset of the given column name or -1 if no such col.
	 *
	 * @param the name of the column which offset is being returned
	 * @return the offset (index) of the column
	 */
	int get_col(String& col) {
		return this->schema->colNames->index(&col);
	}


	/** Return the offset of the given row name or -1 if no such row.
	 *
	 * @param col the name of the row which index is being returned
	 * @return the index of the requested row
	 */
	int get_row(String& row) {
		return this->schema->rowNames->index(&row);
	}


	/** Set the value at the given column and row to the given value.
	  * If the column is not  of the right type or the indices are out of
	  * bound, the result is undefined. */
	  /**
	   * Sets the value of the element at the given column and row index
	   * with the given integer.
	   *
	   * @param col the column index of the element
	   * @param row the row index of the element
	   * @param val the integer value of the element
	   */
	void set(size_t col, size_t row, int val) {
		assert(col < this->schema->numCols);
		assert(row < this->schema->numRows);
		assert(this->schema->col_type(col) == INTEGER);
		IntColumn* intColumn = this->columns->get(col)->as_int();
		intColumn->set(row, val);
	}


	/**
	 * Sets the value of the element at the given column and row index
	 * with the given boolean.
	 *
	 * @param col the column index of the element
	 * @param row the row index of the element
	 * @param val the boolean value of the element
	 */
	void set(size_t col, size_t row, bool val) {
		assert(col < this->schema->numCols);
		assert(row < this->schema->numRows);
		assert(this->schema->col_type(col) == BOOLEAN);
		BoolColumn* boolColumn = this->columns->get(col)->as_bool();
		boolColumn->set(row, val);
	}


	/**
	 * Sets the value of the element at the given column and row index
	 * with the given float.
	 *
	 * @param col the column index of the element
	 * @param row the row index of the element
	 * @param val the float value of the element
	 */
	void set(size_t col, size_t row, float val) {
		assert(col < this->schema->numCols);
		assert(row < this->schema->numRows);
		assert(this->schema->col_type(col) == FLOAT);
		FloatColumn* floatColumn = this->columns->get(col)->as_float();
		floatColumn->set(row, val);
	}


	/**
	 * Sets the value of the element at the given column and row index
	 * with the given String.
	 *
	 * @param col the column index of the element
	 * @param row the row index of the element
	 * @param val the String value of the element
	 */
	void set(size_t col, size_t row, String* val) {
		assert(col < this->schema->numCols);
		assert(row < this->schema->numRows);
		assert(this->schema->col_type(col) == STRING);
		StringColumn* stringColumn = this->columns->get(col)->as_string();
		stringColumn->set(row, val);
	}


	/** Set the fields of the given row object with values from the columns at
	  * the given offset.  If the row is not form the same schema as the
	  * data frame, results are undefined.
	  *
	  * @param idx the row index which values are being filled
	  * @param the row that is being used as a source of values
	  */
	void fill_row(size_t idx, Row& row) {
		assert(idx < this->schema->numRows);
		assert(row.schema->equals(this->schema));

		// new visitor that takes the pointer of the given Row and sets this row
		// at the given index
		IVisitor* visitor = new FillRowVisitor(&row);

		for (size_t colIndex = 0; colIndex < this->columns->size(); colIndex++) {
			// have visitor visit every column and set its values with the values of the given row
			this->columns->get(colIndex)->acceptVisitor(visitor);
		}
		delete visitor;
	}


	/** Add a row at the end of this data frame. The row is expected to have
	 *  the right schema and be filled with values, otherwise undefined.
	 *
	 *  @param row the new row being added to this data frame
	 */
	void add_row(Row& row) {
		assert(this->schema->equals(row.schema));

		// visitor that appends values from the row to the end of every column in this DataFrame
		IVisitor* visitor = new AddRowVisitor(&row);

		for (size_t colIndex = 0; colIndex < this->columns->size(); colIndex++) {
			// visit every row and append new value
			this->columns->get(colIndex)->acceptVisitor(visitor);
		}
		delete visitor;

		// update schema
		this->schema->numRows++;
		row.schema->numRows++;
		row.rowIndex++;
	}


	/** The number of rows in the data frame.
	 *
	 * @return the number of rows in this data frame
	 */
	size_t nrows() {
		return this->schema->numRows;
	}


	/** The number of columns in the data frame.
	 *
	 * @return the number of columns in this data frame
	 */
	size_t ncols() {
		return this->schema->numCols;
	}


	/** Visit rows in order. Cannot modify the structure of this DataFrame.
	 *
	 * @param r the rower used for iterating over rows of this data frame
	 */
	void map(Rower& r) {
		for (size_t rowIndex = 0; rowIndex < this->schema->numRows; rowIndex++) {
			Row row = Row(this->columns, rowIndex);
			r.accept(row);
		}
	}


	void sumValues(int* sum, size_t beginIndex, size_t endIndex) {
		for (size_t rowIndex = beginIndex; rowIndex < endIndex; rowIndex++) {
			*sum += ((IntColumn*)this->columns->get(0))->get(0);
		}
	}


	/**
	 * Uses map with multithreading. Sums the values of the given column.
	 *
	 * @param rower
	 */
	void pmap(Rower& rower) {

		// create threads
		size_t numThreads = 4;
		Thread** threads = new Thread * [numThreads];
		Rower** rowerClones = new Rower * [numThreads];

		for (size_t i = 0; i < numThreads; i++) {
			rowerClones[i] = dynamic_cast<Rower*>(rower.clone());
		}


		// 0. initialize threads
		for (size_t i = 0; i < numThreads; i++) {
			int beginRowIndex = i * this->schema->numRows / numThreads;
			int endRowIndex = (i + 1) * this->schema->numRows / numThreads;
				threads[i] = new HandleRowerThread(this->columns, rowerClones[i],
					beginRowIndex, endRowIndex);

			/*
			if (i == 0) {
				threads[i] = new HandleRowerThread(this->columns, rowerClones[i],
					i * this->schema->numRows / numThreads,
					(i + 1) * this->schema->numRows / numThreads);
			} else {
				threads[i] = new HandleRowerThread(this->columns, rowerClones[i],
					i * this->schema->numRows / numThreads + 1,
					(i + 1) * this->schema->numRows / numThreads);
			}
			*/
		}


		// 1. start threads
		for (size_t i = 0; i < numThreads; i++) {
			threads[i]->start();
		}


		// 2. join threads (wait until all threads are finished)
		for (size_t i = 0; i < numThreads; i++) {
			threads[i]->join();
		}


		// 3. join results
		for (size_t i = 0; i < numThreads - 1; i++) {
			rowerClones[0]->join_delete(rowerClones[i + 1]);
		}


		// 4. join results of the clone threads with the main rower
		rower.join_delete(rowerClones[0]);

		// 5. delete memory of threads
		delete[] threads;
	}


	/** Create a new dataframe, constructed from rows for which the given Rower
	  * returned true from its accept method.
	  *
	  * @param r rowers used for iterating over rows of this data frame
	  * @return the new dataframe created using the rower
	  */
	DataFrame* filter(Rower& r) {
		// create new data frame
		DataFrame* newDataFrame = new DataFrame(*this);

		// traverse through each row and if given Rower returns true,
		// add it to the new DataFrame.
		// The true/false value is determined by implementation of
		// the specific rower.
		for (size_t rowIndex = 0; this->schema->numRows; rowIndex++) {
			Row row = Row(this->columns, rowIndex);
			if (r.accept(row)) {
				newDataFrame->add_row(row);
			}
		}

		return newDataFrame;
	}


	/**
	* Destructor of this DataFrame.
	*/
	~DataFrame() {
		delete this->schema;
		delete this->columns;
	}

};
