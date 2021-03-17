//
// Created by geoco on 13.03.2021.
//

#ifndef RECIPELIB_RESOURCEPOOL_H
#define RECIPELIB_RESOURCEPOOL_H

#include "Resource.h"
#include <memory>
#include <unordered_map>

namespace recipelib{

    class ResourcePool {
    public:
        template <ResourceType T>
        void AddResource(std::string name, uint32_t amount) {
            if (resources_[T] == nullptr) {
                resources_[T] = std::make_shared<recipelib::Resource<T>>(name, amount);
            }
            else {
                resources_[T]->SetAmount(amount);
            }
        }
    private:
        std::unordered_map<recipelib::ResourceType, std::shared_ptr<recipelib::ResourceInterface>> resources_;
    };
}

#endif//RECIPELIB_RESOURCEPOOL_H
