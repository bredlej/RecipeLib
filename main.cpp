#include "lib/Resource.h"
#include "lib/ResourcePool.h"
#include <iostream>
#include <vector>

int main() {
    using recipelib::Resource;
    using recipelib::ResourceType;

    auto only_wood_resources = recipelib::ResourcePool<ResourceType::Wood>();
    auto all_resources = recipelib::ResourcePool<ResourceType::Wood, ResourceType::Stone>();

    auto &stone1 = std::get<Resource<ResourceType::Wood>>(all_resources.resources_);

    // not possible due to compile time verification of the type
    // auto &stone2 = std::get<Resource<ResourceType::Stone>>(only_wood_resources.resources_);

    std::cin;
}
