#pragma once

#include "impl/circuit_host.h"
#include "impl/stack.h"
#include "impl/queue.h"

namespace om636 {
namespace twice_size {

template<typename T> 
Circuit<T> * make_stack()
{
    return new CircuitHost<T, StackPolicy>();
}

template<typename T>
Circuit<T> * make_queue()
{
    return new CircuitHost<T, QueuePolicy>();
}
} // twice_size
} // om636

