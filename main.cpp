#include <iostream>
#include "studentCollection.h"
#include "studentRecord.h"
#include "scIterator.h"

using std::cout;
using std::endl;

double averageRating(studentCollection const&collection);

int main() {


    studentRecord student1(76,1,"Vova");
    studentCollection::studentNode node1(student1);
    const studentCollection::studentNode& node2(node1);
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
    cout<<endl<<"============="<<endl;

    cout<<"average mark =";
    cout<<averageRating(a2);
    //a2.recordAt(2).show();
    return 0;
}

double averageRating(const studentCollection &collection) {
    scIterator iter(collection.firstItemIterator());
    int gradeTotal=0;
    int numRecords=0;
    while (!iter.pastEnd()){
        ++numRecords;
        gradeTotal+=iter.student().grade();
        iter.advance();
    }
    return static_cast<double>(gradeTotal)/numRecords;
}
