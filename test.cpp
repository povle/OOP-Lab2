#include "test.h"
#include "set.h"
#include "set.cpp"
#include <iostream>

void TestSet()
{
    Set<int> empty;
    assert(empty.get_size() == 0);


    Set<int> s;

    assert(s << 1);
    assert(s.get_size() == 1);
    assert(s << 2);
    assert(s.get_size() == 2);
    assert(!(s<<1));
    assert(s.get_size() == 2);
    assert(s[1]);
    assert(!s[3]);

    s.save("test.txt");
    Set<int> f("test.txt");
    assert(f == s);

    Set<int> copy = Set<int>(s);
    assert(copy == s);

    assert(s.remove(1));
    assert(copy != s);
    assert(s.get_size() == 1);
    assert(!s[1]);

    assert(!s.remove(3));
    assert(s.get_size() == 1);


    assert((s && empty) == empty);


    assert((s && s) == s);

    s.clear();
    assert(s.get_size() == 0);
    assert(s == empty);



    std::cerr << "TestSet(): No errors" << std::endl;
}
