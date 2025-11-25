// this program will be my final project for the grpah algorithm 
#include "Vehicule.h"
#include "Simulation.h"
#include <stdio.h>


int main(){
    int time = 0; // this variable will simulate the time in the program 
    int infectedNumber = 0;
    initVehicules();
    Vehicule * patientZero = initPatientZero();
    allVehicules[0] = *patientZero;
    initVehicule(&allVehicules[1]); 
    initVehicule(&allVehicules[2]); 
    initVehicule(&allVehicules[3]); 
    initVehicule(&allVehicules[4]); 
    initVehicule(&allVehicules[5]); 
    initVehicule(&allVehicules[6]); 
    initVehicule(&allVehicules[7]); 
    initGraph();

    while(time != 120){ // we will consider that the process takes 2 minutes which means 120 secondes 
        runStep(1);
        infectVehicules(time, &infectedNumber);
        time++;
    } 

    printf("INFECTED NUMBER OF VEHICULES : %d", infectedNumber);
    
    return 0;
}




