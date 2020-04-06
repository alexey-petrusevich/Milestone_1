#include "../../../include/eau2/dataframe/rowers/rower.h"

Rower::Rower(size_t colIndex) { this->colIndex = colIndex; }

void Rower::join_delete(Rower *other) {
    // empty to be used in the single threaded rower
}
