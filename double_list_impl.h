#pragma once

#include "double_list.h"
#include <iostream>
template <typename T>
double_list<T>::double_list() : head(nullptr), tail(nullptr), size_(0) {}

template <typename T>
void double_list<T>::push_back(const T& value) {
    if (head == nullptr) {
        head = new node<T>(value);
        tail = head;
    }
    else {
        tail->next = new node<T>(value, tail);
        tail = tail->next;
    }
    size_++;
}
template<typename T>
inline void double_list<T>::push_front(const T& value)
{
    if (head == nullptr) {
        head = new node<T>(value);
        tail = head;
    }
    else {
        head->previous = new node<T>(value, nullptr, head);
        head = head->previous;
    }
    size_++;
}



template <typename T>
double_list<T>::double_list(int n, const T& value) : double_list()
{
    while (n--)
        push_back(value);
}


template <typename T>
double_list<T>::double_list(int n) : double_list(n, T())
{ }

template <typename T>
double_list<T>& double_list<T>::operator=(double_list<T> other) {
    swap(*this, other);
    return *this;
}
template <typename T>
double_list<T>::double_list(const double_list<T>& other) : double_list()
{
    if (!other.empty()){
        node<T>* current = other.head;
        while(current != nullptr) {
            push_back(current->value);
            current = current->next;
        }
    }

}


template<typename T>
inline bool double_list<T>::operator==(double_list<T> const& other) const
{
    if (this->head == nullptr && other.head == nullptr)
        return true;
    if (this->head == nullptr || other.head == nullptr)
        return false;
    if (this->size_ != other.size_)
        return false;

    node<T>* current_this = this->head;
    node<T>* current_other = other.head;


    while (current_this != nullptr && current_other != nullptr) {
        if (current_this->value != current_other->value)
            return false;
        current_this = current_this->next;
        current_other = current_other->next;
    }
    return true;
}


template<typename T>
inline bool double_list<T>::operator!=(double_list<T> const& other) const
{
    return !(*this == other);
}

template<typename T>
inline void double_list<T>::pop_front()
{
    // size > 0
    size_--;
    node<T>* temp = head;
    head = head->next;
    if(head != nullptr)
        head->previous = nullptr;
    delete temp;
    if (size_ == 0)
        tail = nullptr;
}
template<typename T>
inline void double_list<T>::pop_back() {
    // size > 0
    size_--;
    node<T>* temp = tail;
    tail = tail->previous;
    delete temp;
    if(tail != nullptr)
        tail->next = nullptr;
    if (size_ == 0)
        head = nullptr;
    
}
template <typename T>
void double_list<T>::clear() {
    while (size_)
        pop_front();
}


template<typename T>
inline T& double_list<T>::front() const
{
    // size > 0
    return head->value;
}

template<typename T>
inline T& double_list<T>::back() const
{
    // size > 0
    return tail->value;
}

template<typename T>
inline bool double_list<T>::empty() const
{
    return !size_;
}


template<typename T>
inline int double_list<T>::size() const
{
    return size_;
}


template<typename T>
inline void double_list<T>::insert(int pos, const T& value) {
    insert(pos, 1, value);
}
template<typename T>
inline void double_list<T>::insert(int pos, int n, const T& value) {
    if (empty()) {
        while (n--)
            push_back(value);
        return;
    }
    size_ += n;
    node<T>* found_position = find_node(pos);

    while (n--) {
        found_position->previous = new node<T>(value, found_position->previous, found_position);
        found_position = found_position->previous;
        if(found_position->previous != nullptr)
            found_position->previous->next = found_position;
    }
    if (pos == 0)
        head = found_position;
    
}
template<typename T>
inline void double_list<T>::insert(int pos, T* begin, T* end) {
    if (empty()) {
        while (begin != end)
            push_back(*(begin++));
        return;
    }
    
    node<T>* found_position = find_node(pos);

    size_ += end - begin;

    while (begin !=  end) {
        found_position->previous = new node<T>(*begin, found_position->previous, found_position);
        found_position = found_position->previous;
        if (found_position->previous != nullptr)
            found_position->previous->next = found_position;
        begin++;
    }
    if (pos == 0)
        head = found_position;

}


template<typename T>
inline void double_list<T>::erase(int index) {
    // index < size
    //erase(index, index);
    node<T>* found_position = find_node(index);
    if (found_position->next != nullptr)
        found_position->next->previous = found_position->previous;
    else
        tail = tail->previous;

    if (found_position->previous != nullptr)
        found_position->previous->next = found_position->next;
    else
        head = head->next;
    size_--;
    delete found_position;

}
template<typename T>
inline void double_list<T>::erase(int begin, int end) {
    // begin <= end < size
    // end - begin <= size-1


    int start_position = (size_ - end > begin) ? begin : end;
    node<T>* found_position = find_node(start_position);

    if (start_position == begin) {
        while (begin != (end--) + 1) {
            erase(begin);
        }
    }
    else 
        while (end != begin - 1)
        erase(end--);


    
    

}


template<typename T>
typename double_list<T>::node<T>* double_list<T>::find_node(const int index) const {
    // index < size
    node<T>* found_position;
    int counter;
    if (index < size_ / 2) {
        found_position = head;
        counter = 0;
        while (counter != index) {
            counter++;
            found_position = found_position->next;
        }
    }
    else {
        found_position = tail;
        counter = size_ - 1;
        while (counter != index) {
            counter--;
            found_position = found_position->previous;
        }
    }

    return found_position;
}

template<typename T>
T double_list<T>::operator[](const int index) const {
    return find_node(index)->value;
}

template<typename T>
T& double_list<T>::operator[](const int index) {
    return find_node(index)->value;
}

template<typename T>
void double_list<T>::resize(int n) {
    resize(n, T());
}

template<typename T>
void double_list<T>::resize(int n, T value) {
    if (n > size_)
        for (int i = size_; i < n; i++)
            push_back(value);
    else
        while (size_ != n)
            pop_back();
}
template<typename T>
inline int double_list<T>::find_value(T value) {
    if (!empty()) {
        node<T>* current = head;
        for (int i = 0; current != nullptr; i++) {
            if (current->value == value)
                return i;
            current = current->next;
        }
        return -1;
    }
}

template<typename T>
inline void double_list<T>::show_list() {
    using std::cout;
    node<T>* current = head;
    while (current != nullptr) {
        cout << current->value << " ";
        current = current->next;
    }
    cout << "\n";
}