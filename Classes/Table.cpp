#include "Table.h"

void Table::seatCustomer(Customer newCustomer) {
    customer = newCustomer;
}

bool Table::isOccupied() const {
    return customer.getId() != 0;
}

void Table::removeCustomer() {
    customer = Customer();
}

Customer Table::getCustomer() const {
    return customer;
}
