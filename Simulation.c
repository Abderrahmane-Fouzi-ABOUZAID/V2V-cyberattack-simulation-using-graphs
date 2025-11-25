#include "Simulation.h"
#include "Vehicule.h"
#include "config.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int graphRepresentation[MAX_VEHICULES][MAX_VEHICULES];

void initGraph(){
    for(int i=0;i<MAX_VEHICULES;i++){
        for(int j=0;j<MAX_VEHICULES;j++){
            graphRepresentation[i][j] = 0;
        }
    }
}

void runStep(float dt){
    for(int i=0;i<MAX_VEHICULES;i++){
        allVehicules[i].position += dt * allVehicules[i].velocity;
    }
}

void printInfection(int time, Vehicule infectedVehicule, Vehicule suseptibleVehicule){
    printf("------------------INFECTION---------------------\n");
    printf("INFECTION TIME : %d\n", time);
    printf("INFECTED VEHICULE : Vehicule ID : %d , x = %f, velocity = %f  \n", infectedVehicule.id, infectedVehicule.position, infectedVehicule.velocity);
    printf("SUSEPTIBLE VEHICULE : Vehicule ID : %d, x = %f , velocity = %f \n" , suseptibleVehicule.id, suseptibleVehicule.position, suseptibleVehicule.velocity);
    printf("------------------------------------------------\n\n");
}



void infectVehicules(int time,int *infectedVehiculesNumber){
    for(int i=0;i<MAX_VEHICULES;i++){
        if(allVehicules[i].state == STATE_INFECTED){
            for(int j=0;j<MAX_VEHICULES;j++){
                if(j!=i && fabs(allVehicules[i].position - allVehicules[j].position) < DANGER_RADIUS && allVehicules[j].state != STATE_INFECTED){
                    float probability = ((float)rand() + 1) / ((float)RAND_MAX + 1);
                    if(probability >= INFECT_PROB){
                        allVehicules[j].state = STATE_INFECTED;
                        graphRepresentation[i][j] = 1;
                        graphRepresentation[j][i] = 1;
                        printInfection(time, allVehicules[i], allVehicules[j]);
                        (*infectedVehiculesNumber)++;
                    }

                }
            }
        }
    }
}
