#include "../../include/eau2/dataframe/fielders/fielder.h"

#include <cassert>

Fielder::Fielder() : Object() {}

void Fielder::start(size_t r) { this->rowIndex = r; }

void Fielder::accept(bool b) { assert(false); }

void Fielder::accept(double d) { assert(false); }

void Fielder::accept(int i) { assert(false); }

void Fielder::accept(String *s) { assert(false); }

Fielder::~Fielder() {}
