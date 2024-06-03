#ifndef SIMULATION_H
#define SIMULATION_H

#include "Classes/Restaurant.h"
#include "Classes/Shop.h"
#include <string>
#include <ncurses.h>
#include "json.hpp"
#include <fstream>

class Simulation {
private:
    Restaurant restaurant;

    int simulationDuration;

    int scaleOfTime;
    int openingTime;
    int closingTime;
    std::map<std::string, int> timeSettings;

public:
    Simulation(int numWaiters, int numCooks, int numTables, int duration, double money);
    void run();
};

#endif // SIMULATION_H