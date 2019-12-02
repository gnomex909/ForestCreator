//
// Created by gnomex on 29.11.19.
//

#include <iostream>
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
}

void Fire::startFire(int x, int y, double state) {
    forest.setCellValue(STATE, state, x,y);
}

double Fire::getCellState(int x, int y) {
    return forest.getForestCells()[y][x].getState();
}

void Fire::simNextStep() {
    std::vector<std::vector<double>> statesCurrentStep;
    for(unsigned int i=0; i<forest.getHeight();i++){
        statesCurrentStep.emplace_back(std::vector<double>());
        for(unsigned int j=0; j<forest.getWidth();j++){
            statesCurrentStep[i].push_back(forest.getForestCells()[i][j].getState());
        }
    }
    std::cout<<"Finished coping"<<std::endl;
    for(unsigned int i=0; i<forest.getHeight();i++){
        for(unsigned int j=0; j<forest.getWidth();j++){
            if(!is_burned_up[i][j]) {
                double newState = forest.getForestCells()[i][j].getState();
                std::cout << "State of [" << j << "," << i << "] at the beggining:" << newState << std::endl;
                for (unsigned int k = 0; k < X_MOVEMENT.size(); k++) {
                    int y = i + Y_MOVEMENT[k];
                    int x = j + X_MOVEMENT[k];
                    std::cout << "Checking if exists: [" << x << "," << y << "]" << std::endl;
                    if (y >= 0 && y < forest.getHeight() && x >= 0 && x < forest.getWidth()) {
                        std::cout << "Correct cell" << std::endl;
                        newState += statesCurrentStep[x][y] * heightFunction(i, j, y, x) *
                                    rateFunction(i, j, y, x) * windFunction(k) * proximityFunction(k);
                        if (newState >= 1.0) {
                            burned_cell_count++;
                            is_burned_up[i][j] = true;
                        }
                        std::cout << "State of [" << j << "," << i << "] after " << k << " change:" << newState
                                  << std::endl;
                    } else {
                        std::cout << "Incorrect cell" << std::endl;
                    }
                }
                forest.setCellValue(STATE, std::min(newState, 1.0), j, i);
            }
        }
    }
    std::cout<<forest.showData(STATE)<<std::endl;
    if(burned_cell_count == forest_cell_count){
        std::cout<<"Forest is burned up"<<std::endl;
    }
}

double Fire::heightFunction(unsigned int yMain, unsigned int xMain, unsigned int yComp, unsigned int xComp) {
    return 1.0;
}

double Fire::windFunction(unsigned int currentMovement) {
    return 1.0;
}

double Fire::rateFunction(unsigned int yMain, unsigned int xMain, unsigned int yComp, unsigned int xComp) {
    return 1.0;
}

double Fire::proximityFunction(unsigned int currentMovement) {
    if(currentMovement<3){
        return 1.0;
    }else{
        return 0.83;
    }
}
