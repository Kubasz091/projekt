#ifndef TABLE_H
#define TABLE_H

#include "Customer.h"
#include "Menu.h"
#include "Dish.h"

class Table {
private:
    Customer customer;
public:
    void seatCustomer(Customer customer);
    bool isOccupied() const;
    void removeCustomer();
    Customer getCustomer() const;
};

#endif // TABLE_H