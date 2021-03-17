//
// Created by geoco on 07.03.2021.
//

#ifndef RECIPELIB_RESOURCE_H
#define RECIPELIB_RESOURCE_H
#include <iostream>
#include <string>
#include <utility>
namespace recipelib {
    enum class ResourceType { Wood,
                              Stone };

    std::string to_string(ResourceType t) {
        switch (t) {
            case ResourceType::Wood:
                return "Wood";
            case ResourceType::Stone:
                return "Stone";
            default:
                return "Unknown";
        }
    }

    template<ResourceType T>
    class Resource {
    public:
        explicit Resource(uint32_t amount) : name_{to_string(T)}, amount_{amount}, type_{T} {}
        ~Resource() = default;

        uint32_t GetAmount() {
            return amount_;
        }
        void SetAmount(uint32_t amount) {
            amount_ = amount;
        }
        std::string GetName() {
            return name_;
        }
        ResourceType GetType() {
            return type_;
        }

    private:
        uint32_t amount_;
        const std::string name_;
        const ResourceType type_;
    };
}// namespace recipelib
#endif//RECIPELIB_RESOURCE_H
