#ifndef SET_H
#define SET_H
#include <list>


template <typename T>
class Set
{
public:
    Set();
    ~Set();
    void remove(T obj);
    bool operator<<(const T obj);
    bool operator[](const T obj) const;
    bool operator==(const Set<T> &other) const;
    bool operator!=(const Set<T> &other) const;
    Set<T> operator&&(const Set<T> &other) const;
    unsigned int get_size() const;


    class Iterator {
        public:
            Iterator() = default;
            Iterator(const Set<T> *set, unsigned int curr_bucket, typename std::list<T>::iterator it) :
                set(set), curr_bucket(curr_bucket), it(it)  {};
            ~Iterator() = default;
            T operator*() const;
            Iterator &operator++();

            bool operator==(const Iterator &other) const;
            bool operator!=(const Iterator &other) const;
        private:
            const Set<T> *set;
            unsigned int curr_bucket;
            typename std::list<T>::iterator it;
        };
    Iterator begin() const;
    Iterator end() const;
private:
    unsigned int size, capacity, min_bucket, max_bucket;
    const float max_load_factor = 0.75;
    float get_load_factor() const;
    void grow();
    bool add(const T obj);
    unsigned int get_bucket(const T obj, unsigned int capacity) const;
    unsigned int place(T obj, std::list<T> *buckets, unsigned int capacity);

    std::list<T> *buckets;
};

#endif // SET_H
