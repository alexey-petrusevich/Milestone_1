#include "../../../include/eau2/dataframe/rowers/multiply_rower.h"

MultiplyRower::MultiplyRower(size_t colIndex) : Rower(colIndex) {}

bool MultiplyRower::accept(Row &r) {
    assert(this->colIndex < r.width());
    size_t val = static_cast<size_t>(
        dynamic_cast<IntColumn *>(r.columnArray->get(this->colIndex))
            ->get_int(r.rowIndex));
    product *= val;
    return false;
}

MultiplyRower::~MultiplyRower() {}
