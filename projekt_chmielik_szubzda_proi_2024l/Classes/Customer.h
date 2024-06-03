#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <chrono>
#include "Bill.h"
#include "Menu.h"
class Customer {
private:
    Bill bill;
    int id;
    bool approached = false;
    std::chrono::time_point<std::chrono::high_resolution_clock> timer;
public:
    Customer();
    Customer(int id);
    MenuPosition order(const Menu& menu);
    void setTimer(double duration);
    bool checkIfReady() const;
    int getId() const;
    double pay();
    bool operator==(const Customer& other) const;

};

#endif 