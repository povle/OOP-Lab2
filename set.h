#ifndef SET_H
#define SET_H
#include <list>


template <typename T>
class Set
{
public:
    Set();
    bool add(T obj);
    class Iterator {
        public:
            T operator*() const;
            Iterator &operator++();
            bool operator==(const Iterator &other) const;
            bool operator!=(const Iterator &other) const;
            bool operator<(const Iterator &other) const;
            bool operator>(const Iterator &other) const;
            bool operator<=(const Iterator &other) const;
            bool operator>=(const Iterator &other) const;
        private:
            Iterator() = default;
            Iterator(unsigned int curr_bucket, unsigned int curr_pos) :
                curr_bucket(curr_bucket), curr_pos(curr_pos) {};
            unsigned int curr_bucket, curr_pos;
            Set *set;
        };
    Iterator begin() const;
    Iterator end() const;
private:
    unsigned int size, capacity, min_bucket, max_bucket;
    float max_load_factor;
    float get_load_factor() const;
    void grow();
    bool place(T obj, std::list<T> *buckets, unsigned int capacity);

    std::list<T> *buckets;
};

#endif // SET_H
