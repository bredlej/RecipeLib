//
// Created by geoco on 13.03.2021.
//

#ifndef RECIPELIB_RESOURCEPOOL_H
#define RECIPELIB_RESOURCEPOOL_H

#include "Resource.h"
#include <memory>
#include <unordered_map>

namespace recipelib{
    constexpr int initial_amount = 0;

    template<ResourceType... T>
    class ResourcePool {
    public:
        std::tuple<Resource<T>...> resources_ { std::make_tuple(Resource<T>(initial_amount) ...) };
    };
}

#endif//RECIPELIB_RESOURCEPOOL_H
