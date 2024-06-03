#include <iostream>
#include <random>
#include "spdlog/spdlog.h"
#include "Restaurant.h"

Restaurant::Restaurant( int num_Cooks, double starting_money) : kitchen(num_Cooks, starting_money) {
    auto duration_in_seconds = std::chrono::duration<double>(clientSpawnDelay);
    auto high_res_duration = std::chrono::duration_cast<std::chrono::high_resolution_clock::duration>(duration_in_seconds);
    timerNextCustomer = std::chrono::high_resolution_clock::now() + high_res_duration; // czas do pojawienia się pierwszego klienta
}

void Restaurant::setParameters(double clientSpawnDelay, double orderPrepareDelay, double waiterWalkDelay, double customerEatDelay, double customerOrderDelay) {
    this->clientSpawnDelay = clientSpawnDelay;
    this->orderPrepareDelay = orderPrepareDelay;
    this->waiterWalkDelay = waiterWalkDelay;
    this->customerEatDelay = customerEatDelay;
    this->customerOrderDelay = customerOrderDelay;
}

void Restaurant::spawnCustomer() {
    for (auto& table : tables) {
        if (!table.isOccupied()) {
            Customer customer(customers_spawned);
            customers_spawned++;
            table.seatCustomer(customer);
            customersWaitingForOrder.push_back(customer);
            customers.push_back(customer);
            customer.setTimer(customerOrderDelay);
            spdlog::info("Customer {} spawned, gonna order in {} seconds", customer.getId(), customerOrderDelay);
            break;
        }
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.7, 1.3);
    auto time_step = clientSpawnDelay;
    time_step *= dis(gen);
    auto duration_in_seconds = std::chrono::duration<double>(time_step);
    auto high_res_duration = std::chrono::duration_cast<std::chrono::high_resolution_clock::duration>(duration_in_seconds);
    timerNextCustomer = std::chrono::high_resolution_clock::now() + high_res_duration;
}

void Restaurant::addWaiter(const Waiter& waiter) {
    waiters.push_back(waiter);
}

void Restaurant::addTable(const Table& table) {
    tables.push_back(table);
}

void Restaurant::addRecipeToMenu(const Recipe& recipe, double price) {
    menu.addRecipe(recipe, price);
}

Kitchen& Restaurant::getKitchen() {
    return kitchen;
}

void Restaurant::handleLogic() {
    if (timerNextCustomer <= std::chrono::high_resolution_clock::now()) {
        spawnCustomer(); // Poprawiono literówkę
    }

    if (!ordersToServe.empty()) {
        for (auto& waiter : waiters) {
            if (waiter.getCurrentDish() == nullptr && waiter.checkIfReady() && waiter.getCurrentCustomer() == 0 && !ordersToServe.empty()) {
                Dish& dish = ordersToServe.front();
                waiter.takeDish(&dish);
                ordersToServe.pop();
                waiter.setTimer(waiterWalkDelay);
                waiter.setCustomerPaying(false);
                spdlog::info("Waiter walking towards customer {} with order: {}", dish.getCustomer().getId(), dish.getRecipe()->getName());
                break; // Dodano break, aby tylko jeden kelner wziął danie
            }
        }
    }

    // Handle customers waiting for order
    for (auto it = customersWaitingForOrder.begin(); it != customersWaitingForOrder.end();) {
        if (it->checkIfReady()) {
            for (auto& waiter : waiters) {
                if (waiter.getCurrentDish() == nullptr && waiter.checkIfReady() && waiter.getCurrentCustomer() == 0) {
                    waiter.takeOrderFromCustomer(it->getId());
                    waiter.setTimer(waiterWalkDelay);
                    waiter.setCustomerPaying(false);
                    spdlog::info("Waiter walking to customer {} to take order", it->getId());
                    it = customersWaitingForOrder.erase(it);
                    break;
                }
            }
        } else {
            ++it;
        }
    }

    // Handle customers waiting to pay
    for (auto it = customersWaitingToPay.begin(); it != customersWaitingToPay.end();) {
        if (it->checkIfReady()) {
            for (auto& waiter : waiters) {
                if (waiter.getCurrentDish() == nullptr && waiter.checkIfReady() && waiter.getCurrentCustomer() == 0) {
                    waiter.takeOrderFromCustomer(it->getId());
                    waiter.setTimer(waiterWalkDelay);
                    waiter.setCustomerPaying(true);
                    spdlog::info("Waiter walking to customer {} to take payment", it->getId());
                    it = customersWaitingToPay.erase(it);
                    break;
                }
            }
        } else {
            ++it;
        }
    }

    for (Waiter& waiter : waiters) {
        if ((waiter.getCurrentDish() != nullptr || waiter.getCurrentCustomer() != 0) && waiter.checkIfReady()) {
            // find the customer using their ID
            auto customerIt = std::find_if(customers.begin(), customers.end(), [&waiter](const Customer& c) {
                return c.getId() == waiter.getCurrentCustomer();
            });

            if (customerIt != customers.end()) {
                Customer& customer = *customerIt; // Get the reference to the customer object

                if (waiter.getCurrentDish() == nullptr && !waiter.getCustomerPaying()) {
                    auto order = customer.order(menu);
                    Recipe* recipePtr = &order.recipe;
                    Dish dish(recipePtr, customer);  // Associate the dish with the customer
                    ordersToMake.push(dish);
                    spdlog::info("Customer ordered: {}", dish.getRecipe()->getName());
                    waiter.takeOrderFromCustomer(0); // Clear current customer after taking the order
                } else if (waiter.getCurrentDish() == nullptr && waiter.getCustomerPaying()) {
                    kitchen.getAccount().deposit(customer.pay());
                    spdlog::info("Customer {} paid", customer.getId());

                    // Remove the customer after they pay
                    customers.erase(customerIt);
                    auto tableIt = std::find_if(tables.begin(), tables.end(), [&customer](Table& table) {
                        return table.getCustomer() == customer;
                    });
                    if (tableIt != tables.end()) {
                        tableIt->removeCustomer();
                    }
                    spdlog::info("Customer left the restaurant");
                    waiter.takeOrderFromCustomer(0); // Clear current customer after the customer leaves
                } else if (waiter.getCurrentDish() != nullptr) {
                    spdlog::info("Waiter served: {}", waiter.getCurrentDish()->getRecipe()->getName());
                    customersWaitingToPay.push_back(customer); // Move customer to waiting to pay queue
                    customer.setTimer(customerEatDelay);
                    spdlog::info("Customer {} is eating for {} seconds", customer.getId(), customerEatDelay);
                    waiter.takeDish(nullptr);
                }
            } else {
                // Handle case where customer with the ID is not found
                spdlog::warn("Customer not found with ID {}", waiter.getCurrentCustomer());
                waiter.takeOrderFromCustomer(0); // Clear invalid customer ID
            }
        }
    }

    if (currentDishPrepearing.empty() && !ordersToMake.empty()) {
        // Move the first dish from ordersToMake to currentDishesPrepearing
        currentDishPrepearing.push_back(std::move(ordersToMake.front()));
        ordersToMake.pop();

        // Now, the dish being prepared is the first (and only) element in the vector
        Dish& dishBeingPrepared = currentDishPrepearing[0];

        dishBeingPrepared.setTimer(kitchen.prepareDish(*dishBeingPrepared.getRecipe(), orderPrepareDelay));
        spdlog::info("Dish {} is being prepared, for {} seconds", dishBeingPrepared.getRecipe()->getName(), orderPrepareDelay);
    }

    if (!currentDishPrepearing.empty() && currentDishPrepearing[0].checkIfReady()) {
        ordersToServe.push(std::move(currentDishPrepearing[0])); // Move the finished dish
        currentDishPrepearing.clear(); // Empty the vector
    }
}
