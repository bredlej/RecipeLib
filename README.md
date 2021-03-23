# RecipeLib
### Description
C++ proof-of-concept project for asynchronous combination of arbitrary resources into products

I'm experimenting here with **C++20** features such as **concepts** and **coroutines** to create a library where
resources can be combined into other resources.

Currently consists of:
- `Resource<R>` a class defining a single resource of type `R`, where `R` is defined by a **concept** `is_a_resource<R>` with some type constraints.
- `Ingredient<T, R>` class describing a pairing of a comparable amount type `T` (like `const int`, `double`, etc.) and an `is_a_resource<R>` value.
- `Recipe<T, R>` class describing a recipe that yields an `Ingredient<T, R>` out of a given list of ingredients.

### Sample usage
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

### TODO
Coming up are some **coroutines** which would use the recipes and ingredients to create data asynchronously.

### Author
Patryk Szczypień - patryk.szczypien@gmail.com
### License
MIT License