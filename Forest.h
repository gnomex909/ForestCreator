//
// Created by obire on 27.11.2019.
//

#ifndef FORESTCREATOR_FOREST_H
#define FORESTCREATOR_FOREST_H


#include <vector>
#include <string>
#include "Cell.h"
//Constants used in setting and getting data
static const int HEIGHT = 0;
static const int RATE = 1;
static const int STATE = 2;
static const int TURN = 4;
static const int STATUS = 5;
class Forest {
    //Vector of all forest cells inside the forest
    std::vector<std::vector<Cell>> forest_cells;
    //Number of rows of the forest cells
    unsigned int height;
    //Number of columns of the forest cells
    unsigned int width;
public:
    /*
     * Main constructor, used to create forest. It also creates all needed Cell objects
     */
    Forest(unsigned int height, unsigned int width);
    /*
     * Getters and setters
     */
    unsigned int getHeight() const;

    void setHeight(unsigned int height);

    unsigned int getWidth() const;

    const std::vector<std::vector<Cell>> &getForestCells() const;

    void setForestCells(const std::vector<std::vector<Cell>> &forestCells);

    void setWidth(unsigned int width);
    /*
     * Function used to visualise data in a console way
     * Args:
     * dataType - one of constants, defining which data we are interested in
     * Returns:
     * string showing matrix of the data
     */
    std::string showData(int dataType);
    /*
     * Function used to get value of equation defining one of dataTypes
     * Args:
     * x - coordinate we are checking value for
     * eqLevel - highest power of x in the equation, shouldn't be higher than 3
     * constant - constant in the equation
     * arg_pow1,arg_pow2,arg_pow3 - arguments associated with x in stated power
     * returns:
     * equation value for selected x
     */
    static double getEquationValue(int x,int eqLevel, double constant, double arg_pow1,double arg_pow2, double arg_pow3);
    /*
     * Function used to obtain data value for provided cell
     * Args:
     * x,y - coordinates of a cel
     * xPow,yPow - highest powers for row and column variables equation
     * xArgs, yArgs - arguments taken by equations. They are in format of {constant,arg_pow1,arg_pow2,arg_pow3}, should always have value for all args, even unused
     * returns:
     * data value
     */
    double sumFunction(unsigned int x, int xPow,const std::vector<double> &xArgs,unsigned int y, int yPow, const std::vector<double> &yArgs);
    /*
     * Function used to set functions defining one of data fields of the cell
     * Args:
     * dataType - one of constants, that defines what data we are interested in
     * xPow,yPow - highest powers for row and column variables equation
     * xArgs, yArgs - arguments taken by equations. They are in format of {constant,arg_pow1,arg_pow2,arg_pow3}, should always have value for all args, even unused
     * xOffset,yOffset - how coordinates are moved in equation (eg. for xOffset -3, equation takes (x-3) instead of x during calculation)
     * Returns:
     * Nothing, as it sets value on cells
     */
    void setDataFunction(int dataType, int xPow,const std::vector<double> &xArgs, int yPow,const std::vector<double> &yArgs, double xOffset, double yOffset);
    /*
     * Function used to set data of cells inside rectangle defined by arguments. Please remember that 0 is actually top row, and (height-1) is lowest one
     * Args:
     * dataType - type of data we want to set
     * value - what is value we are setting. Please remember about constraints: fire rate and state should be between {0,1}
     * upperLimit,lowerLimit,leftLimit,rightLimit - coordinates of the rectangle
     * Returns:
     * Nothing, as it sets value on cells
     */
    void setAreaValue(int dataType, double value, int upperLimit, int lowerLimit, int leftLimit, int rightLimit);
    /*
     * Function used to set value of one cell
     * Args:
     * dataType - type of data we want to set
     * value - what is value we are setting. Please remember about constraints: fire rate and state should be between {0,1}
     * x,y - coordinates of the cell we want to change
     * Returns:
     * Nothing, as it sets value on cells
     */
    void setCellValue(int dataType, double value, int x, int y);
};


#endif //FORESTCREATOR_FOREST_H
