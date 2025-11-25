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
    for(int k=1; k<8; k++) initVehicule(&allVehicules[k]);
    initGraph();

    while(time != 120){ // we will consider that the process takes 2 minutes which means 120 secondes 
        runStep(1);
        updateGraph();
        infectVehicules(time, &infectedNumber);
        if(time % 5 == 0){
            exportToGraphViz(time);
        }

        time++;
    } 

    printf("INFECTED NUMBER OF VEHICULES : %d", infectedNumber);
    
    return 0;
}




