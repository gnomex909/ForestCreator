//
// Created by obire on 27.11.2019.
//

#ifndef FORESTCREATOR_CELL_H
#define FORESTCREATOR_CELL_H


class Cell {
    double height = 10;
    double fire_rate = 1.0;
    double state =0.0;
public:
    Cell();

    Cell(double height, double fireRate);

    double getHeight() const;

    void setHeight(double height);

    double getFireRate() const;

    void setFireRate(double fireRate);

    double getState() const;

    void setState(double state);
};


#endif //FORESTCREATOR_CELL_H
