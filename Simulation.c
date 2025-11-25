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

// NEW FUNCTION: Updates the edges based on distance
void updateGraph(){
    // 1. Reset the graph (clear old connections)
    initGraph();

    // 2. Build new connections based on current positions
    for(int i=0; i<MAX_VEHICULES; i++){
        for(int j=i+1; j<MAX_VEHICULES; j++){ // j=i+1 avoids double checking
            if(fabs(allVehicules[i].position - allVehicules[j].position) < DANGER_RADIUS){
                // They are close enough to communicate!
                graphRepresentation[i][j] = 1;
                graphRepresentation[j][i] = 1;
            }
        }
    }
}

// NEW FUNCTION: Exports the current state to a .dot file
void exportToGraphViz(int time){
    // Create a filename like "step_001.dot"
    char filename[50];
    sprintf(filename, "step_%03d.dot", time);
    
    FILE *f = fopen(filename, "w");
    if(f == NULL) return;

    fprintf(f, "graph G {\n");
    fprintf(f, "  layout=neato;\n"); // Use 'neato' layout for physical positions
    fprintf(f, "  node [style=filled];\n");

    // 1. Define Nodes (Colors based on state)
    for(int i=0; i<MAX_VEHICULES; i++){
        const char *color;
        if(allVehicules[i].state == STATE_INFECTED) color = "red";
        else if(allVehicules[i].state == STATE_RECOVERED) color = "blue";
        else color = "green";

        // Optional: Map position to x-coordinate for visualization
        // We divide by 50 to scale it down for the graph viewer
        fprintf(f, "  %d [fillcolor=%s, pos=\"%f,0!\"];\n", 
                allVehicules[i].id, color, allVehicules[i].position / 50.0);
    }

    // 2. Define Edges
    for(int i=0; i<MAX_VEHICULES; i++){
        for(int j=i+1; j<MAX_VEHICULES; j++){
            if(graphRepresentation[i][j] == 1){
                fprintf(f, "  %d -- %d;\n", allVehicules[i].id, allVehicules[j].id);
            }
        }
    }

    fprintf(f, "}\n");
    fclose(f);
}

void runStep(float dt){
    for(int i=0;i<MAX_VEHICULES;i++){
        allVehicules[i].position += dt * allVehicules[i].velocity;
    }
}

void printInfection(int time, Vehicule infectedVehicule, Vehicule suseptibleVehicule){
    printf("------------------INFECTION---------------------\n");
    printf("INFECTION TIME : %d\n", time);
    printf("Vehicle ID : %d INFECTED Vehicle ID : %d\n", infectedVehicule.id, suseptibleVehicule.id);
    printf("------------------------------------------------\n\n");
}

// UPDATED FUNCTION: Uses the graph we built in updateGraph()
void infectVehicules(int time, int *infectedVehiculesNumber){
    for(int i=0;i<MAX_VEHICULES;i++){
        if(allVehicules[i].state == STATE_INFECTED){
            for(int j=0;j<MAX_VEHICULES;j++){
                // Use the Graph Structure, NOT raw distance
                if(i != j && graphRepresentation[i][j] == 1 && allVehicules[j].state == STATE_SUSEPTIBLE){
                    
                    float probability = ((float)rand()) / ((float)RAND_MAX);
                    if(probability < INFECT_PROB){
                        allVehicules[j].state = STATE_INFECTED;
                        printInfection(time, allVehicules[i], allVehicules[j]);
                        (*infectedVehiculesNumber)++;
                    }
                }
            }
        }
    }
}
