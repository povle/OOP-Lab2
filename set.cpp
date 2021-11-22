#include "set.h"
#include <list>
#include <functional>

//https://www.geeksforgeeks.org/implementing-hash-table-open-addressing-linear-probing-cpp/

template <typename T>
T Set<T>::Iterator::operator*() const
{
    return set->buckets[curr_bucket][curr_pos];
}

template <typename T>
bool Set<T>::Iterator::operator<(const Iterator &other) const {
    return this->set == other.set
            && (this->curr_bucket < other.curr_bucket
                || (this->curr_bucket == other.curr_bucket && this->curr_pos < other.curr_pos));
}

template <typename T>
bool Set<T>::Iterator::operator==(const Iterator &other) const {
    return this->set == other.set
           && this->curr_bucket == other.curr_bucket
           && this->curr_pos == other.curr_pos;
}

template <typename T>
bool Set<T>::Iterator::operator<=(const Iterator &other) const {
    return (*this) == other || (*this) < other;
}

template <typename T>
bool Set<T>::Iterator::operator>=(const Iterator &other) const {
    return !((*this) < other);
}

template <typename T>
bool Set<T>::Iterator::operator>(const Iterator &other) const {
    return !((*this) <= other);
}

template <typename T>
bool Set<T>::Iterator::operator!=(const Iterator &other) const {
    return !(*this==other);
}


template <typename T>
typename Set<T>::Iterator &Set<T>::Iterator::operator++()
{
    if ((*this) >= set->end()){
        throw std::out_of_range("++ on iterator pointing at or past last element");
    }

    curr_pos++;

    if (curr_pos >= set->buckets[curr_bucket].size())
        curr_pos = 0;

    while ((curr_pos >= set->buckets[curr_bucket].size()) && (*this) < set->end())
    {
        curr_bucket++;
    }

    return *this;
}




template <typename T>
typename Set<T>::Iterator Set<T>::begin() const {
    return Iterator(min_bucket, 0);
}

template <typename T>
typename Set<T>::Iterator Set<T>::end() const {
    return Iterator(max_bucket, buckets[max_bucket].size()-1);
}


template <typename T>
Set<T>::Set()
{
    size = 0;
    capacity = 199;
    max_load_factor = 0.75;
    buckets = new std::list<T>[capacity];
    for (int i = 0; i < capacity; i++)
        buckets[i] = NULL;
}


template <typename T>
bool Set<T>::place(T obj, std::list<T> *buckets, unsigned int capacity)
{
    unsigned int pos = std::hash<T>()(obj) % capacity;
    if (buckets[pos] == NULL) {
        buckets[pos] = std::list<T>();
    }

    buckets[pos].push_back(obj);
}

template <typename T>
bool Set<T>::add(T obj)
{
    if (get_load_factor() > max_load_factor)
        grow();

    place(obj, buckets, capacity);

    return true; //FIXME
}

template <typename T>
void Set<T>::grow()
{
    unsigned int new_capacity = capacity * 2;
    std::list<T> *new_buckets = new std::list<T>[new_capacity];

}


template <typename T>
float Set<T>::get_load_factor()
{
    return float(size)/float(capacity);
}
