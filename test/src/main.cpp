#include <memory>
#include <vector>
#include <thread>

#include <lib/asserter/src/test.hpp>
#include <lib/circuit/src/index.hpp>

template <class T>
/**
 * @brief Verifies that a container-like object yields the pushed value 99 when popped.
 *
 * Calls push(99) on the provided container and ensures wait_pop retrieves the value 99.
 * On non-EMSCRIPTEN builds the pop is performed in a background thread to exercise waiting behavior; on EMSCRIPTEN builds the sequence runs synchronously.
 *
 * @tparam T Type of the container-like object; must provide `push(int)` and `wait_pop(int&)`.
 * @param s Pointer-like container instance whose `push` and `wait_pop` methods will be exercised.
 */
void test_wait_pop(T s)
{
#ifndef __EMSCRIPTEN__
    auto tmp = std::thread([=]() {
        int i(0);
        s->wait_pop(i);
        ASSERT(i == 99);
    });

    s->push(99);
    tmp.join();
#else
    s->push(99);
    int i(0);
    s->wait_pop(i);
    ASSERT(i == 99);
#endif 
}

template <class T>
void test_ctor_and_swap()
{
    T a, b;
    a.swap(b);
}

int main()
{
    using namespace om636::circuit;

    test_wait_pop(make_stack<int>());
    test_wait_pop(make_queue<int>());
    test_ctor_and_swap<CircuitQueue<int>>();
    test_ctor_and_swap<CircuitStack<int>>();

    return 0;
}