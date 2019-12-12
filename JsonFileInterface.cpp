//
// Created by obire on 04.12.2019.
//

#include <fstream>
#include <iostream>
#include "JsonFileInterface.h"
#include "include/rapidjson/document.h"
#include "include/rapidjson/ostreamwrapper.h"
#include "include/rapidjson/writer.h"
#include "include/rapidjson/prettywriter.h"


 void JsonFileInterface::createFireJson(const Fire &fire,const std::string &fileName) {
        rapidjson::Document document;
        Forest forest = fire.getForest();
        document.SetObject();
        //Declaration of all arrays that will be inside JSON document
        rapidjson::Value turnOfBurning(rapidjson::kArrayType);
        rapidjson::Value heightOfCells(rapidjson::kArrayType);
        rapidjson::Value rateOfCells(rapidjson::kArrayType);
        rapidjson::Value stateOfCells(rapidjson::kArrayType);
        rapidjson::Value statusOfCells(rapidjson::kArrayType);
        //Objects of height and width, instantly added to the document
        rapidjson::Value forestHeight(forest.getHeight());
        rapidjson::Value forestWidth(forest.getWidth());
        document.AddMember("forest_height", forestHeight,document.GetAllocator());
        document.AddMember("forest_width",forestWidth,document.GetAllocator());
        //Loop that saves height, turn of burning and fire rate of all cells in right arrays
        for(unsigned int i=0;i<fire.getForest().getHeight();i++){
            rapidjson::Value rowTurn(rapidjson::kArrayType);
            rapidjson::Value rowHeight(rapidjson::kArrayType);
            rapidjson::Value rowRate(rapidjson::kArrayType);
            for(unsigned int j=0;j<fire.getForest().getWidth();j++){
                rowTurn.PushBack(forest.getForestCells()[i][j].getTurnOfBurning(), document.GetAllocator());
                rowHeight.PushBack(forest.getForestCells()[i][j].getHeight(), document.GetAllocator());
                rowRate.PushBack(forest.getForestCells()[i][j].getFireRate(), document.GetAllocator());
            }
            turnOfBurning.PushBack(rowTurn, document.GetAllocator());
            rateOfCells.PushBack(rowRate, document.GetAllocator());
            heightOfCells.PushBack(rowHeight, document.GetAllocator());
        }
        //Adding arrays to the document
        document.AddMember("turns_burning",turnOfBurning,document.GetAllocator());
        document.AddMember("cell_height",heightOfCells,document.GetAllocator());
        document.AddMember("cell_rate",rateOfCells,document.GetAllocator());
        //Triple loop to save all the states and statuses, during all of the turns
        for(unsigned int k=0;k<fire.getStatesDuringTurns().size();k++){
            rapidjson::Value stateOfTurn(rapidjson::kArrayType);
            rapidjson::Value statusOfTurn(rapidjson::kArrayType);
            for(unsigned int i=0;i<fire.getForest().getHeight();i++){
                rapidjson::Value rowState(rapidjson::kArrayType);
                rapidjson::Value rowStatus(rapidjson::kArrayType);
                for(unsigned int j=0;j<fire.getForest().getWidth();j++){
                    rowState.PushBack(fire.getStatesDuringTurns()[k][i][j], document.GetAllocator());
                    rowStatus.PushBack(fire.getStatusDuringTurns()[k][i][j], document.GetAllocator());
                }
                stateOfTurn.PushBack(rowState, document.GetAllocator());
                statusOfTurn.PushBack(rowStatus, document.GetAllocator());
            }
            stateOfCells.PushBack(stateOfTurn,document.GetAllocator());
            statusOfCells.PushBack(statusOfTurn,document.GetAllocator());
        }
        //Adding this array to document
        document.AddMember("cell_state",stateOfCells,document.GetAllocator());
        document.AddMember("cell_status",statusOfCells,document.GetAllocator());
        //File writing
        std::cout<<"File writing"<<std::endl;
        std::ofstream outfile("..\\"+fileName+".json");
        rapidjson::OStreamWrapper oStreamWrapper(outfile);
        rapidjson::Writer<rapidjson::OStreamWrapper> writer(oStreamWrapper);
        rapidjson::PrettyWriter<rapidjson::OStreamWrapper> writer2(oStreamWrapper);
        document.Accept(writer);
        outfile.close();
}
