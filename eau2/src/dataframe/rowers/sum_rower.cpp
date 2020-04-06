#include "../../include/eau2/dataframe/rowers/sum_rower.h"

SumRower::SumRower(size_t colIndex) : Rower(colIndex) {}

bool SumRower::accept(Row &r) {
    assert(this->colIndex < r.width());
    size_t val = static_cast<size_t>(
        dynamic_cast<IntColumn *>(r.columnArray->get(this->colIndex))
            ->get_int(r.rowIndex));
    sum += val;
    return false;
}

SumRower::~SumRower() {}
