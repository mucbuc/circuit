#pragma once

#include <queue>

namespace om636 {
namespace circuit {

    template <typename T>
    struct QueuePolicy {
        typedef T value_type;

        template <class U>
        /**
         * @brief Initialize `lhs` by taking ownership of `rhs`'s internal queue.
         *
         * Moves the contents of `rhs.m_queue` into `lhs.m_queue`, leaving `rhs.m_queue`
         * in a valid but unspecified state according to move semantics.
         *
         * @param lhs Destination object whose internal queue will be replaced.
         * @param rhs Source object whose internal queue will be moved from.
         */
        static void on_init(U& lhs, U&& rhs)
        {
            lhs.m_queue = std::move(rhs.m_queue);
        }

        template <class U>
        /**
         * @brief Copies the internal queue from one holder to another.
         *
         * Replaces `lhs`'s stored queue with a copy of `rhs`'s stored queue.
         *
         * @param lhs Destination object whose internal queue will be overwritten.
         * @param rhs Source object whose internal queue will be copied.
         */
        static void on_copy(U& lhs, const U& rhs)
        {
            lhs.m_queue = rhs.m_queue;
        }

        template <class U>
        /**
         * @brief Swap the internal queues of two storage objects.
         *
         * Exchanges the contents of `lhs` and `rhs` by swapping their internal
         * `m_queue` members.
         *
         * @param lhs Storage object whose internal queue will be swapped with `rhs`.
         * @param rhs Storage object whose internal queue will be swapped with `lhs`.
         */
        static void on_swap(U& lhs, U& rhs)
        {
            lhs.m_queue.swap(rhs.m_queue);
        }

        template <class U>
        /**
         * @brief Moves the front element of lhs's internal queue into v and removes it from the queue.
         *
         * Preconditions: lhs's internal queue contains at least one element.
         *
         * @param lhs Object whose internal queue provides the front element.
         * @param v Destination that receives the moved front value.
         */
        static void on_pop(U& lhs, value_type& v)
        {
            v = std::move(lhs.m_queue.front());
            lhs.m_queue.pop();
        }

        template <class U>
        /**
         * @brief Appends a value to the policy's internal queue.
         *
         * Pushes the provided value into lhs.m_queue; the value is moved from `v`.
         *
         * @param lhs Container whose internal queue will receive the value.
         * @param v  Value to be moved into the queue.
         */
        static void on_push(U& lhs, value_type&& v)
        {
            lhs.m_queue.push(std::move(v));
        }

        template <class U>
        /**
         * @brief Check whether the holder's internal queue is empty.
         *
         * @param h The holder whose internal queue is examined.
         * @return `true` if the internal queue is empty, `false` otherwise.
         */
        static bool on_empty(U& h)
        {
            return h.m_queue.empty();
        }

    private:
        std::queue<value_type> m_queue;
    };

} // circuit
} // om636