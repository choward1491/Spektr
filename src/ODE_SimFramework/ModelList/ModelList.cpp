//
//  ModelList.cpp
//  NumCH
//
//  Created by Christian J Howard on 12/25/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#include "ModelList.hpp"

ModelList::ModelList(){
    numStates = 0;
}

void ModelList::initializeModels(){
    for (int i = 0; i < diffeqList.size(); i++) {
        diffeqList[i]->initialize();
    }
    for (int i = 0; i < discreteList.size(); i++) {
        discreteList[i]->initialize();
    }
}

void ModelList::addParentData( SimState & s, Rand & gen){
    for (int i = 0; i < diffeqList.size(); i++) {
        diffeqList[i]->assignRandomGenerator(gen);
        diffeqList[i]->assignSimState(s);
    }
    for (int i = 0; i < discreteList.size(); i++) {
        discreteList[i]->assignRandomGenerator(gen);
        discreteList[i]->assignSimState(s);
    }
}

void ModelList::addDynamics( DynamicModel * model ){
    diffeqList.push_back(model);
    numStates += model->numDims();
}
void ModelList::addDiscrete( DiscreteModel * model , int computationFrequency ){
    Time dt(1,computationFrequency);
    model->assignUpdateRate( computationFrequency );
    discreteList.push_back(model);
    scheduler.push(dt, model);
}

DynamicModel* ModelList::getDynamicsAt(int index){
    return diffeqList[index];
    
}
DiscreteModel* ModelList::getDiscreteAt(int index){
    return discreteList[index];
}

std::vector<DynamicModel*> & ModelList::getDiffeqList(){
    return diffeqList;
}
std::vector<DiscreteModel*> & ModelList::getDiscreteList(){
    return discreteList;
}

int ModelList::getNumStates() const{
    return numStates;
}

void ModelList::setupSimHistory(){
    for (int i = 0; i < diffeqList.size(); i++) {
        diffeqList[i]->setupPrintData();
    }
    for (int i = 0; i < discreteList.size(); i++) {
        discreteList[i]->setupPrintData();
    }
}