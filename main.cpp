/******************************************************************************
*    Bibliothèque et programme déplacements par Stepper et drivers 42d_485    *
*       Fork par Valentin Bonali                    V1.2   du 20/04/2025      *
*     pour le Club Robotique du Lycée Fourcade CROF de Gardanne 13120         *
*******************************************************************************
* OBJECTIF :
* Développer une API propre et maintenable pour piloter des moteurs pas à pas
* via des drivers MKS SERVO42D en liaison RS485 (protocole propriétaire).
*
* Ce programme fonctionne sur une carte Nucleo64 L476RG et pilote :
*   - 3 moteurs NEMA17 via drivers MKS SERVO42D
*   - en mode vitesse ou position (mouvement relatif)
*   - par le bus série RS485 (via Serial1 + broche E_R pour le sens)
*
*******************************************************************************
* MODIFICATIONS ET FONCTIONNALITÉS CLÉS :
* - 🔧 Refonte complète en C++ : structuration, séparation des rôles
* - ✅ Envoi propre de trames avec `flush()` + délai intégré (pas de `delay()`)
* - 🧠 Enums et centralisation des codes commandes RS485
* - 🛠️ Ajout d'une API complète de configuration des moteurs :
*       -> courant, subdivision, sens, mode de la broche En, protection
* - 🏁 Prise en charge du GoHome, SetHome, Reset usine, etc.
* - 💬 Affichage debug paramétrable par drapeaux
*
* Ce projet est évolutif : possibilité d’ajouter des fonctions de lecture (F1, etc.)
* ainsi que la communication avec ROS2 (via UART → microROS).
*******************************************************************************/

#include <Arduino.h>
#include "global.h"
#include "servo42d.h"
#include "embase3pap.h"

void setup() {
  delay(10000); // delai de 10 seconde pour attendre le moniteur série
  // Initialise la liaison série principale (pour debug si AFFICHAGE == true)
  if (AFFICHAGE) {
    Serial.begin(115200);
    while (!Serial);
    Serial.println("Démarrage du robot...");
  }

  // Initialise RS485
  pinMode(E_R, OUTPUT);
  digitalWrite(E_R, LOW);  // On commence en mode réception

  Serial1.begin(38400);  // Démarre la liaison RS485

  // Initialise les moteurs et leurs rôles dans l'embase
  init_moteurs();
  affectations_moteurs();

  delay(1000);  // Petite pause pour stabilité
}

void loop() {
  ////// === TEST 1 : Mouvement d’un seul moteur en vitesse constante
  //Serial.println("Test 1 : Vitesse constante sur moteur gauche...");
  //envoyer_vitesse(mot[mot_gauche], 0, 200, acc_globale);  // sens horaire, 200 tr/min
  //delay(100);
  //envoyer_vitesse(mot[mot_droit], 0, 200, acc_globale);
  //delay(100);
  //envoyer_vitesse(mot[mot_arriere], 0, 200, acc_globale);
  //delay(5000);
  //
  ////// === TEST 4 : Arrêt complet via broadcast
  //Serial.println("Test 4 : Arrêt total des moteurs...");
  //arret_moteur(mot_tous);
  //delay(10000);
  ////
  //envoyer_vitesse(mot[mot_gauche], 1, 500, acc_globale);  // sens horaire, 200 tr/min
  //delay(100);
  //envoyer_vitesse(mot[mot_droit], 1, 500, acc_globale);
  //delay(100);
  //envoyer_vitesse(mot[mot_arriere], 1, 500, acc_globale);
  //delay(5000);
//// Serial.println("Test 4 : Arrêt total des moteurs...");
  //arret_moteur(mot_tous);
  //delay(5000);
  ////// === TEST 2 : Mouvement relatif sur un seul moteur
  //Serial.println("Test 2 : Déplacement relatif sur moteur droit...");
  //MouvRelPulse(mot_gauche, 1, 150, acc_globale, 10000);  // sens anti-horaire, 10000 pulses
  //delay(2);
  //MouvRelPulse(mot_droit, 1, 150, acc_globale, 10000);
  //delay(2);
  //MouvRelPulse(mot_arriere, 1, 150, acc_globale, 10000);
  //delay(5000);
//
  // === TEST 3 : Mouvement groupé avec ldp_package
  //Serial.println("Test 3 : Mouvement groupé (ldp_package)...");
  //uint32_t tableau_ldp[5][6] = {
  //  {1, 320, 0, 2, 0, (uint32_t)Commande::MouvementVitesse},
  //  {2, 320, 1, 2, 0, (uint32_t)Commande::MouvementVitesse},
  //  {3, 250, 0, 2, 20000, (uint32_t)Commande::MouvementRelatif},
  //  {0, 0, 0, 0, 0, 0},
  //  {0, 0, 0, 0, 0, 0}
  //};
  //ldp_package(tableau_ldp);
  //delay(5000);

  // === TEST 4 : Arrêt complet via broadcast
  //Serial.println("Test 4 : Arrêt total des moteurs...");
  //arret_moteur(mot_tous);
  //delay(10000);
//
  //// === Pause avant de boucler
  //Serial.println("Attente avant redémarrage...");
  //delay(1000);
}
