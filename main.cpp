#include <iostream>
#include "Forest.h"
#include "Fire.h"
#include "JsonFileInterface.h"

int main() {
    Forest forest(101,101);
//    forest.setDataFunction(HEIGHT,3,{1,10,1.5,-0.1},2,{0,0,-0.5,-1,-1},0,10);
//    std::cout<<forest.showData(HEIGHT)<<std::endl;
//    forest.setDataFunction(HEIGHT,1,{0,10.0,-1,-1},0,{0,0,0,0,0},0,0);
//    forest.setAreaValue(RATE,0.0,31,51,61,71);
    Fire fire(forest);
//    fire.setWind(EAST,1.3);
//    fire.setWind(NORTHEAST,1.1);
//    fire.setWind(SOUTHEAST,1.1);
//    fire.setWind(WEST,0.8);
//    fire.setWind(NORTHWEST,0.9);
//    fire.setWind(SOUTHWEST, 0.9);
    fire.startFire(51,51,1.0);
    for(int i=0;i<1000;i++){
       if(fire.simNextStep()==1){
           break;
       }
    }
    JsonFileInterface::createFireJson(fire, "test");
    return 0;
}
//-0.10x^3+1.5x^2+10x+1