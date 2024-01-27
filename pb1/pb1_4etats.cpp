/*MACHINE A ETAT*/

// 4 ETATS


#define F_CPU 8000000UL // 8 MHz
#include <avr/io.h>
#include <util/delay.h>

/* Notes*/

// legende : BPR = bouton presse relache
// Seulement besoin de mettre l'etat eteint pour l'etat initial car la couleur change seulement a l'etat allume pendant 2 secondes

// Couleur-actuel = SORTIE_actuel en terme de machine a etat = on va utiliser PORT
// BPR = Input actuel en terme de machine a etat  = on va utiliser PIN

// LED :
// A2 et A3  --> 01 = rouge et 10 = vert
// Mettre A2 et A3 en mode sortie

// bouton :
// D2 : 0 -> bouton non presse / 1 -> bouton presse
// mettre D2 en mode entree

/*Code*/

// prototypes
bool ButtonPressed();
bool ButtonReleased();
bool ButtonPressed_then_Released();

// Definition d'une classe Enum
enum etat_Robot
{
    etat_Eteint_0,
    etat_Eteint_1,
    etat_Eteint_2,
    etat_Allume
}; // le nombre apres 'eteint' fait reference au nombre de fois que le bouton a ete presse et relache

// Definition de constantes de couleur
// Definition des masques pour les couleurs de LED :

// LED eteinte

const int8_t masque_DEL_eteinte{(1 << PA3) | (1 << PA2)}; // 0b00001100

// LED verte - 10 en A3 A2

const int8_t masque_DEL_verte_1{(1 << PA3)}; // 0b00001000
const int8_t masque_DEL_verte_0{~(1 << PA2)}; // 0b00000100

// Delai DEL verte
const int16_t delai_DEL_Verte{2000}; // en ms

int main()
{
    // Definition de chaque port en mode entree ou sortie

    DDRA |= (1 << PA3) | (1 << PA2); // PORT de la LED A3 et A2 en sortie
    DDRD &= ~(1 << PD2);             // PORT pour le bouton poussoir D2 en entree    

    // etat_actuel =  eteint_0  (etat initial)
    etat_Robot etat_present{etat_Eteint_0};
    // Boucle infinie = while true
    while (true)
    {
        switch (etat_present)
        {
        // Si etat_actuel est 'eteint0' :
        case etat_Eteint_0:
        {
            // Couleur_actuel = LED_ETEINTE
            PORTA |= (masque_DEL_eteinte);
            // Si BPR :
            bool est_presse_relache{ButtonPressed_then_Released()};
            if (est_presse_relache)
                // passer a l'etat 'eteint1
                etat_present = etat_Eteint_1;
            break ; 
        }
        case etat_Eteint_1:
        {
            // Si BPR :
            bool est_presse_relache{ButtonPressed_then_Released()};
            if (est_presse_relache)
                // passer a l'etat 'eteint2'
                etat_present = etat_Eteint_2;
            break ;                             
        }
        case etat_Eteint_2:
        {
            // Si BPR :
            bool est_presse_relache{ButtonPressed_then_Released()};
            if (est_presse_relache)
                // passer a l'etat 'Allume'
                etat_present = etat_Allume;
            break ;                 
        }
        case etat_Allume:
        {
            // La LED devient verte pendant 2 secondes
            PORTA |= masque_DEL_verte_1;
            PORTA &= masque_DEL_verte_0;

            _delay_ms(delai_DEL_Verte);
            // revenir a l'etat initial
            etat_present = etat_Eteint_0;
            break ;             
        }
        }
    }
}

// Definition de fonctions
const int8_t delai_debounce{10} ;         // delai en ms
const int8_t masque_boutton{(1 << PD2)}; // masque pour verifier l'etat de la PIND2

// fonction qui verifie si le bouton a ete presse ou relache selon le parametre --> debounce
bool ButtonPressed()
{
    bool is_state_button = PIND & masque_boutton;                   // vrai si le boutton est dans l'etat attendu sinon faux
    if (is_state_button)
    {
        _delay_ms(delai_debounce);
        is_state_button = PIND & masque_boutton; // mise a jour de l'etat du boutton apres 10 ms
        if (is_state_button)
            return true;
    }
    return false;
}

// fonction qui verifie si le bouton est relache --> aussi avec un debounce
bool ButtonReleased() { return !ButtonPressed(); }


// fonction qui veriife si le bouton a ete PRESSE  puis RELACHE  (delai entre les 2 ?)

const int8_t delai_pression_relache{50} ;

bool ButtonPressed_then_Released()
{
    bool est_appuye = ButtonPressed();
    if (est_appuye)
    {
        _delay_ms(delai_pression_relache); 
        bool est_relache = ButtonReleased();
        if (est_relache)
            return true;
    }
    return false;
}
