#include "../../../include/eau2/dataframe/handle_rower_thread.h"

HandleRowerThread::HandleRowerThread(ColumnArray *columnArray, Rower *rower,
                                     size_t beginRowIndex, size_t endRowIndex)
    : Thread() {
    assert(columnArray != nullptr);
    assert(rower != nullptr);
    assert(beginRowIndex <= endRowIndex);
    this->columnArray = columnArray;
    this->rower = rower;
    this->beginRowIndex = beginRowIndex;
    this->endRowIndex = endRowIndex;
}

void HandleRowerThread::run() {
    for (size_t rowIndex = this->beginRowIndex; rowIndex < this->endRowIndex;
         rowIndex++) {
        Row row = Row(this->columnArray, rowIndex);
        rower->accept(row);
    }
}
