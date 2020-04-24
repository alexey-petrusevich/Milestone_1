#include "../../../include/eau2/dataframe/rowers/parallel_multiply_rower.h"
#include "../../../include/eau2/dataframe/columns/int_column.h"

ParallelMultiplyRower::ParallelMultiplyRower(size_t colIndex,
                                             size_t beginRowIndex)
    : Rower(colIndex) {
    this->beginRowIndex = beginRowIndex;
}

bool ParallelMultiplyRower::accept(Row &r) {
    size_t val = static_cast<size_t>(
        dynamic_cast<IntColumn *>(r.columnArray->get(this->colIndex))
            ->get_int(r.rowIndex));
    product *= val;
    return false;
}

Object *ParallelMultiplyRower::clone() {
    return new ParallelMultiplyRower(this->colIndex, this->beginRowIndex);
}

void ParallelMultiplyRower::join_delete(Rower *other) {
    ParallelMultiplyRower *multiplyRower =
        dynamic_cast<ParallelMultiplyRower *>(other);
    if (multiplyRower != nullptr) {
        // multiply to this product and delete given rower
        this->product *= multiplyRower->product;
        delete multiplyRower;
    }
}

ParallelMultiplyRower::~ParallelMultiplyRower() {}
