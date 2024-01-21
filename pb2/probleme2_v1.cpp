#define F_CPU 8000000UL // 8 MHz
#include <avr/io.h>
#include <util/delay.h>

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




