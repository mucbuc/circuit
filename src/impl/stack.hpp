#pragma once

#include <stack>

namespace om636 {
namespace circuit {

    template <typename T>
    struct StackPolicy {
        typedef T value_type;

        template <class U>
        /**
         * @brief Copy the internal stack state from one policy instance to another.
         *
         * Copies the underlying std::stack holding values from rhs into lhs by assignment.
         *
         * @tparam U Container-like type that exposes a member `m_stack`.
         * @param lhs Destination instance whose internal stack will be overwritten.
         * @param rhs Source instance providing the stack state to copy.
         */
        static void on_copy(U& lhs, const U& rhs)
        {
            lhs.m_stack = rhs.m_stack;
        }

        template <class U>
        /**
         * @brief Initializes `lhs` by moving the internal stack from `rhs`.
         *
         * Moves `rhs`'s internal std::stack into `lhs`, leaving `rhs`'s stack in a valid but unspecified (moved-from) state.
         *
         * @param lhs Destination object whose internal stack will be replaced.
         * @param rhs Source rvalue whose internal stack will be moved.
         */
        static void on_init(U& lhs, U&& rhs)
        {
            lhs.m_stack = std::move(rhs.m_stack);
        }

        template <class U>
        /**
         * @brief Swap the internal stacks of two wrapper objects.
         *
         * Exchanges the contents of `lhs.m_stack` and `rhs.m_stack` so that each object
         * takes ownership of the other's stack elements.
         *
         * @param lhs Left-hand wrapper whose internal stack will be swapped.
         * @param rhs Right-hand wrapper whose internal stack will be swapped.
         */
        static void on_swap(U& lhs, U& rhs)
        {
            lhs.m_stack.swap(rhs.m_stack);
        }

        template <class U>
        /**
         * @brief Moves the top element of the internal stack into `v` and removes it from the stack.
         *
         * Retrieves the element at the top of `lhs.m_stack`, moves it into the output parameter `v`,
         * then pops that element from the stack.
         *
         * @param lhs Container whose internal stack will be modified.
         * @param[out] v Receives the moved top element.
         *
         * @note Calling this when `lhs.m_stack` is empty results in undefined behavior.
         */
        static void on_pop(U& lhs, value_type& v)
        {
            v = std::move(lhs.m_stack.top());
            lhs.m_stack.pop();
        }

        template <class U>
        /**
         * @brief Pushes a value onto the policy's internal stack.
         *
         * Moves `v` into the container and appends it as the new top element of `lhs.m_stack`.
         *
         * @param lhs The policy instance whose internal stack is modified.
         * @param v The value to push; it is moved from into the stack.
         */
        static void on_push(U& lhs, value_type&& v)
        {
            lhs.m_stack.push(std::move(v));
        }

        template <class U>
        /**
         * @brief Checks whether the underlying stack of the provided handler is empty.
         *
         * @param h Handler whose internal stack is queried.
         * @return `true` if the underlying stack is empty, `false` otherwise.
         */
        static bool on_empty(U& h)
        {
            return h.m_stack.empty();
        }

    private:
        std::stack<value_type> m_stack;
    };

} // circuit
} // om636