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
