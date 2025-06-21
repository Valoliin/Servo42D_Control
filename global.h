/*********************************************************
* Fichier : global.h                                    *
* Description : Déclarations globales et constantes     *
* mécaniques, temps, liaison série, broches et moteurs  *
* Utilisé dans tout le projet                           *
**********************************************************/

#ifndef GLOBAL_H
#define GLOBAL_H

#include <Arduino.h>
#include <HardwareSerial.h>

// === DRAPEAUX DEBUG (affichage série)
#define AFFICHAGE true
#define DEBUG_STATUS false
#define DEBUG_LDP false
#define DEBUG_AFF_REP false
#define DEBUG_AFF_TR true
#define DEBUG_AFF_CRC false
#define DEBUG_VIT false
#define DEBUG_MVT false
#define DEBUG_PULSE true

// === CONSTANTES MECANIQUES
#define pas_tour 200
#define micropas 4
#define rayon_embase 118
#define diametre_roue 80
#define tour_roue (PI * diametre_roue)
#define vitesse_faible 50
#define perimetre_embase (2 * rayon_embase * PI)
#define impulsions_mm ((micropas * pas_tour) / (PI * diametre_roue))
#define impulsions_dg (impulsions_mm * perimetre_embase / 360)
#define DEG_RAD (360 / (2 * PI))

#define nb_mot 4

// === ASPECT MOUVEMENT
#define DEPLACE  true
#define VITESSE  !DEPLACE
#define RADIAN   true
#define DEGRES   !RADIAN

extern const uint8_t acc_globale;
extern int vitesse_nom;
extern bool deg_rad;

// === STRUCTURE DE MOUVEMENT
struct Mvt {
  int vx;
  int vy;
  int vc;
  uint32_t pulses;
  bool type;
};

extern Mvt mvts[10];

// === HORLOGE ET DIALOGUE
extern unsigned long heure;
extern bool parle;
extern bool rep_en_cours;

// === RS485
extern HardwareSerial Serial1;
#define E_R D3

// === IDENTIFIANTS MOTEURS
extern uint8_t mot_arriere;
extern uint8_t mot_droit;
extern uint8_t mot_gauche;
extern int8_t mot_tous;


#endif