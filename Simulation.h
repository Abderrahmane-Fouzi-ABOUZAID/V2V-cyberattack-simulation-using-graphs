#ifndef SIMULATION_H
#define SIMULATION_H
#include "Vehicule.h"
#include "config.h"

void runStep(float dt);
void infectVehicules(int time, int *n); 
void initGraph();
void updateGraph(); // NEW: Calculates edges based on position
void exportToGraphViz(int time); // NEW: Saves the .dot file
void printInfection(int time, Vehicule infectedVehicule, Vehicule suseptibleVehicule);

extern int graphRepresentation[MAX_VEHICULES][MAX_VEHICULES];

#endif
