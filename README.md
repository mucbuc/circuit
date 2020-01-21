## Objective

Syncronize container operations (for single objects)

## Interface

```
namespace om636 {
namespace circuit {

    template <class T>
    struct Circuit {
        typedef T value_type;

        virtual ~Circuit() = default;
        virtual void push(value_type&&) = 0;
        virtual bool check_pop(value_type&) = 0;
        virtual void wait_pop(value_type&) = 0;
    };

} // circuit
} // om636
```

## Example
```
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
```

##### output 
```
popped: 99
popped: 77
popped: 88
```
