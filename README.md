# Bibliothèque et programme déplacements des Makerbase Servo42d_485    
par Valentin Bonali                    V1.0   du 20/04/2025           
pour le Club Robotique du Lycée Fourcade CROF de Gardanne 13120         
     
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
*******************************************************************************
