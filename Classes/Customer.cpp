#include "Customer.h"

Customer::Customer() : id(0) {}

Customer::Customer(int id) : id(id) {}

MenuPosition Customer::order(const Menu& menu) {
    std::vector<MenuPosition> dishes = menu.getDishes();
    srand(time(0));
    int randomIndex = rand() % dishes.size();
    MenuPosition& randomDish = dishes[randomIndex];
    bill.addOrder(randomDish.recipe.getName(), randomDish.price);
    return randomDish;
}

int Customer::getId() const {
    return id;
}

void Customer::setTimer(double duration) {
    auto duration_in_seconds = std::chrono::duration<double>(duration);
    auto high_res_duration = std::chrono::duration_cast<std::chrono::high_resolution_clock::duration>(duration_in_seconds);

    timer = std::chrono::high_resolution_clock::now() + high_res_duration;
}

bool Customer::checkIfReady() const {
    return std::chrono::high_resolution_clock::now() >= timer;
}

double Customer::pay() {
    double total = bill.pay();
    return total;
}

bool Customer::operator==(const Customer& other) const {
    return id == other.id;
}