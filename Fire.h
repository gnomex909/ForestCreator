//
// Created by gnomex on 29.11.19.
//

#ifndef FORESTCREATOR_FIRE_H
#define FORESTCREATOR_FIRE_H


#include <vector>
#include "Forest.h"
#include <random>
//Constants for winds, to make it easier to decide which one to use
static const int NORTH = 0;
static const int SOUTH = 1;
static const int EAST = 2;
static const int WEST = 3;
static const int NORTHEAST = 4;
static const int NORTHWEST = 5;
static const int SOUTHEAST = 6;
static const int SOUTHWEST = 7;
//Movement constants, used for iterating through graph cells
static const std::vector<int> Y_MOVEMENT{-1,1,0,0,-1,-1,1,1};
static const std::vector<int> X_MOVEMENT{0,0,1,-1,1,-1,1,-1};
class Fire {
    //Max fire rate found in graph
    double max_fire_rate = 0;
    //Graph used to optimize simulating next step
    std::vector<std::vector<bool>> is_burned_up;
    //Vector of wind variables
    std::vector<double> winds = {1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0};
    //Vector of graphs, to store how fire progressed during each turn
    std::vector<std::vector<std::vector<double>>> states_during_turns;

    std::vector<std::vector<std::vector<int>>> status_during_turns;
    //Count of burned up cells, used to finish simulation early
    int burned_cell_count = 0;
    //Count of all cells in the forest
    int forest_cell_count;
    //Bool to check if forest is fully burned out
    bool forest_burned_up = false;
    //Reference to forest object, that will be burned
    Forest& forest;
    //Current time step
    int turn=0;
    //Bool to check if data was shown at the end
    bool final_data_shown = false;

    std::mt19937_64 rng;
public:
    /*
     * Main constructor
     * Args:
     * forest - reference to forest we will be burning down
     * Returns:
     * Fire object
     */
    explicit Fire(Forest &forest);
    /*
     * Function used to set state of one cell, to be used at the beginning of simulation to start a fire
     * Args:
     * x, y - coordinates of a desired cell
     * state - state to be set
     */
    void startFire(int x, int y, double state);
    /*
     * Main function, used to simulate changes between time steps. Here one can find main logic behind the process
     * Returns:
     * 0 if forest isn't burned up fully
     * 1 if forest is fully burned up
     */
    int simNextStep();
    /*
     * Function defining how height difference affects simulation
     * Args:
     * yMain,xMain - coordinates of main cell, in the middle
     * yComp,xComp - coordinates of a cell we compare height to
     * Returns:
     * Result of the equation
     */
    double heightFunction(unsigned int yMain, unsigned int xMain, unsigned int yComp, unsigned int xComp);
    /*
     * Function defining how wind affects simulation
     * Args:
     * currentMovement - which cell we are now comparing main cell to
     * Returns:
     * Result of the equation
     */
    double windFunction(unsigned int currentMovement);
    /*
     * Function defining how fire rate affects simulation
     * Args:
     * yMain,xMain - coordinates of main cell, in the middle
     * yComp,xComp - coordinates of a cell we compare fire rate to
     * Returns:
     * Result of the equation
     */
    double rateFunction(unsigned int yMain, unsigned int xMain, unsigned int yComp, unsigned int xComp);
    /*
     * Function defining how status of cell
     * Args:
     * status - status of neighbour cell
     * Returns:
     * Result of the equation
     */
    double statusFunction(int status);
    /*
     * Function used to get state of the cell during current time step
     * Args:
     * x,y - coordinates of the cell
     * Returns:
     * State of the cell in current time step
     */
    double getCellState(int x, int y);

    const std::vector<std::vector<std::vector<int>>> &getStatusDuringTurns() const;

    /*
     * Getters and Setters
     */
    const std::vector<std::vector<std::vector<double>>> &getStatesDuringTurns() const;

    void setStatesDuringTurns(const std::vector<std::vector<std::vector<double>>> &statesDuringTurns);

    Forest &getForest() const;

    void setForest(Forest &forest);

    void setWind(int windDirection, double value);
};


#endif //FORESTCREATOR_FIRE_H
