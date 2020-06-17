//
// Created by stepanai on 19.04.2020.
//

#ifndef STUDENT_COLECTION_STUDENTCOLLECTION_H
#define STUDENT_COLECTION_STUDENTCOLLECTION_H

#include "studentRecord.h"

//class studentRecord;


class studentCollection {
public:
    struct studentNode{
        studentRecord const*studentData;
        studentNode *next;
        bool isDynamic;
        bool isConst;
        studentNode()=default;
        studentNode(const studentNode &oldNode);
        studentNode(studentNode &&tempNode);
        studentNode(studentRecord &&a);
        studentNode(studentRecord&);
        studentNode(studentRecord const&);
        //studentNode(const studentNode &a){}
        //studentNode(studentNode &&a){}
        studentNode& operator=(const studentNode &a);
        studentNode& operator=(studentNode &&a);
        ~studentNode();
    };
public:
    studentCollection();
    studentCollection(std::initializer_list<studentNode> &&_l);
    studentCollection(const studentCollection &original);
    studentCollection(studentCollection &&original);
    ~studentCollection();

    studentCollection& operator=(const studentCollection &oldCollection);
    studentCollection& operator=(studentCollection &&oldCollection);

    void addRecord(studentRecord const&newStudent);
    void addRecord(studentRecord &newStudent);
    void addRecord(studentRecord&&);

    studentRecord const* recordWithNumber(int id);
    void print();
    void removeRecord(int id);
    void optimize();

private:
    studentNode *_listHead;
    bool (*_praepostorPolicy)(studentRecord r1,studentRecord r2);
    void deleteList();
    studentNode* copyCollection(const studentNode *original);
};


#endif //STUDENT_COLECTION_STUDENTCOLLECTION_H
