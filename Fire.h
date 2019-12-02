//
// Created by gnomex on 29.11.19.
//

#ifndef FORESTCREATOR_FIRE_H
#define FORESTCREATOR_FIRE_H


#include <vector>
#include "Forest.h"
static const int NORTH = 0;
static const int SOUTH = 1;
static const int EAST = 2;
static const int WEST = 3;

static const std::vector<int> Y_MOVEMENT{1,-1,0,0,1,1,-1,-1};
static const std::vector<int> X_MOVEMENT{0,0,1,-1,1,-1,1,-1};
class Fire {
    double max_fire_rate = 0;
    std::vector<std::vector<bool>> is_burned_up;
    std::vector<double> winds = {1.0,1.0,1.0,1.0};
    int burned_cell_count = 0;
    int forest_cell_count;
    Forest& forest;
public:
    Fire(Forest &forest);

    void startFire(int x, int y, double state);

    void simNextStep();

    double heightFunction(unsigned int yMain, unsigned int xMain, unsigned int yComp, unsigned int xComp);

    double windFunction(unsigned int currentMovement);

    double rateFunction(unsigned int yMain, unsigned int xMain, unsigned int yComp, unsigned int xComp);

    double proximityFunction(unsigned int currentMovement);

    double getCellState(int x, int y);
};


#endif //FORESTCREATOR_FIRE_H
