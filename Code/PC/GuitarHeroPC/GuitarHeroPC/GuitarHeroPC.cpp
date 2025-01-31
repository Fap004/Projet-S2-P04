#include "ComBluetooth.h"

/*
    FICHIER MAIN
*/

int main() {
    const bool EST_BLUETOOTH = true;

    if (EST_BLUETOOTH) {
        ComBluetooth com("COM3");
        if (com.ouvrirPort()) {
            bool isOk = com.envoyerMessage("Hello HC-05!");
            if (isOk) {
                printf("message envoyé");
            }
        }
    }

    return 0;
}
