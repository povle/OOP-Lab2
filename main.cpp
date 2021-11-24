//#include "mainwindow.h"

//#include <QApplication>

//int main(int argc, char *argv[])
//{
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
//    return a.exec();
//}


#include "set.h"
#include "set.cpp"
#include "string.h"
#include <iostream>


int main()
{
    Set<int> s, j;


    s << 3;
    s << 2;
    s << 1;
    s << 4;

    for (auto i = s.begin(); i != s.end(); ++i)
        std::cout << (*i) << std::endl;

    s.remove(3);


    for (auto i = s.begin(); i != s.end(); ++i)
        std::cout << (*i) << std::endl;

//    j << 2;
//    j << 4;
//    j << 6;
//    j << 8;

//    Set<int> is = s&&j;

////    std::cout << int(s == j) << std::endl;

////    auto i = s.end();

////    std::cout << i.curr_bucket << std::endl;

////    auto j = s.begin();
////    ++i;


//    for (auto i = is.begin(); i != is.end(); ++i)
//        std::cout << (*i) << std::endl;
}
