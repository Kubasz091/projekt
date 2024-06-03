#ifndef BILL_H
#define BILL_H

#include <vector>
#include <string>
#include "Recipe.h"
#include "Menu.h"

class Bill {
private:
    std::vector<std::string> orders;
    double totalCost = 0.0;
    bool paid;
public:
    Bill(); // Constructor
    void addOrder(const std::string& orderName, double price);
    double pay(); // Marks the bill as paid
    bool isPaid() const; // Checks whether the bill has been paid
};

#endif // BILL_H