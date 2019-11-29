//
// Created by gnomex on 29.11.19.
//

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
