//
// Created by stepanai on 17.04.2020.
//

#include "studentRecord.h"
#include <utility>
#include <iostream>

studentRecord::studentRecord() {
    setGrade(0);
    setStudentID(-1);
    setName("");
}

studentRecord::studentRecord(int newGrade, int newID, std::string newName) {
    setGrade(newGrade);
    setStudentID(newID);
    setName(newName);
    std::string a="sfh";
}

[[maybe_unused]] int studentRecord::grade() const {
    return this->_grade;
}

void studentRecord::setGrade(int newGrade) &{
    if (isValidGrade(newGrade))
        this->_grade=newGrade;
}

int studentRecord::studentID() const {
    return _studentID;
}

void studentRecord::setStudentID(int newID) &{
    _studentID=newID;
}

std::string const& studentRecord::name() const {
    return _name;
}

void studentRecord::setName(std::string newName) &{
    _name=std::move(newName);
}

void studentRecord::show() const {
    std::cout<<studentID()<<":"<<name()<<" GradeScore="<<grade()<<" GradeLetter="<<letterGrade();
}

std::string studentRecord::letterGrade() const {
    if (!isValidGrade(_grade))
        return "ERROR";
    const int NUMBER_CATEGORIES=11;
    const std::string GRADE_LETTER[]={"F","D","D+","C-","C","C+","B-","B","B+","A-","A"};
    const int GRADE_SCORE[]={0,60,67,70,73,77,80,83,87,90,93};
    int category=0;
    while (category<NUMBER_CATEGORIES && GRADE_SCORE[category]<=_grade)
        ++category;

    return GRADE_LETTER[category-1];
}

bool isValidGrade(int grade) {
    return (grade>=0 && grade<=100);
}







