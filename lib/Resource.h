//
// Created by geoco on 07.03.2021.
//

#ifndef RECIPELIB_RESOURCE_H
#define RECIPELIB_RESOURCE_H
#include <chrono>
#include <concepts>
#include <cppcoro/shared_task.hpp>
#include <cppcoro/static_thread_pool.hpp>
#include <cppcoro/task.hpp>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

namespace resources {
    struct ResourceBase {};
    struct Wood : ResourceBase {
        static constexpr const char *name = "Wood";
    };
    struct Stone : ResourceBase {
        static constexpr const char *name = "Stone";
    };
    struct Water : ResourceBase {
        static constexpr const char *name = "Water";
    };
    struct Building : ResourceBase {
        static constexpr const char *name = "Building made of stone & wood";
    };
}// namespace resources

namespace recipelib {
    template<typename T>
    concept has_a_name = requires {
        { T::name }
        ->std::convertible_to<const char *>;
    };

    template<typename T>
    concept is_a_resource = (std::is_base_of_v<resources::ResourceBase, T> && has_a_name<T>);

    template<typename... T>
    concept is_one_or_more_resources = (is_a_resource<T> && ...);

    template<is_a_resource T>
    class Resource {
    public:
        Resource() = default;

        friend std::ostream &operator<<(std::ostream &stream, const Resource &res) {
            return stream << "[" << T::name << "]";
        }
    };

    struct IngredientBase {};

    template<typename T>
    concept is_an_amount = std::totally_ordered<T>;

    template<typename T, typename I>
    concept is_an_ingredient = is_an_amount<T> &&std::is_base_of_v<IngredientBase, I>;

    template<typename T, typename... I>
    concept is_one_or_more_ingredients = (is_an_ingredient<T, I> && ...);

    /**
     * Describes an Ingredient, which is a pairing of a Resource and its amount
     * @tparam T Type of the amount variable
     * @tparam R Resource type
     */
    template<is_an_amount T, is_a_resource R>
    class Ingredient : public IngredientBase {
    public:
        Ingredient() = delete;
        explicit Ingredient(T amount) : value_{Resource<R>(), amount} {};
        explicit Ingredient(T amount, Resource<R> resource) : value_{resource, amount} {};
        ~Ingredient(){};
        auto &get() { return value_; };
        Resource<R> GetResource() { return value_.first; };
        T GetAmount() { return value_.second; };

    private:
        std::pair<Resource<R>, T> value_;
    };

    template<is_an_amount T, is_a_resource R>
    struct RecipeBase {
        virtual T GetOutputAmount() = 0;
        virtual Resource<R> GetProductType() = 0;
    };

    /**
     * Describes a recipe for the creation of an ingredient from other ingredients.
     *
     * The template parameter passed to the class constructor defines the resulting ingredient.
     * @tparam T Type of the variable defining the amount of ingredients produced by yielding this recipe
     * @tparam R Resource that is yielded by the recipe
     */
    template<is_an_amount T, is_a_resource R>
    class Recipe : RecipeBase<T, R> {
        using IngredientList = std::vector<std::shared_ptr<recipelib::IngredientBase>>;

    public:
        explicit Recipe(T outputAmount, IngredientList &&ingredients) : outputAmount_{outputAmount}, ingredients_(std::move(ingredients)){};
        Recipe(T outputAmount, std::initializer_list<recipelib::IngredientBase> &&ingredients) {
            outputAmount_ = outputAmount;
            for (auto &ingredient : ingredients) {
                ingredients_.push_back(std::make_shared<recipelib::IngredientBase>(ingredient));
            }
        }
        Resource<R> GetProductType() { return Resource<R>(); };
        T GetOutputAmount() { return outputAmount_; };
        Ingredient<T, R> yield() { return Ingredient<T, R>(outputAmount_); }

    private:
        T outputAmount_;
        IngredientList ingredients_;
    };

    template<is_a_resource R>
    class ResourceBuilder {
    public:
        cppcoro::shared_task<Resource<R>> build(cppcoro::static_thread_pool &tp, uint32_t time_seconds) {
            co_await tp.schedule();
            std::cout << "Starting build of " << R::name << " (" << time_seconds << " seconds)" << std::endl;
            auto start_time = std::chrono::steady_clock::now();
            int seconds_elapsed = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - start_time).count();
            while (seconds_elapsed < time_seconds) {
                if (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - start_time).count() != seconds_elapsed) {
                    seconds_elapsed = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - start_time).count();
                    std::cout << R::name << ": [" << seconds_elapsed << "/" << time_seconds << "]" << std::endl;
                }
            }
            std::cout << "  (" << R::name << " finished)" << std::endl;
            co_return Resource<R>();
        }
    };
}// namespace recipelib

#endif//RECIPELIB_RESOURCE_H
