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
    studentRecord *student5=new studentRecord(77,5,"Bova");
    a2.addRecord(student4);
    a2.addRecord(*student5);
    a2.setPraepostorPolicy(&nameComesFirst);
    a2.print();
    cout<<endl;
    cout<<"Praepoptor is ";
    a2.praepostorStudent().show();
    return 0;
}
