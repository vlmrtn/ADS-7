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
    if (light) {
        countOp++;
    }
}
int Train::getLength() {
    if (!first) return 0;
    countOp = 0;
    Cage* currentCar = first;
    int distance = 0;
    if (!currentCar->light) {
        currentCar->light = true;
        countOp++;
    }
    while (true) {
        currentCar = currentCar->next;
        distance++;
        countOp++;
        if (currentCar->light) {
            currentCar->light = false;
            countOp++;
            for (int stepsBack = 0; stepsBack < distance; stepsBack++) {
                currentCar = currentCar->prev;
                countOp++;
            }
            if (currentCar == first && !currentCar->light) {
                return distance;
            }

            distance = 0;
        }
    }
}
int Train::getOpCount() const {
    return countOp;
}
void Train::toggleLight(Cage* cage) {
    if (cage) {
        if (cage->light) {
            countOp--;
        } else {
            countOp++;
        }
        cage->light = !cage->light;
    }
}
