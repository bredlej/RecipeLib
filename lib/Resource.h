//
// Created by geoco on 07.03.2021.
//

#ifndef RECIPELIB_RESOURCE_H
#define RECIPELIB_RESOURCE_H
#include <concepts>
#include <iostream>
#include <string>
#include <utility>

namespace resource {
    struct ResourceBase {};
    struct Wood : ResourceBase {
        static constexpr const char *name = "Wood";
    };
    struct Stone : ResourceBase {
        static constexpr const char *name = "Stone";
    };

    template<typename T>
    concept is_wood_type = std::is_same_v<Wood, T>;
    template<typename T>
    concept is_stone_type = std::is_same_v<Stone, T>;

    template<typename T>
    concept has_a_name = requires {
        { T::name }
        ->std::convertible_to<const char *>;
    };

    template<typename T>
    concept is_a_resource = (std::is_base_of_v<ResourceBase, T> && has_a_name<T>);

    template<typename... T>
    concept is_one_or_more_resources = (is_a_resource<T> && ...);

    template<resource::is_a_resource T>
    class Resource {
        using type = T;

    public:
        uint32_t amount_;
        Resource() = default;
        explicit Resource(uint32_t amount) : amount_{amount} {};
        friend std::ostream &operator<<(std::ostream &stream, const Resource &res) {
            return stream << "[" << T::name << "]: " << res.amount_;
        }
    };
}// namespace resource


#endif//RECIPELIB_RESOURCE_H
