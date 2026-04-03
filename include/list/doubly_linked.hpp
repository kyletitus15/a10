#pragma once

#include <utility>     // provides std::swap

namespace dsac::list {
//akin to std::list
template <typename T>
class DoublyLinkedList {
    private:
        class Node {
            public:
                T elem;
                Node* prev{nullptr};
                Node* next{nullptr};
                
                // ToDo
                Node() = default;
                Node(const T& element, Node* prv, Node* nxt) : elem{element}, prev{prv}, next{nxt} {}
        };
        int sz{0};
        Node* header; // sentinel node
        Node* trailer;// sentinel node
        void create_sentinels() {
            header = new Node();
            trailer = new Node();
            header->next = trailer;
            trailer->prev = header;
        }
    public:
        // ToDo
        DoublyLinkedList() {
            create_sentinels();
        }
        int size() const {
            return sz;
        }
        bool empty() const {
            return sz == 0;
        }
        T& front() {
            return header->next->elem;
        }
        const T& front() const {
            return header->next->elem;
        }
        T& back() {
            return trailer->prev->elem;
        }
        const T& back() const {
            return trailer->prev->elem;
        }
    private:
        Node* insert_before(T elem, Node* successor) {
            Node* predecessor = successor->prev;
            Node* newest = new Node(elem, predecessor, successor);
            predecessor->next = newest;
            successor->prev = newest;
            sz++;
            return newest;
        }
        void erase(Node* node) {
            Node* pred = node->prev;
            Node* succ = node->next;
            pred->next = succ;
            succ->prev = pred;
            delete node;
            sz--;
        }
    public:
        void push_front(const T& elem) {
            insert_before(elem, header->next);
        }
        void push_back(const T& elem) {
            insert_before(elem, trailer);
        }
        void pop_front() {
            erase(header->next);
        }
        void pop_back() {
            erase(trailer->prev);
        }
        void concatenate(DoublyLinkedList& M) {
            // self-concatenation: do nothing
            if (this == &M) return;

            // nothing to add if M is empty
            if (M.sz == 0) return;

            // the real first and last nodes of M
            Node* mFirst = M.header->next;
            Node* mLast  = M.trailer->prev;

            // Case 1: current list is empty
            if (sz == 0) {
                header->next  = mFirst;
                mFirst->prev  = header;
                trailer->prev = mLast;
                mLast->next   = trailer;
            }
            // Case 2: both non-empty — splice M after our last real node
            else {
                Node* ourLast = trailer->prev;
                ourLast->next = mFirst;
                mFirst->prev  = ourLast;
                mLast->next   = trailer;
                trailer->prev = mLast;
            }

            sz += M.sz;

            // reset M to empty using its own sentinels
            M.header->next  = M.trailer;
            M.trailer->prev = M.header;
            M.sz = 0;
        }
    public:
        class iterator {
            friend class DoublyLinkedList;
            private:
                Node* node_ptr;
            public:
                iterator(Node* ptr = nullptr) : node_ptr{ptr} {}
                T& operator*() const {
                    return node_ptr->elem;
                }
                T* operator->() const {
                    return &node_ptr->elem;
                }
                iterator& operator++() {
                    node_ptr = node_ptr->next;
                    return *this;
                }
                iterator operator++(int) {
                    iterator old(*this);
                    ++(*this);
                    return old;
                }
                iterator& operator--() {
                    node_ptr = node_ptr->prev;
                    return *this;
                }
                iterator operator--(int) {
                    iterator old(*this);
                    --(*this);
                    return old;
                }
                bool operator==(const iterator& other) const {
                    return node_ptr == other.node_ptr;
                }
                bool operator!=(const iterator& other) const {
                    return node_ptr != other.node_ptr;
                }
        };
        class const_iterator {
            private:
                const Node* node_ptr;
            public:
                const_iterator(const Node* ptr = nullptr) : node_ptr{ptr} {}
                const T& operator*() const {
                    return node_ptr->elem;
                }
                const T* operator->() const {
                    return &node_ptr->elem;
                }
                const_iterator& operator++() {
                    node_ptr = node_ptr->next;
                    return *this;
                }
                const_iterator operator++(int) {
                    const_iterator old(*this);
                    ++(*this);
                    return old;
                }
                const_iterator& operator--() {
                    node_ptr = node_ptr->prev;
                    return *this;
                }
                const_iterator operator--(int) {
                    const_iterator old(*this);
                    --(*this);
                    return old;
                }
                bool operator==(const const_iterator& other) const {
                    return node_ptr == other.node_ptr;
                }
            bool operator!=(const const_iterator& other) const {
                    return node_ptr != other.node_ptr;

            }
        };

    public:
        iterator begin() {
            return iterator(header->next);
        }
        const_iterator begin() const {
            return const_iterator(header->next);
        }
        iterator end() {
            return iterator(trailer);
        }
        const_iterator end() const {
            return const_iterator(trailer);
        }
        iterator insert(iterator it, const T& elem) {
            Node* node = it.node_ptr;
            Node* newnode = insert_before(elem, node);
            return iterator(newnode);
        }
        iterator erase(iterator it) {
            Node* node = it.node_ptr;
            ++it;
            erase(node);
            return it;
        }
    private:
        void clone(const DoublyLinkedList& other) {
            for (T e : other) {
                push_back(e);
            }
        }
    public:
        friend void swap(DoublyLinkedList& a, DoublyLinkedList& b) {
            std::swap(a.sz, b.sz);
            std::swap(a.header, b.header);
            std::swap(a.trailer, b.trailer);
        }
        void clear() {
            while (sz > 0) {
                pop_front();
            }
        }
        DoublyLinkedList(const DoublyLinkedList& other) {
            create_sentinels();
            clone(other);
        }
        DoublyLinkedList& operator=(const DoublyLinkedList& other) {
            if (this != &other) {
                clear();
                clone(other);
            }
            return *this;
        }
        DoublyLinkedList(DoublyLinkedList&& other) {
            create_sentinels();
            swap(*this, other);
        }
        DoublyLinkedList& operator=(DoublyLinkedList&& other) {
            if (this != &other) {
                swap(*this, other);
            }
            return *this;
        }
        ~DoublyLinkedList() {
            clear();
            delete header; delete trailer;
        }
        void print() const;
};
}  // namespace dsac::list