#include <memory>
#include <vector>

#include <tmp/src/test.h>

#include <lib/circuit/src/factory.h>

template <class T>
void test_wait_pop(T s)
{

    auto tmp = std::thread([=]() {
        int i(0);
        s->wait_pop(i);
        ASSERT(i == 99);
    });

    s->push(99);
    tmp.join();
}

int main()
{
    using namespace om636::twice_size;

    test_wait_pop(make_stack<int>());
    test_wait_pop(make_queue<int>());

    return 0;
}
