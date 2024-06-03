#ifndef SHOP_H
#define SHOP_H

#include <map>
#include <string>
#include <stdexcept>
#include <vector>
#include "Ingredient.h"

class Shop {
private:
    std::vector<Ingredient> ingredients;
    double totalSpent;

public:
    Shop();
    void addIngredient(std::string name, double price);
    double buyIngredient(std::string name, int quantity);
    double getIngredientPrice(std::string name);
    Ingredient getIngredient(std::string name);
    double getTotalSpent();
};

#endif // SHOP_H