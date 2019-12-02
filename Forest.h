//
// Created by obire on 27.11.2019.
//

#ifndef FORESTCREATOR_FOREST_H
#define FORESTCREATOR_FOREST_H


#include <vector>
#include <string>
#include "Cell.h"
static const int HEIGHT = 0;
static const int RATE = 1;
static const int STATE = 2;
static const int TURN = 4;
class Forest {
    std::vector<std::vector<Cell>> forest_cells;
    unsigned int height;
    unsigned int width;
    std::vector<double> wind_force{1.0,1.0,1.0,1.0,1.0,1.0};
public:
    Forest(unsigned int height, unsigned int width);

    unsigned int getHeight() const;

    void setHeight(unsigned int height);

    unsigned int getWidth() const;

    const std::vector<std::vector<Cell>> &getForestCells() const;

    void setForestCells(const std::vector<std::vector<Cell>> &forestCells);

    void setWidth(unsigned int width);

    const std::vector<double> &getWindForce() const;

    void setWindForce(const std::vector<double> &windForce);

    std::string showData(int dataType);

    static double getEquationValue(int x,int eqLevel, double constant, double arg_pow1,double arg_pow2, double arg_pow3);

    double sumFunction(unsigned int x, int xPow,const std::vector<double> &xArgs,unsigned int y, int yPow, const std::vector<double> &yArgs);

    void setDataFunction(int dataType, int xPow,const std::vector<double> &xArgs, int yPow,const std::vector<double> &yArgs, double xOffset, double yOffset);

    void setAreaValue(int dataType, double value, int upperLimit, int lowerLimit, int leftLimit, int rightLimit);

    void setCellValue(int dataType, double value, int x, int y);
};


#endif //FORESTCREATOR_FOREST_H
