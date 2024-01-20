/*
 * Nom: Mohamed Omar Zedek / Souhayl Sejjari
 * Groupe 02
 * Equipe 27
 * TP2 PB2
 * Description: 
 * 
 * Identifications matérielles : interrupteur relie au 3e bit du port D | led reliee aux 2 premiers bits du port A tel que A0 --> (-) et A1 --> (+)
 */

/*
| Etat present      | debounce() | buttonPressed() | Etat suivant      |  PORTA |
|-------------------|------------|-----------------|-------------------|:------:|
| rougeBouttonAmbre | 0          | 0               | rougeBouttonAmbre |  rouge |
| rougeBouttonAmbre | 1          | 1               | rougeBouttonAmbre |  ambre |
| rougeBouttonAmbre | 1          | 0               | vertBouttonRouge  |  rouge |
| vertBouttonRouge  | 0          | 0               | vertBouttonRouge  |  vert  |
| vertBouttonRouge  | 1          | 1               | vertBouttonRouge  |  rouge |
| vertBouttonRouge  | 1          | 0               | eteintBouttonVert |  rouge |
| eteintBouttonVert | 0          | 0               | eteintBouttonVert | eteint |
| eteintBouttonVert | 1          | 1               | eteintBouttonVert |  vert  |
| eteintBouttonVert | 1          | 0               | rougeBouttonAmbre |  vert  |
*/

#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>

const uint8_t IN = 0x00;
const uint8_t OUT = 0xFF;
const uint8_t vert = 1 << PA0;
const uint8_t rouge = 1 << PA2;
const uint8_t eteint = 0;
const uint8_t bit3 = 1 << PA2;
const uint8_t delaiDebounce = 25;
const uint8_t delaiVariationAmbre = 10;

enum class Etats {rougeBouttonAmbre, vertBouttonRouge, eteintBouttonVert};

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

void couleurAmbre(){
    PORTA = vert;
    _delay_ms(delaiVariationAmbre);
    PORTA = rouge;
    _delay_ms(delaiVariationAmbre);
}

int main() {

    DDRA = OUT;
    DDRB = OUT;
    DDRC = OUT;
    DDRD = IN;

    Etats etatCourant = Etats::rougeBouttonAmbre;

    while (1){

        switch (etatCourant){
        case Etats::rougeBouttonAmbre:
            PORTA = rouge;
            if (debounce()){
                while (buttonPressed()){
                    couleurAmbre();
                    }
                etatCourant = Etats::vertBouttonRouge;
                }
            break;

        case Etats::vertBouttonRouge :
            PORTA = vert;
            if (debounce()){
                while (buttonPressed()){
                    PORTA = rouge;
                    }
                etatCourant = Etats::eteintBouttonVert;
                }
            break;

        case Etats::eteintBouttonVert:
            PORTA = eteint;
            if (debounce()){
                while (buttonPressed()){
                    PORTA = vert;
                    }
                etatCourant = Etats::rougeBouttonAmbre;
                }
            break;

        default :
            break;
        }
        
    }
    
}