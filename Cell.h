//
// Created by obire on 27.11.2019.
//

#ifndef FORESTCREATOR_CELL_H
#define FORESTCREATOR_CELL_H


class Cell {
    //Height of the cell
    double height = 10;
    //Rate of burning, right now 1.0 means it will be fully burned in 1 time step
    double fire_rate = 1.0;
    //State of the cell
    double state =0.0;
    //Turn during which it got burned fully
    int turn_of_burning = -1;
public:
    Cell();

    Cell(double height, double fireRate);

    double getHeight() const;

    void setHeight(double height);

    double getFireRate() const;

    void setFireRate(double fireRate);

    double getState() const;

    void setState(double state);

    int getTurnOfBurning() const;

    void setTurnOfBurning(int turnOfBurning);
};


#endif //FORESTCREATOR_CELL_H
