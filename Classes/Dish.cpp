#include "Dish.h"

Dish::Dish(Recipe* recipe, Customer customer) : recipe(recipe), customer(customer){}

void Dish::setTimer(double duration) {
    auto duration_in_seconds = std::chrono::duration<double>(duration);
    auto high_res_duration = std::chrono::duration_cast<std::chrono::high_resolution_clock::duration>(duration_in_seconds);

    timer = std::chrono::high_resolution_clock::now() + high_res_duration;
}

bool Dish::checkIfReady() {
    return std::chrono::high_resolution_clock::now() >= timer;
}

Recipe* Dish::getRecipe() const {
    return recipe;
}

Customer Dish::getCustomer() const {
    return customer;
}