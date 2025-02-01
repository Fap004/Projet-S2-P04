#include "Gameplay.h"
#include "ComBluetooth.h"
#include <iostream>

using namespace std;

Gameplay::Gameplay(bool bluetooth, bool verbose, bool admin) {
    this->bluetooth = bluetooth;
    this->verbose = verbose;
    this->admin = admin;
    com = new ComBluetooth("COM3");

    if (this->bluetooth) {
        configBluetooth();
    }
}

void Gameplay::loopGame() {
    std::string message;
    if (com->lireMessage(message)) {
        std::cout << "Message reçu : " << message << std::endl;
    }

    Sleep(500);
    loopGame();
}

bool Gameplay::configBluetooth() {
    if (com->ouvrirPort()) {
        bool isOk = com->envoyerMessage("Hello HC-05!");
        if (isOk) {
            if (verbose)
                printf("message envoyé");
            return true;
        }
    }
    return false;
}
