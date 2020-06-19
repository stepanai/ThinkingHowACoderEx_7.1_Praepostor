//
// Created by stepanai on 19.04.2020.
//
#include <iostream>
#include <cstring>
#include "studentCollection.h"
#include "studentRecord.h"
#include "scIterator.h"

studentCollection::studentCollection() {
    _listHead=nullptr;
    _praepostorPolicy=nullptr;
}

studentCollection::studentCollection(std::initializer_list<studentNode> &&_l) {
    _listHead=nullptr;

    for (unsigned long i=0;i<_l.size();++i){
        studentNode *newNode=new studentNode;
        *newNode=_l.begin()[i];
        newNode->next=_listHead;
        _listHead=newNode;
        //static ListItem *temp;
        //temp=new ListItem;
        //p->next=temp;
        //addRecord(_l.begin()[i]);
        //temp->value=_l.begin()[i].value;
        //p=temp;
        //++count;
    }
}

void studentCollection::addRecord(const studentRecord &newStudent) {
    optimize();
    studentNode *newNode=new studentNode;
    newNode->studentData=&newStudent;
    newNode->isDynamic=false;
    newNode->isConst=true;
    newNode->next=_listHead;
    _listHead=newNode;
}
void studentCollection::addRecord(studentRecord &newStudent) {
    optimize();
    studentNode *newNode=new studentNode;
    newNode->studentData=&newStudent;
    newNode->isDynamic=false;
    newNode->isConst=false;
    newNode->next=_listHead;
    _listHead=newNode;
}

void studentCollection::addRecord(studentRecord &&newStudent) {
    optimize();
    studentNode *newNode=new studentNode;
    //newNode->studentData=new studentRecord(newStudent.grade(),newStudent.studentID(),newStudent.name());
    newNode->studentData=new studentRecord(std::move(newStudent));
    newNode->isDynamic=true;
    newNode->isConst=false;
    newNode->next=_listHead;
    _listHead=newNode;
}

studentRecord const*studentCollection::recordWithNumber(int id) {
    optimize();
    studentNode *p=_listHead;
    while(p && p->studentData->studentID()!=id)
        p=p->next;
    if (p)
        return p->studentData;
    else
        return nullptr;
}

void studentCollection::print() {
    optimize();
    studentNode *p=_listHead;
    while (p) {
        p->studentData->show();
        std::cout<<std::endl;
        p=p->next;
    }
}

void studentCollection::removeRecord(int id) {
    optimize();
    studentNode *p=_listHead;
    studentNode *prev=nullptr;
    while (p && p->studentData->studentID()!=id){
        prev=p;
        p=p->next;
    }
    if (!p)
        return;
    if (!prev)
        _listHead=_listHead->next;
    else
        prev->next=p->next;
    delete p;
}

void studentCollection::optimize() {
    studentNode *p=_listHead;
    studentNode *prev=nullptr;
    while (p){
        if (p->studentData->_grade==0 && p->studentData->_studentID!=-1) {
            if (prev)
                prev->next=p->next;
            else
                _listHead=_listHead->next;
            studentNode *temp=p;
            p=p->next;
            //temp->~studentNode();
            delete temp;
        }
        else{
            prev=p;
            p=p->next;
        }

    }
}

void studentCollection::deleteList() {
    while (_listHead){
        studentNode *temp=_listHead;
        _listHead=_listHead->next;
        delete temp;
    }
}

studentCollection::~studentCollection() {
    deleteList();
}

studentCollection::studentNode* studentCollection::copyCollection(const studentCollection::studentNode *original) {
    if (!original)
        return nullptr;
    studentNode *newCollection=new studentNode(*original);
    studentNode *oldP=original->next;
    studentNode *newP=newCollection;
    while (oldP){
        newP->next=new studentNode(*oldP);
        newP=newP->next;
        oldP=oldP->next;
    }
    newP->next=nullptr;
    return newCollection;
}

studentCollection &studentCollection::operator=(const studentCollection &old) {
    if (_listHead!=old._listHead){
        deleteList();
        _listHead=copyCollection(old._listHead);
    }
    return *this;
}

studentCollection &studentCollection::operator=(studentCollection &&old) {
    if (_listHead!=old._listHead){
        deleteList();
        _listHead=old._listHead;
        old._listHead=nullptr;
    }
    return *this;
}

studentCollection::studentCollection(const studentCollection &original) {
    _listHead=copyCollection(original._listHead);
}

studentCollection::studentCollection(studentCollection &&original) {
    _listHead=original._listHead;
    original._listHead=nullptr;
}

void studentCollection::setPraepostorPolicy(bool (*praepostorPolicy)(studentRecord, studentRecord)) {
    _praepostorPolicy=praepostorPolicy;
}

studentRecord studentCollection::praepostorStudent() const {
    if (!_listHead || !_praepostorPolicy){
        return studentRecord(-1,-1,"");
    }
    studentNode *p=_listHead;
    studentRecord praepostor=*p->studentData;
    p=p->next;
    while (p){
        if ((*_praepostorPolicy)(*p->studentData,praepostor)){
            praepostor=*p->studentData;
        }
        p=p->next;
    }
    return praepostor;
}

studentRecord studentCollection::recordAt(int position)const {
    studentNode *p=_listHead;
    int i=1;
    while (p && i<position){
        ++i;
        p=p->next;
    }
    if (!p)
        return studentRecord(-1,-1,"");
    else
        return *p->studentData;
}

studentCollection::studentNode* studentCollection::firstItemIterator()const {
    //return scIterator(_listHead);
    return _listHead;
}


studentCollection::studentNode::~studentNode() {
    if (isDynamic)
        delete studentData;
    studentData=nullptr;
}

studentCollection::studentNode::studentNode(studentRecord &&a) {
    //studentData=new studentRecord(a.grade(),a.studentID(),a.name());
    //studentData=&a;
    studentData=new studentRecord(std::move(a));
    isDynamic=true;
    isConst=false;
    next=nullptr;
}

studentCollection::studentNode::studentNode(studentRecord &aa) {
    studentData=&aa;
    isDynamic=false;
    isConst=false;
    next=nullptr;
}

studentCollection::studentNode::studentNode(const studentRecord &aa) {
    studentData=&aa;
    isDynamic=false;
    isConst=true;
    next=nullptr;
}

studentCollection::studentNode& studentCollection::studentNode::operator=(const studentCollection::studentNode &a) {
    if (isDynamic)
        delete studentData;
    if (a.isDynamic) {

        //studentData=new studentRecord(a.studentData->_grade,a.studentData->_studentID,a.studentData->_name);
        studentData=new studentRecord(*(a.studentData));
        //studentData=a.studentData;
    }
    else{
        studentData=a.studentData;
    }
    //a.studentData=nullptr;
    next=nullptr;
    isDynamic=a.isDynamic;
    isConst=a.isConst;
    return *this;
}

studentCollection::studentNode &studentCollection::studentNode::operator=(studentCollection::studentNode &&a) {
    if (isDynamic)
        delete studentData;
    studentData=a.studentData;
    a.studentData=nullptr;
    next=nullptr;
    isDynamic=a.isDynamic;
    isConst=a.isConst;
    return *this;
}

studentCollection::studentNode::studentNode(const studentCollection::studentNode &oldNode) {
    if (oldNode.isDynamic)
        studentData=new studentRecord(*(oldNode.studentData));
    else
        studentData=oldNode.studentData;
    next=nullptr;
    isDynamic=oldNode.isDynamic;
    isConst=oldNode.isConst;
}

studentCollection::studentNode::studentNode(studentCollection::studentNode &&tempNode) {
    studentData=tempNode.studentData;
    tempNode.studentData=nullptr;
    next=nullptr;
    isDynamic=tempNode.isDynamic;
    isConst=tempNode.isConst;
};

bool higherGrade(studentRecord r1, studentRecord r2) {
    return r1.grade() > r2.grade();
}

bool lowerStudentNumber(studentRecord r1, studentRecord r2) {
    return r1.studentID()<r2.studentID();
}

bool nameComesFirst(studentRecord r1, studentRecord r2) {
    return strcmp(r1.name().c_str(), r2.name().c_str())<0;
}
