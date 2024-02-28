#include "ifood.h"

#include <string>

std::unique_ptr<IFood> IFood::create() {
    return nullptr;
}


std::string Banana::name() {
    return "Banana";
}

std::unique_ptr<IFood> Banana::create() {
    return std::make_unique<Banana>();
}


std::string Pizza::name() {
    return "Pizza";
}

std::unique_ptr<IFood> Pizza::create() {
    return std::make_unique<Pizza>();
}
