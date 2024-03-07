#pragma once
template <typename T>
class double_list {
public:
    double_list();
    explicit double_list(int n); // OK
    double_list(int n, const T& value); // OK
    double_list(const double_list<T>& list); // OK
    double_list<T>& operator=(double_list<T> other); // OK
       


        

    bool operator==(double_list<T> const& other) const; // OK
    bool operator!=(double_list<T> const& other) const; // OK

    T& front() const; // OK
    T& back() const; // OK
    int size() const; // OK
    bool empty() const; // OK

    T operator[](const int index) const; // OK
    T& operator[](const int index); // OK

    void resize(int n); // TO DO
    void resize(int n, T value); // TO DO

    void push_back(const T& value); // OK
    void push_front(const T& value); // OK

    void insert(int pos, const T& value); // OK
    void insert(int pos, int n, const T& value); // OK
    void insert(int pos, T* begin, T* end); // OK

    void pop_front(); // OK
    void pop_back(); // OK
    void clear(); // OK
    void erase(int index); // OK
    void erase(int begin, int end); // OK
    void show_list();


    static void swap(double_list<T>& list1, double_list<T>& list2) // OK
    {
        using std::swap;
        swap(list1.size_, list2.size_);
        swap(list1.head, list2.head);
        swap(list1.tail, list2.tail);
    }

   


    //1.	Напишіть метод, який буде шукати елемент із заданим ключем у однозв'язному списку.

    int find_value(T value); // OK
        

private:
    template <typename T>
    class node {
    public:

        T value;
        node* previous;
        node* next;
        node() : value(T()), previous(nullptr), next(nullptr) {}
        node(T value, node* previous) : value(value), previous(previous), next(nullptr) {}
        node(T value, node* previous, node* next) : value(value), previous(previous), next(next) {}
        node(T value) : value(value), previous(nullptr), next(nullptr) {}
    };
    node<T>* head;
    node<T>* tail;
    int size_;

    node<T>* find_node(const int index) const; // OK
};




