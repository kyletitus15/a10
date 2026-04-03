//stackqueue/stack_queue_utils.hpp

#pragma once

#include "array/vector.hpp"
#include "list/doubly_linked.hpp"

#include "stackqueue/stack.hpp"
#include "stackqueue/queue.hpp"

#include <string>
#include <stdexcept>

std::string remove_duplicates(std::string input) {
    dsac::stackqueue::stack<char> stack;
    for (auto c : input) {
        if (!stack.empty() && stack.top() == c) {
            stack.pop();
        }
        else {
            stack.push(c);
        }
    }
    
    std::string res;
    while (!stack.empty()) {
        res = res + stack.top();
        stack.pop();
    }

    std::reverse(res.begin(), res.end());
    return res;
}

std::string clean_backspace_string(std::string input) {
    dsac::stackqueue::stack<char> stack;
    for (auto c : input) {
        if (c == '<') {
            if (!stack.empty()) {
                stack.pop();
            }
        }
        else {
            stack.push(c);
        }
    }

    std::string res;
    while (!stack.empty()) {
        res = res + stack.top();
        stack.pop();
    }

    std::reverse(res.begin(), res.end());
    return res;
}

template <
    typename T, 
    typename StackContainer=dsac::array::Vector<T>,
    typename QueueContainer=dsac::array::Vector<T>
    >
bool stack_contains(
    dsac::stackqueue::stack<T, StackContainer>& st, 
    dsac::stackqueue::queue<T, QueueContainer>& qu, 
    const T& elt) {
        if (!qu.empty()) {
        throw std::invalid_argument("Q must be initially empty.");
    }
    bool isPresent = false;

    while (!st.empty()) {
        if (st.top() == elt) isPresent = true;
        qu.push(st.top());
        st.pop();
    }

    while (!qu.empty()) {
        st.push(qu.front());
        qu.pop();
    }
    
    return isPresent;
    }