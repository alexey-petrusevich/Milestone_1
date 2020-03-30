#include "../src/array.h"
#include "../src/columns.h"
#include "../src/dataframe.h"

int main() {
    ColumnArray* colArr = new ColumnArray();
    StringColumn* col = new StringColumn();
    col->push_back(new String("a"));
    colArr->append(col);
    Schema* schema = colArr->getSchema();
    DataFrame* df = new DataFrame(*schema);
    delete df;
    delete schema;
    delete colArr;
    //delete col;
    return 0;
}