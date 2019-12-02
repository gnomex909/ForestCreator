//
// Created by obire on 27.11.2019.
//

#include "Cell.h"


Cell::Cell() {}

Cell::Cell(double height, double fireRate) : height(height), fire_rate(fireRate) {}

double Cell::getHeight() const {
    return height;
}

void Cell::setHeight(double height) {
    Cell::height = height;
}

double Cell::getFireRate() const {
    return fire_rate;
}

void Cell::setFireRate(double fireRate) {
    fire_rate = fireRate;
}

double Cell::getState() const {
    return state;
}

void Cell::setState(double state) {
    Cell::state = state;
}

int Cell::getTurnOfBurning() const {
    return turn_of_burning;
}

void Cell::setTurnOfBurning(int turnOfBurning) {
    turn_of_burning = turnOfBurning;
}


