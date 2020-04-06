#include "../../../include/eau2/dataframe/rowers/parallel_sum_rower.h"

ParallelSumRower::ParallelSumRower(size_t colIndex, size_t beginRowIndex)
    : Rower(colIndex) {
    this->beginRowIndex = beginRowIndex;
}

bool ParallelSumRower::accept(Row &r) {
    int val = dynamic_cast<IntColumn *>(r.columnArray->get(this->colIndex))
                  ->get_int(r.rowIndex);
    sum += val;
    return false;
}

Object *ParallelSumRower::clone() {
    return new ParallelSumRower(this->colIndex, this->beginRowIndex);
}

void ParallelSumRower::join_delete(Rower *other) {
    ParallelSumRower *sumRower = dynamic_cast<ParallelSumRower *>(other);
    if (sumRower != nullptr) {
        // add to this sum and delete given rower this->sum +=
        size_t otherSum = sumRower->sum;
        this->sum += otherSum;
        delete sumRower;
    }
}

ParallelSumRower::~ParallelSumRower() {}
