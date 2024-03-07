#include <iostream>
#include "Header.h"

using namespace std;

int main() {
    double_list<int> list1;

   /* list1.push_back(1);
    list1.push_back(5);
    list1.push_back(6);*/


    list1.push_front(1);
    list1.push_front(5);
    list1.push_front(6);

    list1.show_list();
   

    
   return 0;
}