// Copyright 2021 NNTU-CS
#include "train.h"
Train::Train() : first(nullptr), countOp(0) {}

Train::~Train() {
    if (!first) return;

    Cage* current = first->next;
    while (current != first) {
        Cage* next = current->next;
        delete current;
        current = next;
    }
    delete first;
}
void Train::addCar(bool light) {
    Cage* newCage = new Cage{light, nullptr, nullptr};
    if (!first) {
        first = newCage;
        first->next = first;
        first->prev = first;
    } else {
        Cage* last = first->prev;
        last->next = newCage;
        newCage->prev = last;
        newCage->next = first;
        first->prev = newCage;
    }
    if (light) countOp++;
}


int Train::getLength() {
    if (!first) return 0;
    int length = 0;
    const Cage* current = first;
    do {
        length++;
        current = current->next;
    } while (current != first);
    return length;
}

int Train::getOpCount() const {
    int count = 0;
    if (!first) return 0;
    const Cage* current = first;
    do {
        if (current->light)  count++;
        current = current->next;
    } while (current != first);
    return count;
}

