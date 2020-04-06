#include "../../include/eau2/dataframe/coltypes.h"

#include <cstring>

#include "../../include/eau2/sorer/helpers.h"

ColType infer_type(char* c) {
    // missing values
    if (c == nullptr) {
        return ColType::BOOLEAN;
    }
    // check boolean
    if (strlen(c) == 1) {
        if ((*c == '0') || (*c == '1')) {
            return ColType::BOOLEAN;
        }
    }
    // check int
    if (is_int(c)) {
        return ColType::INTEGER;
    }
    // check float
    if (is_float(c)) {
        return ColType::DOUBLE;
    }
    return ColType::STRING;
}
