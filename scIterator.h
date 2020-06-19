//
// Created by stepanai on 19.06.2020.
//

#ifndef PRAEPOSTOR_SCITERATOR_H
#define PRAEPOSTOR_SCITERATOR_H

#include "studentCollection.h"

class scIterator {
public:
    scIterator();
    explicit scIterator(studentCollection::studentNode *initial);

    void advance();
    bool pastEnd()const;
    studentRecord student();

private:
    studentCollection::studentNode *current{};
};


#endif //PRAEPOSTOR_SCITERATOR_H
