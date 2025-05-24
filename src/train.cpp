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
}
int Train::getLength() {
    if (!first) return 0;
    countOp = 0;
    Cage* current = first;
    if (!current->light) {
        current->light = true;
    }
    int length = 1;
    while (true) {
        current = current->next;
        countOp++;
        if (!current->light) {
            length++;
            continue;
        } else {
            current->light = false;
            int steps = length;
            while (steps--) {
                current = current->prev;
            }
            if (!current->light) {
                return length;
            } else {
                steps = length;
                while (steps--) {
                    current = current->next;
                }
                length++;
                continue;
            }
        }
    }
}
int Train::getOpCount() const {
    return countOp;
}
