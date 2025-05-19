// Copyright 2021 NNTU-CS
#include "train.h"
Train::Train() : first(nullptr), countOp(0) {}

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
}

int Train::getLength() {
    if (!first) return 0;
    int length = 0;
    Cage* current = first;
    do {
        length++;
        current = current->next;
    } while (current != first);
    return length;
}

int Train::getOpCount() {
    int count = 0;
    Cage* current = first;
    if (!current) return 0;

    do {
        count++; // 1 операция для каждой лампочки
        current = current->next;
    } while (current != first);

    return count;
}

Train::~Train() {
    if (!first) return;
    Cage* current = first;
    do {
        Cage* next = current->next;
        delete current;
        current = next;
    } while (current != first);
}
