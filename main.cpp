#include "lib/Resource.h"
#include "lib/ResourcePool.h"
#include <iostream>

int main() {
    std::cout << "-- Scope 1 start" <<std::endl;
    auto stone_ingredient = recipelib::Ingredient<const int, resources::Stone>(1);
    auto wood_ingredient = recipelib::Ingredient<const double, resources::Wood>(2.5);

    {
        std::cout << "-- Scope 2 start"<<std::endl;
        auto recipe = recipelib::Recipe<int, resources::Building>(1, {stone_ingredient, wood_ingredient});

        auto firstBuilding = recipe.yield();
        std::cout << firstBuilding.GetResource() << ": " << firstBuilding.GetAmount() << std::endl;

        auto secondBuilding = recipe.yield();
        std::cout << secondBuilding.GetResource() << ": " << secondBuilding.GetAmount() << std::endl;
        std::cout << "-- Scope 2 end"<<std::endl;
    }
    std::cout << "-- Scope 1 end"<<std::endl;
}
