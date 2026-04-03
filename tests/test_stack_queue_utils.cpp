//tests/test_stack_queue_utils.cpp

#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

#include "array/vector.hpp"
#include "list/doubly_linked.hpp"

#include "stackqueue/stack.hpp"
#include "stackqueue/queue.hpp"
//#include "stackqueue/deque.hpp"
#include "stackqueue/array_queue.hpp"
#include "stackqueue/stack_queue_utils.hpp"

#include <string>

TEST_CASE("Remove Duplicates Tests") {
    REQUIRE(remove_duplicates("abbaca") == "ca");
    REQUIRE(remove_duplicates("aabbcc") == "");
}

TEST_CASE("Clean Backspace String Tests") {
    REQUIRE(clean_backspace_string("ab<c") == "ac");
    REQUIRE(clean_backspace_string("<") == "");
}

TEST_CASE("Stack Restore Tests") {
    dsac::stackqueue::stack<int> stack;
    dsac::stackqueue::queue<int> queue;
    int x = 1;
    int y = 4;
    stack.push(1);
    stack.push(2);
    stack.push(3);
    REQUIRE(stack_contains(stack, queue, x));
    REQUIRE_FALSE(stack_contains(stack, queue, y));
    
}

TEST_CASE("Stack Basic Operations") {
    dsac::stackqueue::stack<int> st;

    REQUIRE(st.empty());
    REQUIRE(st.size() == 0);

    st.push(1);
    st.push(2);
    st.push(3);

    REQUIRE(st.size() == 3);
    REQUIRE(st.top() == 3);

    st.pop();
    REQUIRE(st.top() == 2);
    REQUIRE(st.size() == 2);

    st.pop();
    st.pop();
    REQUIRE(st.empty());
}

TEST_CASE("Queue Basic Operations") {
    dsac::stackqueue::queue<int> qu;

    REQUIRE(qu.empty());
    REQUIRE(qu.size() == 0);

    qu.push(1);
    qu.push(2);
    qu.push(3);

    REQUIRE(qu.size() == 3);
    REQUIRE(qu.front() == 1);
    REQUIRE(qu.back() == 3);

    qu.pop();
    REQUIRE(qu.front() == 2);
    REQUIRE(qu.size() == 2);

    qu.pop();
    qu.pop();
    REQUIRE(qu.empty());
}


