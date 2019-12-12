//
// Created by obire on 27.11.2019.
//

#ifndef FORESTCREATOR_CELL_H
#define FORESTCREATOR_CELL_H

static const int FUEL = 0;
static const int BURNING = 1;
static const int BURNED = 2;
static const int NFUEL = -1;
class Cell {
    //Height of the cell
    double height = 10;
    //Rate of burning, right now 1.0 means it will be fully burned in 1 time step
    double fire_rate = 0.25;
    //State of the cell
    double state =0.0;
    //Status of the cell, according to the model;
    int status = FUEL;
    //Turn during which it got burned fully
    int turn_of_burning = -1;
public:
    Cell();

    Cell(double height, double fireRate);

    double getHeight() const;

    int getStatus() const;

    void setStatus(int status);

    void setHeight(double height);

    double getFireRate() const;

    void setFireRate(double fireRate);

    double getState() const;

    void setState(double state);

    int getTurnOfBurning() const;

    void setTurnOfBurning(int turnOfBurning);
};


#endif //FORESTCREATOR_CELL_H
