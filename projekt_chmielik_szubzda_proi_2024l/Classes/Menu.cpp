#include "Menu.h"

void Menu::addRecipe(const Recipe& recipe, const double price) {
    dishes.push_back(MenuPosition(recipe, price));
}

double Menu::getPrice(const std::string& dishName) const {
    auto it = std::find_if(dishes.begin(), dishes.end(), [&dishName](const MenuPosition& position) {
        return position.recipe.getName() == dishName;
    });

    if (it != dishes.end()) {
        return it->price;
    } else {
        throw std::runtime_error("Dish not found in menu");
    }
}

Recipe Menu::getRecipe(const std::string& dishName) const {
    auto it = std::find_if(dishes.begin(), dishes.end(), [&dishName](const MenuPosition& position) {
        return position.recipe.getName() == dishName;
    });

    if (it != dishes.end()) {
        return it->recipe;
    } else {
        throw std::runtime_error("Dish not found in menu");
    }
}

std::vector<MenuPosition> Menu::getDishes() const {
    return dishes;
}