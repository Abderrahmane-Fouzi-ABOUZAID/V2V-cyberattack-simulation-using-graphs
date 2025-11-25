#ifndef VEHICULE_H
#define VEHICULE_H

typedef enum {
    STATE_SUSEPTIBLE,
    STATE_INFECTED,
    STATE_RECOVERED
} InfectionState;

typedef struct {
    int id;
    InfectionState state;
    float position;
    float velocity;
} Vehicule;

void initVehicule(Vehicule *v);
void initVehicules();
extern Vehicule *allVehicules;
Vehicule * initPatientZero();

#endif
