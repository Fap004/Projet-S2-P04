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
        std::string message;
        if (comFilaire->recevoirMessage(message)) {
            interpreterMsg(message);
        }
    }
    Sleep(500);
    loopGame();
}

bool Gameplay::configFilaire(std::string nomPort) {
    comFilaire = new ComFilaire(nomPort);
    return true;
}

void Gameplay::interpreterMsg(string msg) {
    json j = json::parse(msg);

    for (auto it = j.begin(); it != j.end(); ++it) {
        if (it.key() == "message") {
            std::cout << it.value() << std::endl;
        }
        if (it.key() == "bouton1" && it.value() == "released") {
            std::cout << "note rouge appuyé" << std::endl;
        }
    }
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
