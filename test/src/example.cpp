#include <lib/asserter/src/test.hpp>

#include <lib/circuit/src/interface.hpp>
#include <lib/circuit/src/index.hpp>


using namespace std;
using namespace om636::circuit;

/**
 * @brief Test program that verifies LIFO push/pop behavior of the stack implementation using assertions.
 *
 * The program creates a stack of integers, pushes 88 then 77, pops the top element with a blocking pop
 * and asserts it equals 77, then attempts a non-blocking pop and, if successful, asserts the remaining
 * value equals 88.
 *
 * @return int Exit code: 0 on success. The program may abort if assertions fail.
 */
int main()
{
    auto s = make_stack<int>();

    s->push(88);
    s->push(77);

    int i(0);
    s->wait_pop(i);
    ASSERT(i == 77);
    if (s->check_pop(i)) {
        ASSERT(i == 88);
    }
}