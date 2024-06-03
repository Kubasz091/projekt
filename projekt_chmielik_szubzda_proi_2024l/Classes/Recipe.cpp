#include "Recipe.h"

Recipe::Recipe(const std::string& name, const std::vector<IngredientQuantity>& ingredients)
    : name(name), ingredients(ingredients) {}

double Recipe::calculateCost() const {
    double cost = 0.0;
    for (const auto& ingredientQuantity : ingredients) {
        cost += ingredientQuantity.ingredient.getCost() * ingredientQuantity.quantity;
    }
    return cost;
}

const std::string& Recipe::getName() const {
    return name;
}

const std::vector<IngredientQuantity>& Recipe::getIngredients() const {
    return ingredients;
}