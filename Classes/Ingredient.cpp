#include "Ingredient.h"

Ingredient::Ingredient(const std::string& name, double cost) : name(name), cost(cost) {}

const std::string& Ingredient::getName() const {
    return name;
}

double Ingredient::getCost() const {
    return cost;
}