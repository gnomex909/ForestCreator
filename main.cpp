#include <iostream>
#include "Forest.h"
#include "Fire.h"

int main() {
    int n;
    Forest forest(20,20);
//    forest.setDataFunction(HEIGHT,3,{1,10,1.5,-0.1},2,{0,0,-0.5,-1,-1},0,10);
//    std::cout<<forest.showData(HEIGHT)<<std::endl;
    Fire fire(forest);
    fire.startFire(1,1,1.0);
    std::cout<<forest.showData(STATE)<<std::endl;
    for(int i=0;i<20;i++){
        fire.simNextStep();
        std::cin>>n;
    }
    return 0;
}
//-0.10x^3+1.5x^2+10x+1