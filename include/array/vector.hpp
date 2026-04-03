//vector.hpp
#pragma once

#include <algorithm>  //for std::max
#include <stdexcept>  //for std::out_of_range
#include <utility>    //for std::move

namespace dsac::array {

template <typename T>
class Vector {

private:
    int cap{0};
    int sz{0};
    T* data{nullptr};

public:
    //empty
    Vector() = default;
    
    //capacity
    int capacity() const {
        return cap;
    }

    //elements stored
    int size() const {
        return sz;
    }
    
    // True is empty
    bool empty() const {
        return sz == 0;
    }
    
    //element at index when vector is const
    const T& operator[](int i) const {
        return data[i];
    }
    
    //element at index when vector is non-const
    T& operator[](int i) {
        return data[i];
    }
    
    // at function for const
    const T& at(int i) const {
        if (i < 0 || i >= sz) {
            throw std::out_of_range("Invalid Index");
        }
        return data[i];
    }
    
    // at function for non const
    T& at(int i) {
        if (i < 0 || i >= sz) {
            throw std::out_of_range("Invalid Index");
        }
        return data[i];
    }
    
    // first element
    const T& front() const {
        if (empty()) throw std::underflow_error("Queue is empty");
        return data[0];
    }

    // first element
    T& front() {
        if (empty()) throw std::underflow_error("Queue is empty");
        return data[0];
    }
    
    // last element
    const T& back() const {
        if (empty()) throw std::underflow_error("Queue is empty");
        return data[sz - 1];
    }

    // last element
    T& back() {
        if (empty()) throw std::underflow_error("Queue is empty");
        return data[sz - 1];
    }
    
    //capacity >= minimum
    void reserve(int minimum) {
        if (cap < minimum) {
            T* temp{new T[minimum]};
            for (int i{0}; i < sz; i++) {
                temp[i] = std::move(data[i]);
            }
            delete[] data;
            data = temp;
            cap = minimum;
        }
    }

    // insert at end
    void push_back(const T& elem) {
        if (sz == cap) {
            reserve(std::max(1, 2 * cap));
        }
        data[sz++] = elem;
    }

    // called by other functions to reduce cap by half 
    // when sz <= cap/4 
    void shrink() {
        if (sz <= cap / 4) {
            int newcap = std::max(1, cap / 2);
            T* temp{new T[newcap]};
            for (int i{0}; i < sz; i++) {
                temp[i] = std::move(data[i]);
            }
            delete[] data;
            data = temp;
            cap = newcap;
        }
    }

    // remove from end
    // also call shrink
    void pop_back() {
        if (sz > 0) {
            sz--;
            shrink();
        }
    }

    // insert at index
    void insert(int i, const T& elem) {
        if (sz == cap) {
            reserve(std::max(1, 2 * cap));
        }
        for (int k{sz - 1}; k >= i; k--) {
            data[k + 1] = std::move(data[k]);
        }
        data[i] = elem;
        sz++;
    }

    // removes at index
    // also call shrink
    void erase(int i) {
        for (int k{i + 1}; k < sz; k++) {
            data[k - 1] = std::move(data[k]);
        }
        sz--;
        shrink();
    }
    
    // explicitly reduce the cap to sz and keep at least 1 slot
    void shrink_to_fit() {
        int newcap = std::max(1, sz);
        if (newcap < cap) {
            T* temp{new T[newcap]};
            for (int i{0}; i < sz; i++) {
                temp[i] = std::move(data[i]);
            }
            delete[] data;
            data = temp;
            cap = newcap;
        }
    }
    
private:
    void clone(const Vector& other) {
        cap = other.cap;
        sz = other.sz;
        data = new T[cap];
        for (int k = 0; k < sz; k++) {
            data[k] = other.data[k];
        }
    }

    void transfer(Vector& other) {
        cap = other.cap;
        sz = other.sz;
        data = other.data;
        other.cap = other.sz = 0;
        other.data = nullptr;
    }

public: 
    Vector(const Vector& other) {
        clone(other);
    }
    //dsac::array::Vector<int> v_copy = v;

    Vector& operator=(const Vector& other) {
        if (this != &other) {
            delete[] data;
            clone(other);
        }
        return *this;
    }
    //dsac::array::Vector<int> copy_v; v_copy = v;

    Vector(Vector&& other) {
        transfer(other);
    }
    //dsac::array::Vector<int> v_new = std::move(v);
    Vector& operator=(Vector&& other) {
        if (this != &other) {
            delete[] data;
            transfer(other);
        }
        return *this;
    }

    ~Vector() { delete[] data; }    

    public:
        class iterator {
            friend class Vector;
            private:
                Vector* vec;
                int ind;        // index within the vector
            
            public:
                iterator(Vector* v = nullptr, int i = -1)
                    : vec{v}, ind{i} {}
                T& operator*() const {
                    return (*vec)[ind];
                }
                T* operator->() const {
                    return &(*vec)[ind];
                }
                iterator& operator++() {
                    ++ind;
                    return *this;
                }
                iterator operator++(int) {
                    iterator old(*this);
                    ++ind;
                    return old;
                }
                iterator& operator--() {
                    --ind;
                    return *this;
                }
                iterator operator--(int) {
                    iterator old(*this);
                    --ind;
                    return old;
                }
                bool operator==(iterator rhs) const {
                    return vec == rhs.vec && ind == rhs.ind;
                }
                bool operator!=(iterator rhs) const {
                    return !(*this == rhs);
                }
        };

        class const_iterator {
            private:
                const Vector* vec;
                int ind;                   // index within the vector
            
            public:
                const_iterator(const Vector* v = nullptr, int i = -1)
                    : vec{v}, ind{i} {}
                const T& operator*() const {
                    return (*vec)[ind];
                }
                const T* operator->() const {
                    return &(*vec)[ind];
                }
                const_iterator& operator++() {
                    ++ind;
                    return *this;
                }
                const_iterator operator++(int) {
                    const_iterator old(*this);
                    ++ind;
                    return old;
                }
                const_iterator& operator--() {
                    --ind;
                    return *this;
                }
                const_iterator operator--(int) {
                    const_iterator old(*this);
                    --ind;
                    return old;
                }
                bool operator==(const_iterator rhs) const {
                    return vec == rhs.vec && ind == rhs.ind;
                }
                bool operator!=(const_iterator rhs) const {
                    return !(*this == rhs);
                }
        };

        iterator begin() {
            return iterator(this, 0);
        }
        iterator end() {
            return iterator(this, sz);
        }
        const_iterator begin() const {
            return const_iterator(this, 0);
        }
        const_iterator end() const {
            return const_iterator(this, sz);
        }

        iterator insert(iterator it, const T& elem) {
            insert(it.ind, elem);
            return it;
        }

        iterator erase(iterator it) {
            erase(it.ind);
            return it;
        }
    
    

}; //end class Vector
}//end namespace dsac::array

