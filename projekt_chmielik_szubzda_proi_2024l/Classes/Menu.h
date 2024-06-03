#ifndef MENU_H
#define MENU_H

#include <vector>
#include <map>
#include <stdexcept>
#include "Recipe.h"

struct MenuPosition {
    Recipe recipe;
    double price;

    MenuPosition(const Recipe& recipe, double price)
        : recipe(recipe), price(price) {}
};

class Menu {
private:
    std::vector<MenuPosition> dishes;
public:
    void addRecipe(const Recipe& recipe, const double price);
    double getPrice(const std::string& dishName) const;
    Recipe getRecipe(const std::string& dishName) const;

    std::vector<MenuPosition> getDishes() const;
};

#endif // MENU_H