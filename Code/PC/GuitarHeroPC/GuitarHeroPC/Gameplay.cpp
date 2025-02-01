#include "Gameplay.h"
#include "ComBluetooth.h"
#include <iostream>

using namespace std;

Gameplay::Gameplay(string nomPort, bool bluetooth, bool verbose, bool admin) {
    this->estBluetooth = bluetooth;
    this->verbose = verbose;
    this->admin = admin;

    if (this->estBluetooth) {
        configBluetooth(nomPort);
    }
    else {
        configFilaire(nomPort);
    }
}

void Gameplay::loopGame() {
    if (estBluetooth) {
        std::string message;
        if (comBluetooth->lireMessage(message)) {
            std::cout << "Message reçu : " << message << std::endl;
        }
    }
    else {
        std::cout << "loopGame";
    }

    Sleep(500);
    loopGame();
}

bool Gameplay::configFilaire(std::string nomPort) {
    comFilaire = new ComFilaire(nomPort);
    return true;
}

bool Gameplay::configBluetooth(std::string nomPort) {
    comBluetooth = new ComBluetooth(nomPort);

    if (comBluetooth->ouvrirPort()) {
        bool isOk = comBluetooth->envoyerMessage("Hello HC-05!");
        if (isOk) {
            if (verbose)
                printf("message envoyé");
            return true;
        }
    }
    return false;
}
