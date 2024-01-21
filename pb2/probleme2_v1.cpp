// INFOOOOOOOOOOOOOOOOOOOOOOS //

// table d'etat //

#define F_CPU 8000000UL // 8 MHz
#include <avr/io.h>
#include <util/delay.h>


// prototypes

/* Bouton poussoir*/
bool ButtonPressed();
bool ButtonReleased();

/* Couleur */
void DEL_libre_Eteinte();
void DEL_libre_Rouge();
void DEL_libre_Vert();
void DEL_libre_Ambre();

// Etats

enum etat_robot
{
    etat_Rouge_Libre,
    etat_Ambre_Presse,
    etat_Vert_Libre,
    etat_Rouge_Presse,
    etat_Eteint_Libre,
    etat_Vert_Presse
}; // Presse = le bouton est presse ; Libre = Rien n'appuie sur le bouton

// Constantes du main
uint8_t mask_PORTA{(1 << PA1) | (1 << PA0)};
uint8_t mask_PORTD{~(1 << PD2)};

// Main function

int main()
{
    // Definition du mode sortie / entree des ports
    DDRA |= mask_PORTA; // A0 et A1 en sortie
    DDRD &= mask_PORTD; // D2 en entree

    // Etat initial
    etat_robot etat_present{etat_Rouge_Libre};

    // main loop
    while (true)
    {
        switch (etat_present)
        {
        case etat_Rouge_Libre:
        {
            DEL_libre_Rouge();

            bool bouton_appuye{ButtonPressed()};
            if (bouton_appuye)
                etat_present = etat_Ambre_Presse;
            break;
        }
        case etat_Ambre_Presse:
        {
            DEL_libre_Ambre();

            bool bouton_libre(ButtonReleased());
            if (bouton_libre)
                etat_present = etat_Vert_Libre;
            break;
        }
        case etat_Vert_Libre:
        {
            DEL_libre_Vert();

            bool bouton_appuye{ButtonPressed()};
            if (bouton_appuye)
                etat_present = etat_Rouge_Presse;
            break;
        }
        case etat_Rouge_Presse:
        {
            DEL_libre_Rouge();

            bool bouton_libre(ButtonReleased());
            if (bouton_libre)
                etat_present = etat_Eteint_Libre;
            break;
        }

        case etat_Eteint_Libre:
        {
            DEL_libre_Eteinte();

            bool bouton_appuye{ButtonPressed()};
            if (bouton_appuye)
                etat_present = etat_Vert_Presse;
            break;
        }

        case etat_Vert_Presse:
        {
            DEL_libre_Vert();

            bool bouton_libre(ButtonReleased());
            if (bouton_libre)
                etat_present = etat_Rouge_Libre; // retour a l'etat initial
            break;
        }
        }
    }
}

// Definition de fonctions

/*Etat du bouton*/

const uint8_t delai_debounce{10};         // delai en ms
const uint8_t masque_boutton{(1 << PD2)}; // masque pour verifier l'etat de la PIND2

// fonction qui verifie si le bouton a ete presse ou relache selon le parametre --> debounce
bool ButtonPressed()
{
    bool is_state_button = PIND & masque_boutton;
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

/*Couleur de la DEL libre*/

// On considere qu'on utilise les broches A0 / A1 pour la DEL libre

const uint8_t delay_couleur_ambre{10};

void DEL_libre_Eteinte()
{
    uint8_t mask_eteint{((1 << PA1) | (1 << PA0))};
    PORTA |= mask_eteint;
}

void DEL_libre_Rouge()
{
    PORTA |= (1 << PA1);
    PORTA &= ~(1 << PA0);
}

void DEL_libre_Vert()
{
    PORTA |= (1 << PA0);
    PORTA &= ~(1 << PA1);
}

void DEL_libre_Ambre()
{
    DEL_libre_Rouge();
    _delay_ms(delay_couleur_ambre);
    DEL_libre_Vert();
    _delay_ms(delay_couleur_ambre);
}