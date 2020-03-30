#include "../src/array.h"
#include "../src/columns.h"
#include "../src/dataframe.h"

int main() {
    ColumnArray* colArr = new ColumnArray();
    IntColumn* col = new IntColumn();
    col->push_back(5);
    colArr->append(col);
    Schema* schema = colArr->getSchema();
    DataFrame* df = new DataFrame(*schema);
    delete df;
    delete schema;
    delete colArr;
    return 0;
}