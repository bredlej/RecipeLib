//
// Created by geoco on 13.03.2021.
//

#ifndef RECIPELIB_RESOURCEPOOL_H
#define RECIPELIB_RESOURCEPOOL_H

#include "Resource.h"

namespace recipelib{

    static constexpr int initial_amount = 0;
    struct ResourcePoolBase {};

    template<recipelib::is_one_or_more_resources... Resources>
    class ResourcePool : ResourcePoolBase {
    public:
        std::tuple<recipelib::Resource<Resources>...> resources_{std::make_tuple(recipelib::Resource<Resources>()...)};
    };

    template<typename T>
    concept is_a_resource_pool = std::is_base_of_v<ResourcePoolBase, T>;

    template<recipelib::is_a_resource T>
    auto &get(is_a_resource_pool auto &pool) {
        return std::get<recipelib::Resource<T>>(pool.resources_);
    }
}

#endif//RECIPELIB_RESOURCEPOOL_H
