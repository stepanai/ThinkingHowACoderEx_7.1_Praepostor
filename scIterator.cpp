//
// Created by stepanai on 19.06.2020.
//

#include "scIterator.h"

scIterator::scIterator():current(nullptr) {

}

scIterator::scIterator(studentCollection::studentNode *initial):current(initial) {

}

void scIterator::advance() {
    if (current)
        current=current->next;


}

bool scIterator::pastEnd() const {
    return !current;
}

studentRecord scIterator::student() {
    if (!current)
        return studentRecord(-1,-1,"");
    else
        return *current->studentData;
}
