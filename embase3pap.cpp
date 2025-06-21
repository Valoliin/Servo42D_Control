/*********************************************************
* Fichier : embase3pap.cpp                              *
* Description : Gestion de l'embase 3 roues             *
*omnidirectionnelles                                    *
* Calcule et envoie les commandes de vitesse et position*
* aux trois moteurs du robot mobile                     *
*RESTE A FAIRE: corriger les fonction les deux fonction *
* trimoteur qui on était réaliser avec ldp_package mais *
* mais lors des test il s'est avérer que ldp_package    *
* n'existe pas dans notre version de servo42d           *
**********************************************************/

#include "servo42d.h"
#include "embase3pap.h"
#include "WSerial.h"
#include "global.h"

// ! Initialise chaque moteur avec ses paramètres matériels et logiques
// ? Affecte les IDs, labels, vitesses et inversions pour chaque moteur selon leur position
void affectations_moteurs() {
    // ───── MOTEUR ARRIÈRE ─────
    mot[mot_arriere].id = 1;
    mot[mot_arriere].libelle = "Arriere";
    mot[mot_arriere].vitesse = 300;
    mot[mot_arriere].inversion = false;

    set_courant(mot_arriere, 2000);               // 1800 mA
    set_subdivision(mot_arriere, 16);             // 16 subdivisions
    set_direction(mot_arriere, 0);                // CW
    set_enable_pin_mode(mot_arriere, 2);          // Toujours actif
    set_auto_screen_off(mot_arriere, 1);          // Éteindre écran auto
    set_locked_rotor_protection(mot_arriere, 1);  // Active la protection
    set_interpolation(mot_arriere, 1);            // Interpolation activée
    set_slave_respond(mot_arriere, 1);            // Autorise les réponses

    // ───── MOTEUR GAUCHE ─────
    mot[mot_gauche].id = 2;
    mot[mot_gauche].libelle = "Gauche";
    mot[mot_gauche].vitesse = 300;
    mot[mot_gauche].inversion = false;

    set_courant(mot_gauche, 2000);
    set_subdivision(mot_gauche, 16);
    set_direction(mot_gauche, 0);
    set_enable_pin_mode(mot_gauche, 2);
    set_auto_screen_off(mot_gauche, 1);
    set_locked_rotor_protection(mot_gauche, 1);
    set_interpolation(mot_gauche, 1);
    set_slave_respond(mot_gauche, 1);

    // ───── MOTEUR DROIT ─────
    mot[mot_droit].id = 3;
    mot[mot_droit].libelle = "Droit";
    mot[mot_droit].vitesse = 300;
    mot[mot_droit].inversion = false;

    set_courant(mot_droit, 2000);
    set_subdivision(mot_droit, 16);
    set_direction(mot_droit, 0);
    set_enable_pin_mode(mot_droit, 2);
    set_auto_screen_off(mot_droit, 1);
    set_locked_rotor_protection(mot_droit, 1);
    set_interpolation(mot_droit, 1);
    set_slave_respond(mot_droit, 1);
}


// ! Lecture et envoi du mouvement courant
// ? Extrait vx, vy, vc depuis la séquence et envoie la commande selon le mode (vitesse ou déplacement)
void ordre_trimoteur(int num_mvt) {
    int vx = mvts[num_mvt].vx;
    int vy = mvts[num_mvt].vy;
    int vc = mvts[num_mvt].vc;

    if (mvts[num_mvt].type == VITESSE) {
        trimoteur_vit(vx, vy, vc);
    } else if (mvts[num_mvt].type == DEPLACE) {
        trimoteur_dep(vx, vy, vc, mvts[num_mvt].pulses);
    }
}

// ! Exemple : trimoteur_vit(200, 0, 20);
// ? Calcule et envoie les vitesses aux trois moteurs en mode vitesse constante
void trimoteur_vit(int vx, int vy, int vc) {
    float da = (vx * 0.0f) + (vy * -1.0f) + vc;
    float dg = (vx * -0.866f) + (vy * 0.5f) + vc;
    float dd = (vx * 0.866f) + (vy * 0.5f) + vc;

    mot[mot_arriere].vitesse = abs((int)da);
    mot[mot_arriere].sens = (da < 0);

    mot[mot_gauche].vitesse = abs((int)dg);
    mot[mot_gauche].sens = (dg < 0);

    mot[mot_droit].vitesse = abs((int)dd);
    mot[mot_droit].sens = (dd < 0);

    // Construction du tableau à 6 colonnes pour ldp_package
    //uint32_t trimoteur_tab[5][6] = {
    //    { mot[mot_arriere].id, mot[mot_arriere].vitesse, mot[mot_arriere].sens, acc_globale, 0, (uint32_t)Commande::MouvementVitesse },
    //    { mot[mot_gauche].id,  mot[mot_gauche].vitesse,  mot[mot_gauche].sens,  acc_globale, 0, (uint32_t)Commande::MouvementVitesse },
    //    { mot[mot_droit].id,   mot[mot_droit].vitesse,   mot[mot_droit].sens,   acc_globale, 0, (uint32_t)Commande::MouvementVitesse },
    //    { 0, 0, 0, 0, 0, 0 },
    //    { 0, 0, 0, 0, 0, 0 }
    //};
//
    //ldp_package(trimoteur_tab);
}

// ! Exemple : trimoteur_dep(200, 0, 20, 10000);
// ? Calcule les directions et vitesses pour les trois moteurs en mouvement relatif
void trimoteur_dep(int vx, int vy, int vc, uint32_t nb_pulses) {
    float da = (vx * 0.0f) + (vy * -1.0f) + vc;
    float dg = (vx * -0.866f) + (vy * 0.5f) + vc;
    float dd = (vx * 0.866f) + (vy * 0.5f) + vc;

    mot[mot_arriere].vitesse = abs((int)da);
    mot[mot_arriere].sens = (da < 0);

    mot[mot_gauche].vitesse = abs((int)dg);
    mot[mot_gauche].sens = (dg < 0);

    mot[mot_droit].vitesse = abs((int)dd);
    mot[mot_droit].sens = (dd < 0);

    // Construction du tableau à 6 colonnes pour ldp_package (mode relatif)
    //uint32_t trimoteur_tab[5][6] = {
    //    { mot[mot_arriere].id, mot[mot_arriere].vitesse, mot[mot_arriere].sens, acc_globale, nb_pulses, (uint32_t)Commande::MouvementRelatif },
    //    { mot[mot_gauche].id,  mot[mot_gauche].vitesse,  mot[mot_gauche].sens,  acc_globale, nb_pulses, (uint32_t)Commande::MouvementRelatif },
    //    { mot[mot_droit].id,   mot[mot_droit].vitesse,   mot[mot_droit].sens,   acc_globale, nb_pulses, (uint32_t)Commande::MouvementRelatif },
    //    { 0, 0, 0, 0, 0, 0 },
    //    { 0, 0, 0, 0, 0, 0 }
    //};
//
    //ldp_package(trimoteur_tab);
}
