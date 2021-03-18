#include "lib/Resource.h"
#include "lib/ResourcePool.h"
#include <iostream>

int main() {
    auto all_resources = recipelib::ResourcePool<resource::Wood, resource::Stone>();
    auto wood_resource = recipelib::ResourcePool<resource::Wood>();

    resource::Resource wood1 = recipelib::get<resource::Wood>(all_resources);
    auto &wood2 = recipelib::get<resource::Wood>(wood_resource);

    std::cout << wood1 << std::endl;
    wood1.amount_ = 3;
    std::cout << wood1 << std::endl;
    std::cout << wood2 << std::endl;

    resource::Resource stone = recipelib::get<resource::Stone>(all_resources);
    std::cout << stone;
}
