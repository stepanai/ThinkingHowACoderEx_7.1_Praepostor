#include <iostream>
#include "studentCollection.h"
#include "studentRecord.h"

using std::cout;
using std::endl;



int main() {




    studentRecord student1(76,1,"Vova");
    studentCollection::studentNode node1(student1);
    studentCollection::studentNode node2(node1);
    studentRecord const student3(66,3,"Loh");
    studentCollection a2({student1,studentRecord(83,2,"Goga"),student3});
    cout<<"-------------"<<endl;
    studentRecord student4(76,4,"Vova");
    studentRecord *student5=new studentRecord(77,5,"Sova");
    a2.addRecord(student4);
    a2.addRecord(*student5);
    delete student5;
    student5=nullptr;
    a2.optimize();
    studentRecord *student6=new studentRecord(45,6,"Lowiwe");
    a2.addRecord(*student6);
    cout<<"-------------"<<endl;
    a2.optimize();
    //a2.print();
    studentCollection a3(a2);
    a3=studentCollection({student1,*student6});
    a2.removeRecord(4);
    a2.removeRecord(6);
    cout<<"-------------"<<endl;
    a2.print();
    cout<<"-------------"<<endl;
    a3.print();
    return 0;
}
