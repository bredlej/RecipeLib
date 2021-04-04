# RecipeLib
### Description
C++ proof-of-concept project for asynchronous combination of arbitrary resources into products

I'm experimenting here with **C++20** features such as **concepts** and **coroutines** to create a library where
resources can be combined into other resources.

Currently consists of:
- `Resource<R>` a class defining a single resource of type `R`, where `R` is defined by a **concept** `is_a_resource<R>` with some type constraints.
- `Ingredient<T, R>` class describing a pairing of a comparable amount type `T` (like `const int`, `double`, etc.) and an `is_a_resource<R>` value.
- `Recipe<T, R>` class describing a recipe that yields an `Ingredient<T, R>` out of a given list of ingredients.
- `ResourceBuilder<R>` class for creating asynchronous tasks which return a `Resource<R>` in a given time
### Sample usage - Creation of recipes from ingredients
```c++
#include "lib/Resource.h"

/* Declare some resource types here */
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

int main() {
    auto my_stone_resource = recipelib::Resource<resources::Stone>();
            
    auto stone_ingredient = recipelib::Ingredient<const int, resources::Stone>(1, my_stone_resource);
    auto wood_ingredient = recipelib::Ingredient<const double, resources::Wood>(2.5); // constructor deduces resource type from template
    
    auto building_recipe = recipelib::Recipe<int, resources::Building>(1, {stone_igredient, wood_ingredient});
    
    auto first_building = building_recipe.yield();
    auto second_building = building_recipe.yield(); 
}
```
### Sample usage - Asynchronous creation of Resources
Resources can be built simultaneously in realtime with use of **C++20 coroutines**.

The program uses the [CppCoro](https://github.com/lewissbaker/cppcoro) library as the coroutine implementation.
Below is a sample code that creates two resources simultaneously (`resources::Wood` in 3 seconds and `resources::Stone` in 2 seconds) and waits until both are done before continuing to run.
```c++
#include "lib/Resource.h"
#include <cppcoro/schedule_on.hpp>
#include <cppcoro/static_thread_pool.hpp>
#include <cppcoro/sync_wait.hpp>
#include <cppcoro/when_all.hpp>
#include <iostream>

int main() {
    using namespace recipelib;

    auto builder_thread = cppcoro::static_thread_pool(2);
    auto wood_builder_task = ResourceBuilder<resources::Wood>().build(builder_thread, 3);
    auto stone_builder_task = ResourceBuilder<resources::Stone>().build(builder_thread, 2);

    cppcoro::sync_wait(when_all(cppcoro::schedule_on(builder_thread, wood_builder_task),
                                cppcoro::schedule_on(builder_thread, stone_builder_task)));

    std::cout << "Done building wood and stone." << std::endl;
}
```
Returns the output:
```
Starting build of Wood (3 seconds)
Starting build of Stone (2 seconds)
Wood: [1/3]
Stone: [1/2]
Wood: [2/3]
Stone: [2/2]
  (Stone finished)
Wood: [3/3]
  (Wood finished)
Done building wood and stone.
```

### Author
Patryk Szczypień - patryk.szczypien@gmail.com
### License
MIT License