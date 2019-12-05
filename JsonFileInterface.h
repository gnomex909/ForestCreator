//
// Created by obire on 04.12.2019.
//

#ifndef FORESTCREATOR_JSONFILEINTERFACE_H
#define FORESTCREATOR_JSONFILEINTERFACE_H


#include "Fire.h"

class JsonFileInterface {
public:
    /*
     * Function used to create JSON saving how fire was spreading
     * Args:
     * fire - object of finished forest fire
     * filename - name of the file, without file extension
     */
    static void createFireJson(const Fire &fire, const std::string &fileName);
};


#endif //FORESTCREATOR_JSONFILEINTERFACE_H
