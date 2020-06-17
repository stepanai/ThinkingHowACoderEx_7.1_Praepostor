//
// Created by stepanai on 17.04.2020.
//

#ifndef STUDENT_RECORD_STUDENTRECORD_H
#define STUDENT_RECORD_STUDENTRECORD_H
#include <string>

//class string;

class studentRecord {
public:
    //Конструкторы
    friend class studentCollection;
    studentRecord();
    studentRecord(int newGrade,int newID, std::string newName);
    //Геттеры и Сеттеры
    int grade()const;
    void setGrade(int newGrade)&;
    int studentID()const;
    void setStudentID(int newID)&;
    std::string const& name()const;
    void setName(std::string newName)&;
    //Показать сведения о студенте
    void show()const;
    //получить символьное представление оценки
    std::string letterGrade()const;
private:
    //Члены класса
    int _grade{};
    int _studentID{};
    std::string _name;
    //friend bool isValidGrade(int);
};

bool isValidGrade(int);


#endif //STUDENT_RECORD_STUDENTRECORD_H
