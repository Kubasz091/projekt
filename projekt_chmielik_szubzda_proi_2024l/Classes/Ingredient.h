#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <string>

class Ingredient {
private:
    const std::string name;
    const double cost;
public:
    Ingredient(const std::string& name, double cost);
    const std::string& getName() const;
    double getCost() const;
};

#endif // INGREDIENT_H