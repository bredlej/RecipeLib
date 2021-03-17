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

    class ResourceInterface {
    public:
        virtual uint32_t GetAmount() = 0;
        virtual void SetAmount(uint32_t amount) = 0;
        virtual std::string GetName() = 0;
        virtual ResourceType GetType() = 0;

    };

    template<ResourceType T>
    class Resource : public ResourceInterface {
    public:
        explicit Resource(std::string name, uint32_t amount) : name_{std::move(name)}, amount_{amount}, type_{T} {}
        ~Resource() {std::cout << "Destroying " << GetName() << std::endl;}
        uint32_t GetAmount() override {
            return amount_;
        }
        void SetAmount(uint32_t amount) override {
            amount_ = amount;
        }
        std::string GetName() override {
            return name_;
        }
        ResourceType GetType() override {
            return type_;
        }

    private:
        uint32_t amount_;
        std::string name_;
        const ResourceType type_;
    };
}// namespace recipelib
#endif//RECIPELIB_RESOURCE_H
