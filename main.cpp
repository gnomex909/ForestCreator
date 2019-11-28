#include <iostream>
#include "Forest.h"

int main() {
    int n;
    Forest forest(20,20);
    forest.setHeightFunction(3,{1,10,1.5,-0.1},2,{0,0,-0.5,-1,-1},0,10);
    std::cout<<forest.showHeight()<<std::endl;
    return 0;
}
//-0.10x^3+1.5x^2+10x+1