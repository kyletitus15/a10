#pragma once

#include "array/vector.hpp"
#include "list/doubly_linked.hpp"


namespace dsac::stackqueue {
/// A simplified version of the STL stack
template <typename T, typename Container=dsac::array::Vector<T>>
class stack {
    private:
        Container data;

    public:
        /// return the number of elements currently in the stack
        int size() const {
            return data.size();
        }
        
        /// return whether the stack is currently empty
        bool empty() const {
            return data.empty();
        }

        /// return const reference to the top element of the stack
        const T& top() const {
            return data.back();
        }

        /// return live (non-const) reference to the top element of the stack
        T& top() {
            return data.back();
        }

        /// add an element to the top of the stack
        void push(const T& elem) {
            data.push_back(elem);
        }

        /// remove the top element from the stack
        void pop() {
            data.pop_back();
        }
};
}  // namespace dsac::stackqueue
