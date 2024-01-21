/*IDEES*/

/*Fonction couleur*/
// Faire des fonctions specifiques pour les changements de couleur et indiquer les ports a utiliser dans la description (eteinte , rouge ,vert , ambre)
// point forts :
// intuitif pendant le codage, on a pas a reflechir pour le masque a chaque fois -> gain de temps
// evite les erreurs
// si on veut changer de port --> il suffit de le changer dans la fonction

/*Class enum pour les etats*/
// Rouge_Presse --> Rouge bouton Presse
// Vert_Libre --> Vert bouton LIBRE
// ...



/* DESCRIPTION */


// INFOS A METTRE --> checker le cours !
// Table des ETATS


#define F_CPU 8000000UL // 8 MHz
#include <avr/io.h>
#include <util/delay.h>


// Prototypes des fonctions 

// Definir les etats a l'aide noms SIGNIFICATIFS dans une classe Enum (sans le 'class' sinon la synthaxe est chiante)
enum etat_Robot {etat_initial} ; // juste a titre d'exemple mais pas des bon NOMS !


// Definir les valeurs constantes a utiliser dans le main (masques , combinaison de masques, temps de delai ...)


// Fonction main qui fait tourner la machine a etat

int main(){

    // Definir si les PORTS seront en sortie ou en entree (DDRA, DDRB ...) --> utiliser des masques avec bit shifts

    // Initialiser une variable de type Nom_de_l'enumeration avec la constante enum de l'etat initial
    etat_Robot etat_present {etat_initial} ; 

    // Initialiser le / les variables avec les INPUTS initiales 

    // Declarer les variables de sortie si necessaire (pas necessaire pour changer la couleur d'une DEL)
    
    // Boucle infinie qui fait fonctionner la machine a etat 
    while (true){
        switch (etat_present){
            // implementation
        }
    }

}

// Definition des fonctions utilisees dans la fonction main (meilleur pratique : utiliser un autre fichier + un header qui fait le lien ) 

// fonction 1 

// fonction 2 