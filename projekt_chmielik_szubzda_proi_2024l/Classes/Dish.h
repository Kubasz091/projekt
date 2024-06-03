#ifndef DISH_H
#define DISH_H

#include <chrono>
#include "Recipe.h"
#include "Customer.h"

class Dish {
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> timer;
    Recipe* recipe;
    Customer customer;

public:
    Dish(Recipe* recipe, Customer customer);
    void setTimer(double duration);
    bool checkIfReady();
    Recipe* getRecipe() const;
    Customer getCustomer() const;
};

#endif // DISH_H