#include "Vehicule.h"
#include <stdlib.h>
#include "config.h"


Vehicule *allVehicules = NULL;

void initVehicules() {
    allVehicules = malloc(MAX_VEHICULES * sizeof(Vehicule));
}

void initVehicule(Vehicule *v) {
    int r = rand() % MAX_ID_VALUE;
    while (r == 404) {
        r = rand() % MAX_ID_VALUE;
    }

    v->id = r;
    v->position = MIN_POSITION + rand() % (MAX_POSITION - MIN_POSITION + 1);
    v->velocity = MIN_VELOCITY + rand() % (MAX_VELOCITY - MIN_VELOCITY + 1);
    v->state = STATE_SUSEPTIBLE;
}

Vehicule * initPatientZero(){
    Vehicule * patientZero = malloc(sizeof(Vehicule)); 
    patientZero->id = 404;
    patientZero->state = STATE_INFECTED;
    patientZero->position = 0;
    patientZero->velocity = 65;
    return patientZero;
}
