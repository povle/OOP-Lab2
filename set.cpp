#include "set.h"
#include <list>
#include <functional>
#include <iostream>

template <typename T>
T Set<T>::Iterator::operator*() const
{
    return *it;
}



template <typename T>
bool Set<T>::Iterator::operator==(const Set<T>::Iterator &other) const {
    return this->set == other.set
           && this->curr_bucket == other.curr_bucket
           && this->it == other.it;
}

template <typename T>
bool Set<T>::Iterator::operator!=(const Set<T>::Iterator &other) const {
    return !(*this==other);
}


template <typename T>
typename Set<T>::Iterator &Set<T>::Iterator::operator++()
{
    if ((*this) == set->end()){
        throw std::out_of_range("++ on iterator pointing past last element");
    }

    ++it;


    if (it == set->buckets[curr_bucket].end() && (*this) != set->end())
    {
        curr_bucket++;
        while ((set->buckets[curr_bucket].empty()) && curr_bucket < set->capacity)
            curr_bucket++;
        it = set->buckets[curr_bucket].begin();
    }
    return *this;
}



template <typename T>
typename Set<T>::Iterator Set<T>::begin() const {
    return Iterator(this, min_bucket, buckets[min_bucket].begin());
}

template <typename T>
typename Set<T>::Iterator Set<T>::end() const {
    return Iterator(this, max_bucket, buckets[max_bucket].end());
}


template <typename T>
Set<T>::Set()
{
    size = 0;
    capacity = 199;
    buckets = new std::list<T>[capacity];
    for (unsigned int i = 0; i < capacity; i++)
        buckets[i] = std::list<T>();
}

template <typename T>
Set<T>::~Set()
{
    delete [] buckets;
}


template <typename T>
unsigned int Set<T>::place(T obj, std::list<T> *buckets, unsigned int capacity)
{
    unsigned int bucket = std::hash<T>()(obj) % capacity;
    buckets[bucket].push_back(obj);
    return bucket;
}

template <typename T>
bool Set<T>::add(const T obj)
{
    if ((*this)[obj])
        return false;

    size++;

    if (get_load_factor() > max_load_factor)
        grow();

    unsigned int bucket = place(obj, buckets, capacity);

    if (size == 1)
    {
        max_bucket = bucket;
        min_bucket = bucket;
    }
    else if (bucket > max_bucket)
    {
        max_bucket = bucket;
    }
    else if (bucket < min_bucket)
    {
        min_bucket = bucket;
    }

    return true;
}


template <typename T>
bool Set<T>::operator<<(const T obj)
{
    return add(obj);
}

template <typename T>
bool Set<T>::operator[](const T obj)
{
    unsigned int bucket = std::hash<T>()(obj) % capacity;

    for (auto iter = buckets[bucket].begin(); iter != buckets[bucket].end(); ++iter)
        if ((*iter) == obj)
            return true;

    return false;
}



template <typename T>
void Set<T>::grow()
{
    unsigned int new_capacity = capacity * 2;
    std::list<T> *new_buckets = new std::list<T>[new_capacity];

    for (auto iter = begin(); iter != end(); ++iter)
    {
        place(*iter, new_buckets, new_capacity);
    }

    delete [] buckets;
    buckets = new_buckets;
}


template <typename T>
float Set<T>::get_load_factor() const
{
    return float(size)/float(capacity);
}
