#include "Supplier.h"

Supplier::Supplier(std::string l, std::string h) : Person(std::move(l), std::move(h)) {}