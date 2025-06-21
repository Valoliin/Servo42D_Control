/*********************************************************
* Fichier : global.cpp                                  *
* Description : Définition des variables globales       *
* partagées par les différents modules du programme     *
**********************************************************/

#include "global.h"

HardwareSerial Serial1(D2, D8);
bool rep_en_cours = false;
unsigned long heure = 0;
bool parle = false;

int vitesse_nom = 75;
bool deg_rad = false;
const uint8_t acc_globale = 10;

uint8_t mot_arriere = 1;
uint8_t mot_droit   = 2;
uint8_t mot_gauche  = 3;
int8_t mot_tous    = -1;

Mvt mvts[10];

