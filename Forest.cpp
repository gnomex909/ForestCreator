//
// Created by obire on 27.11.2019.
//

#include <sstream>
#include <iostream>
#include <cmath>
#include "Forest.h"

unsigned int Forest::getHeight() const {
    return height;
}

void Forest::setHeight(unsigned int height) {
    Forest::height = height;
}

unsigned int Forest::getWidth() const {
    return width;
}

void Forest::setWidth(unsigned int width) {
    Forest::width = width;
}

const std::vector<double> &Forest::getWindForce() const {
    return wind_force;
}

void Forest::setWindForce(const std::vector<double> &windForce) {
    wind_force = windForce;
}

Forest::Forest(unsigned int height, unsigned int width) : height(height), width(width) {
    std::cout<<"Starting constructor"<<std::endl;
    for(unsigned int i=0; i<height;i++){
        forest_cells.emplace_back(std::vector<Cell>());
        for(unsigned int j=0; j<width;j++){
            forest_cells[i].push_back(Cell());
        }
    }
}

std::string Forest::showData(int dataType) {
    std::stringstream stringstream;
    for(unsigned int i=0; i<height;i++){
        stringstream<<"[";
        for(unsigned int j=0; j<width;j++){
            if(j!=-0){
                stringstream<<" ";
            }
            if(dataType == HEIGHT) {
                stringstream << forest_cells[i][j].getHeight();
            }else if(dataType == RATE){
                stringstream << forest_cells[i][j].getFireRate();
            }else if(dataType == STATE){
                stringstream << forest_cells[i][j].getState();
            }else if(dataType == TURN){
                stringstream << forest_cells[i][j].getTurnOfBurning();
            }
        }
        stringstream<<"]"<<std::endl;
    }
    return stringstream.str();
}


double Forest::getEquationValue(const int x, const int eqLevel, const double constant, const double arg_pow1,
                                const double arg_pow2, const double arg_pow3) {
    switch(eqLevel){
        case 0:
            return constant;
        case 1:
            return x*arg_pow1+constant;
        case 2:
            return pow(x,2)*arg_pow2+x*arg_pow1+constant;
        case 3:
            return pow(x,3)*arg_pow3+pow(x,2)*arg_pow2+x*arg_pow1+constant;
        default:
            return -1;
    }
}
double Forest::sumFunction(const unsigned int x,const int xPow,const std::vector<double> &xArgs,const unsigned int y,const int yPow, const std::vector<double> &yArgs){
    double xRes, yRes;
    xRes = getEquationValue(x,xPow,xArgs[0],xArgs[1],xArgs[2],xArgs[3]);
    yRes = getEquationValue(y,yPow,yArgs[0],yArgs[1],yArgs[2],yArgs[3]);
    return xRes+yRes;
}
void Forest::setDataFunction(const int dataType,const int xPow, const std::vector<double> &xArgs,const int yPow, const std::vector<double> &yArgs, const double xOffset, const double yOffset) {
    for(unsigned int i=0; i<height;i++){
        for(unsigned int j=0; j<width;j++){
            double result = sumFunction(j-xOffset, xPow, xArgs, i-yOffset, yPow,yArgs);
            if(dataType==HEIGHT) {
                forest_cells[i][j].setHeight(result);
            }else if(dataType==RATE){
                forest_cells[i][j].setFireRate(result);
            }
        }
    }
}

void Forest::setAreaValue(int dataType, double value, int upperLimit, int lowerLimit, int leftLimit, int rightLimit) {
    for(unsigned int i=lowerLimit; i<=upperLimit;i++){
        for(unsigned int j=leftLimit; j<=rightLimit;j++){
            if(dataType==HEIGHT) {
                forest_cells[i][j].setHeight(value);
            }else if(dataType==RATE){
                forest_cells[i][j].setFireRate(value);
            }
        }
    }
}

void Forest::setCellValue(int dataType, double value, int x, int y) {
    if(dataType==HEIGHT) {
        forest_cells[y][x].setHeight(value);
    }else if(dataType==RATE){
        forest_cells[y][x].setFireRate(value);
    }else if(dataType==STATE){
        forest_cells[y][x].setState(value);
    }else if(dataType==TURN){
        forest_cells[y][x].setTurnOfBurning((int)value);
    }
}

const std::vector<std::vector<Cell>> &Forest::getForestCells() const {
    return forest_cells;
}

void Forest::setForestCells(const std::vector<std::vector<Cell>> &forestCells) {
    forest_cells = forestCells;
}


