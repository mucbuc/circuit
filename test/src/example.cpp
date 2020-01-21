#include <iostream>
#include <thread>

#include <tmp/src/test.h>

#include <lib/circuit/src/index.h>

using namespace std;
using namespace om636::circuit;

int main()
{
    CircuitStack<int> s;
	
    auto t = thread([&]() {
        int i(0);
        s.wait_pop(i);
	cout << "popped: " << i << endl;
	s.push(88);
	s.push(77);
    });

    s.push(99);
    t.join();

    int i(0);
    while (s.check_pop(i)) {
    	cout << "popped: " << i << endl;
    }
}
