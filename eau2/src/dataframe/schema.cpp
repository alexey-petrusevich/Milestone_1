#include "../../include/eau2/dataframe/schema.h"

#include <cstring>

Schema::Schema(Schema &from) : Object() {
    this->numRows = from.numRows;
    this->numCols = from.numCols;

    // copy col types
    this->colTypes = new ColTypeArray();
    for (size_t colTypeIndex = 0; colTypeIndex < this->numCols;
         colTypeIndex++) {
        this->colTypes->append(from.col_type(colTypeIndex));
    }
}

Schema::Schema() : Object() {
    this->numRows = 0;
    this->numCols = 0;
    this->colTypes = new ColTypeArray();
}

Schema::Schema(const char *types) {
    assert(types != nullptr);
    this->numRows = 0;
    this->numCols = strlen(types);
    this->colTypes = new ColTypeArray(this->numCols);

    // add ColTypes to this Schema
    for (size_t i = 0; i < this->numCols; i++) {
        // appending a character of the unknown type produces assertion
        // error
        this->colTypes->append(types[i]);
    }
}

void Schema::add_column(char typ) {
    // appending the unknown type to types produces assertion error
    // may exit of 'typ' value is not one of the values defined in ColType
    // enumerator
    this->colTypes->append(typ);
    this->numCols++;
}

void Schema::add_col_type(ColType type) {
    this->colTypes->append(type);
    this->numCols++;
}

char Schema::col_type(size_t idx) {
    assert(idx < this->numCols);
    return static_cast<char>(this->colTypes->get(idx));
}

size_t Schema::width() { return this->numCols; }

size_t Schema::length() { return this->numRows; }

bool Schema::equals(Object *o) {
    Schema *otherSchema = dynamic_cast<Schema *>(o);
    if (otherSchema == nullptr) {
        return false;
    }
    return this->numCols == otherSchema->numCols &&
           this->numRows == otherSchema->numRows &&
           this->colTypes->equals(otherSchema->colTypes);
}

size_t Schema::hash() {
    return this->numCols + this->numRows + this->colTypes->hash();
}

Schema::~Schema() { delete this->colTypes; }
