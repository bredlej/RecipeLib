#include "lib/Resource.h"
#include "lib/ResourcePool.h"
#include <iostream>
#include <memory>
#include <vector>

int main() {
    using recipelib::ResourceType;
    using recipelib::Resource;

    auto resources = std::vector<std::unique_ptr<recipelib::ResourceInterface>>{};

    resources.emplace_back(std::make_unique<Resource<ResourceType::Wood>>("Wood #1", 4));
    resources.emplace_back(std::make_unique<Resource<ResourceType::Stone>>("Stone #1", 1));
    resources.emplace_back(std::make_unique<Resource<ResourceType::Wood>>("Wood2 #2", 7));

    for (auto &resource: resources) {
        std::cout << resource->GetName() << " amount: " << resource->GetAmount() << std::endl;
        std::cout << resource->GetName() << " is Wood? " << (resource->GetType() == ResourceType::Wood) << std::endl;
        std::cout << resource->GetName() << " is Stone? " << (resource->GetType() == ResourceType::Stone) << std::endl;
        std::cout << std::endl;
    }

    std::cout << "After removing resources" << std::endl;

    resources.erase(std::remove_if(resources.begin(),
                                   resources.end(),
                                   [&](std::unique_ptr<recipelib::ResourceInterface> const &res) {return res->GetType() == ResourceType::Stone;})
                            , resources.end());

    for (auto &resource: resources) {
        std::cout << resource->GetName() << " amount: " << resource->GetAmount() << std::endl;
        std::cout << resource->GetName() << " is Wood? " << (resource->GetType() == ResourceType::Wood) << std::endl;
        std::cout << resource->GetName() << " is Stone? " << (resource->GetType() == ResourceType::Stone) << std::endl;
        std::cout << std::endl;
    }

    std::cout << "Resource Pool" << std::endl;
    auto resource_pool = recipelib::ResourcePool();

    resource_pool.AddResource<ResourceType::Wood>("W1 - template", 1);
    resource_pool.AddResource<ResourceType::Stone>("S1 - template", 3);
    resource_pool.AddResource<ResourceType::Stone>("S2 - template", 2);
    std::cin;
}
