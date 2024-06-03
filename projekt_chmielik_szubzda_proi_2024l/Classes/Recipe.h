#ifndef RECIPE_H
#define RECIPE_H

#include <vector>
#include <string>
#include "Ingredient.h"

struct IngredientQuantity {
    const Ingredient ingredient;
    const int quantity;

    IngredientQuantity(const Ingredient& ingredient, int quantity)
        : ingredient(ingredient), quantity(quantity) {}
};

class Recipe {
private:
    const std::string name;
    const std::vector<IngredientQuantity> ingredients;
public:
    Recipe(const std::string& name, const std::vector<IngredientQuantity>& ingredients);
    double calculateCost() const;
    const std::string& getName() const;
    const std::vector<IngredientQuantity>& getIngredients() const;
};

#endif // RECIPE_H