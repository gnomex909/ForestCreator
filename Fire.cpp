//
// Created by gnomex on 29.11.19.
//

#include <iostream>
#include <cmath>
#include <chrono>
#include "Fire.h"

Fire::Fire(Forest &forest) : forest(forest) {
    for(unsigned int i=0; i<forest.getHeight();i++){
        is_burned_up.emplace_back(std::vector<bool>());
        for(unsigned int j=0; j<forest.getWidth();j++){
            is_burned_up[i].push_back(false);
            if(forest.getForestCells()[i][j].getFireRate()>max_fire_rate){
                max_fire_rate=forest.getForestCells()[i][j].getFireRate();
            }
        }
    }
    forest_cell_count = forest.getHeight() * forest.getWidth();
    uint64_t timeSeed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::seed_seq ss{uint32_t(timeSeed & 0xffffffff), uint32_t(timeSeed>>32)};
    rng.seed(ss);
}

void Fire::startFire(const int x,const int y,const double state) {
    forest.setCellValue(STATE, state, x,y);
    forest.setCellValue(STATUS,BURNING,x,y);
    if(state>=1.0){
        forest.setCellValue(STATE,1.0,x,y);
        forest.setCellValue(TURN,0,x,y);
        forest.setCellValue(STATUS,BURNED,x,y);
        is_burned_up[y][x]=true;
        burned_cell_count++;
    }
}

double Fire::getCellState(const int x,const int y) {
    return forest.getForestCells()[y][x].getState();
}

int Fire::simNextStep() {
    // initialize a uniform distribution between 0 and 1
    std::uniform_real_distribution<double> unif(0, 1);
 //We increase time step we are calculating for
    turn++;
    //If forest isn't fully burned up
    if(!forest_burned_up) {
        //We create vector that saves the state of cells from the last turn
        std::vector<std::vector<double>> statesCurrentStep;
        std::vector<std::vector<int>> statusCurrentStep;
        for (unsigned int i = 0; i < forest.getHeight(); i++) {
            statesCurrentStep.emplace_back(std::vector<double>());
            statusCurrentStep.emplace_back(std::vector<int>());
            for (unsigned int j = 0; j < forest.getWidth(); j++) {
                statesCurrentStep[i].push_back(forest.getForestCells()[i][j].getState());
                statusCurrentStep[i].push_back(forest.getForestCells()[i][j].getStatus());
            }
        }
        //We save that state to be saved in JSON later on
        states_during_turns.push_back(statesCurrentStep);
        status_during_turns.push_back(statusCurrentStep);
//        std::cout << "Finished copying" << std::endl;
        //For all cells in forest
        for (unsigned int i = 0; i < forest.getHeight(); i++) {
            for (unsigned int j = 0; j < forest.getWidth(); j++) {
                //We check if it's burned up, if not we calculate it's state
                if (!is_burned_up[i][j]) {
                    //We check if status of the cell is unburned
                    if(forest.getForestCells()[i][j].getStatus()==FUEL){
//                      Our threshold if no neighbours is burning equals 0.0
                        double threshold = 0.0;
                        //Then we add state based on all adjacent cells
                        for (unsigned int k = 0; k < X_MOVEMENT.size(); k++) {
                            int y = i + Y_MOVEMENT[k];
                            int x = j + X_MOVEMENT[k];
//                        std::cout << "Checking if exists: [" << x << "," << y << "]" << std::endl;
                            //Check if cell is actually inside the graph
                            if (y >= 0 && y < forest.getHeight() && x >= 0 && x < forest.getWidth()) {
//                           //We add to result of all the equations
                                threshold += heightFunction(i, j, y, x) *
                                             rateFunction(i, j, y, x) * windFunction(k) * statusFunction(statusCurrentStep[y][x]);
//                            std::cout << "State of [" << j << "," << i << "] after " << k << " change:" << newState
//                                      << std::endl;
                            } else {
//                            std::cout << "Incorrect cell" << std::endl;
                            }

                        }
                        //We roll rundom number between 0 and 1, to check if cell managed to start burning
                        double randomNumber = unif(rng);
                        if(randomNumber<=threshold){
                            forest.setCellValue(STATUS,BURNING,j,i);
                        }
                    }else if(forest.getForestCells()[i][j].getStatus()==BURNING) {
                        //if cell is already burning, we update it's state, by adding fire rate until it's gets to 1.0
                        double newState = forest.getForestCells()[i][j].getState() + forest.getForestCells()[i][j].getFireRate();
                        if (newState >= 1.0) {
                            burned_cell_count++;
                            is_burned_up[i][j] = true;
                            forest.setCellValue(TURN, turn, j, i);
                            forest.setCellValue(STATUS, BURNED, j, i);
                        }
                        //Safety check, to not get state higher than 1.0
                        forest.setCellValue(STATE, std::min(newState, 1.0), j, i);
                    }
                }
            }
        }
//        std::cout << forest.showData(STATE) << std::endl;
//      If we get to the point of having fully burned up forest, we get to this code
        if(burned_cell_count == forest_cell_count){
//            std::cout<<"Forest is burned up"<<std::endl;
            forest_burned_up = true;
            std::vector<std::vector<double>> statesLastTurn;
            //Saving of the states of the cells in the last turn
            for (unsigned int i = 0; i < forest.getHeight(); i++) {
                statesLastTurn.emplace_back(std::vector<double>());
                for (unsigned int j = 0; j < forest.getWidth(); j++) {
                        statesLastTurn[i].push_back(forest.getForestCells()[i][j].getState());
                    }
                }
        }
        //We return 0 unless forest is fully burned up
        return 0;
    }else{
        //Check if data of turns of burning was shown
        if(!final_data_shown){
            std::cout << forest.showData(TURN) << std::endl;
            final_data_shown=true;
        }
        //We return 1 to signal forest is fully burned
        return 1;
    }

}

double Fire::heightFunction(const unsigned int yMain,const unsigned int xMain,const unsigned int yComp,const unsigned int xComp) {
    double mainHeight = forest.getForestCells()[yMain][xMain].getHeight();
    double compHeight = forest.getForestCells()[yComp][xComp].getHeight();
    double diff = mainHeight-compHeight;
    if(diff>0){
        return (1 + (diff/10));
    }else{
        return (pow(2.73, diff));
    }
}

double Fire::windFunction(const unsigned int currentMovement) {
    //We have to remember that northern wind actually comes from NORTH
    switch(currentMovement){
        case 0:
            return winds[NORTH];
        case 1:
            return winds[SOUTH];
        case 2:
            return winds[EAST];
        case 3:
            return winds[WEST];
        case 4:
            return winds[NORTHEAST];
        case 5:
            return winds[NORTHWEST];
        case 6:
            return winds[SOUTHEAST];
        case 7:
            return winds[SOUTHWEST];
        default:
            return 1.0;

    }
}

double Fire::rateFunction(const unsigned int yMain,const unsigned int xMain,const unsigned int yComp,const unsigned int xComp) {
    //We simply compare fire rate of main cell to maximum, to which our time-step is fused to
    if(forest.getForestCells()[yMain][xMain].getFireRate()==0){
        if(!is_burned_up[yMain][xMain]) {
            burned_cell_count++;
            is_burned_up[yMain][xMain] = true;
        }
    }
    return forest.getForestCells()[yMain][xMain].getFireRate()/max_fire_rate;
}

double Fire::statusFunction(const int status) {
    //If neighbour is in those state we return 1/8
    if(status==BURNING || status==BURNED){
        return 0.125;
    }else{
        return 0;
    }
}

const std::vector<std::vector<std::vector<double>>> &Fire::getStatesDuringTurns() const {
    return states_during_turns;
}

void Fire::setStatesDuringTurns(const std::vector<std::vector<std::vector<double>>> &statesDuringTurns) {
    states_during_turns = statesDuringTurns;
}

Forest &Fire::getForest() const {
    return forest;
}

void Fire::setForest(Forest &forest) {
    Fire::forest = forest;
}

void Fire::setWind(int windDirection,double value) {
    Fire::winds[windDirection]= value;
}

const std::vector<std::vector<std::vector<int>>> &Fire::getStatusDuringTurns() const {
    return status_during_turns;
}
