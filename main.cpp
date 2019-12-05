#include <iostream>
#include "Forest.h"
#include "Fire.h"
#include "JsonFileInterface.h"

int main() {
    Forest forest(101,101);
//    forest.setDataFunction(HEIGHT,3,{1,10,1.5,-0.1},2,{0,0,-0.5,-1,-1},0,10);
//    std::cout<<forest.showData(HEIGHT)<<std::endl;
//    forest.setDataFunction(HEIGHT,1,{0,10.0,-1,-1},0,{0,0,0,0,0},0,0);
    forest.setAreaValue(RATE,0.25,31,71,61,71);
    Fire fire(forest);
    fire.startFire(50,50,1.0);
    std::cout<<forest.showData(RATE)<<std::endl;
    for(int i=0;i<500;i++){
       if(fire.simNextStep()==1){
           break;
       }
    }
    JsonFileInterface::createFireJson(fire, "test");
    return 0;
}
//-0.10x^3+1.5x^2+10x+1