#include "Waiter.h"

void Waiter::takeOrderFromCustomer(int customerId) {
    customer = customerId;
}

void Waiter::takeDish(Dish* newDish) {
    dish = newDish;
}

int Waiter::getCurrentCustomer() {
    return customer;
}

Dish* Waiter::getCurrentDish() {
    return dish;
}

void Waiter::setTimer(double duration) {
    auto duration_in_seconds = std::chrono::duration<double>(duration);
    auto high_res_duration = std::chrono::duration_cast<std::chrono::high_resolution_clock::duration>(duration_in_seconds);

    timer = std::chrono::high_resolution_clock::now() + high_res_duration;
}

bool Waiter::checkIfReady() const {
    return std::chrono::high_resolution_clock::now() >= timer;
}

void Waiter::setCustomerPaying(bool paying) {
    customer_paying = paying;
}

bool Waiter::getCustomerPaying() const {
    return customer_paying;
}