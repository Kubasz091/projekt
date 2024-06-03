#include "Kitchen.h"

Kitchen::Kitchen(int numCooks, double staring_money)
    : numCooks(numCooks), shop(), account(staring_money) {}

double Kitchen::prepareDish(const Recipe& recipe, double normalCookingTime) {
    for (const auto& ingredientQuantity : recipe.getIngredients()) {
        auto cost = shop.buyIngredient(ingredientQuantity.ingredient.getName(), ingredientQuantity.quantity);
        account.withdraw(cost);
    }
    auto normalCookingTime_step = normalCookingTime * recipe.getIngredients().size();
    auto return_time = normalCookingTime_step*0.8 / (1 + 0/5 * (numCooks - 1)) + normalCookingTime_step*0.2;

    return return_time;
}

Shop& Kitchen::getShop() {
    return shop;
}

Account& Kitchen::getAccount() {
    return account;
}