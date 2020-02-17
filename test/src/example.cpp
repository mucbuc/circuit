#include <tmp/src/test.h>

#include <lib/circuit/src/index.h>

using namespace std;
using namespace om636::circuit;

int main()
{
    auto s = make_stack<int>();

    s->push(88);
    s->push(77);

    s->wait_pop(i);
    if (s->check_pop(i)) {
    }
}
