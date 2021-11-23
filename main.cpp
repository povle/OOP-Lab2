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
#include <iostream>


int main()
{
    Set<int> s;
    std::cout << int(s << 1) << std::endl;
    std::cout << int(s << 2) << std::endl;
    std::cout << int(s << 3) << std::endl;
    std::cout << int(s << 1) << std::endl;
//    s << 3;
//    s << 2;

//    auto i = s.end();

//    std::cout << i.curr_bucket << std::endl;

//    auto j = s.begin();
//    ++i;


    for (auto i = s.begin(); i != s.end(); ++i)
        std::cout << (*i) << std::endl;
}
