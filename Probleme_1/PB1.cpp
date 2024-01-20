/*
 * Nom: Mohamed Omar Zedek / Souhayl Sejjari
 * Groupe 02
 * Equipe 27
 * TP2 PB1
 * Description: Allumage de la lampe (eteinte) en vert apres 3 cliques sur l'interrupteur puis retour a l'etat initial (eteint)
 * Le programme utilise un switch case afin de naviguer entre les differents etats, et incremente le compteur de clique de 1 a chaque clique. 
 * Lorsque le compteur est a 0, la led est a l'etat initial. Lorsqu'il vaut 1 ou 2 la led est a l'etat intermediaire. Et lorsque le compteur atteint 3, 
 * la led passe a l'etat allumee en vert et le compteur et reinitialise.
 * 
 * Identifications matérielles : interrupteur relie au 3e bit du port D | led reliee aux 2 premiers bits du port A tel que A0 --> (-) et A1 --> (+)
 */

/* Tableau d'etats
|    Etat present   | buttonPressedThenReleased() | nbCliquesEffectues |    Etat suivant   | nbCliquesEffectues |  PORTA |
|:-----------------:|:---------------------------:|:------------------:|:-----------------:|:------------------:|:------:|
|    etatInitial    |              0              |          0         |    etatInitial    |          0         | eteint |
|    etatInitial    |              1              |          0         | etatIntermediaire |          1         | eteint |
| etatIntermediaire |              0              |          1         | etatIntermediaire |          1         | eteint |
| etatIntermediaire |              1              |          1         | etatIntermediaire |          2         | eteint |
| etatIntermediaire |              0              |          2         | etatIntermediaire |          2         | eteint |
| etatIntermediaire |              1              |          2         | etatIntermediaire |          3         | eteint |
| etatIntermediaire |              X              |          3         |   etatAllumeVert  |          0         | eteint |
|   etatAllumeVert  |              X              |          0         |    etatInitial    |          0         |  vert  |
*/

#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>

const uint8_t IN = 0x00;
const uint8_t OUT = 0xFF;
const uint8_t vert = 1 << PA0;
const uint8_t eteint = 0;
const uint8_t bit3 = 1 << PA2;
const uint8_t delaiDebounce = 25;
const uint16_t delaiLedAllumee = 2000;

enum class Etats {etatInitial, etatIntermediaire, etatAllumeVert};

bool buttonPressed(){
    return (PIND & bit3);
}

bool debounce(){
    if (buttonPressed()){
        _delay_ms(delaiDebounce);
        if (buttonPressed()){
            return true;
        }
        return false;
    }
    return false;
}

bool buttonPressedThenReleased() {
    if (debounce()){
        while (debounce()) {
            
            }
        return true;
    }
}

int main() {

    DDRA = OUT;
    DDRB = OUT;
    DDRC = OUT;
    DDRD = IN;


    uint8_t nbCliquesEffectues = 0;
    Etats etatCourant = Etats::etatInitial;

    while (1){
    
    switch (etatCourant){
    case Etats::etatInitial :
        PORTA = eteint;
        if (buttonPressedThenReleased()){
            etatCourant = Etats::etatIntermediaire;
            nbCliquesEffectues ++;
        }
        break;
    
    case Etats::etatIntermediaire :
        if (nbCliquesEffectues == 3){
            etatCourant = Etats::etatAllumeVert;
        }
        else if (buttonPressedThenReleased()){
            nbCliquesEffectues ++;
        }
        break;
    case Etats::etatAllumeVert :
        PORTA = vert;
        _delay_ms(delaiLedAllumee);
        nbCliquesEffectues = 0;
        etatCourant = Etats::etatInitial;
        break;

    default:
        break;
        }
    }    
}