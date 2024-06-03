#include <iostream>
#include "Simulation.h"
#include "spdlog/spdlog.h"
#include <unistd.h>

int main() {
    int numWaiters, numCooks, numTables, duration;
    double startingMoney;

    spdlog::info("Enter number of waiters: ");
    std::cin >> numWaiters;

    spdlog::info("Enter number of cooks: ");
    std::cin >> numCooks;

    spdlog::info("Enter number of tables: ");
    std::cin >> numTables;

    spdlog::info("Enter duration of simulation: ");
    std::cin >> duration;

    spdlog::info("Enter starting money: ");
    std::cin >> startingMoney;

    try {
        Simulation simulation(numWaiters, numCooks, numTables, duration, startingMoney);
        sleep(3);
        simulation.run();
    } catch (const std::runtime_error& e) {
        spdlog::error("Error running the simulation: {}", e.what());
        return 1;
    }

    return 0;
}