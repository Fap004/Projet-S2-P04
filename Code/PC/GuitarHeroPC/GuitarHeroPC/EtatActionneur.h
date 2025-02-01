#pragma once
#include <iostream>

enum BoutonEtat {
    RELACHE,
    APPUYE
};

struct EtatActionneur {
    BoutonEtat btnRouge = RELACHE;
    BoutonEtat btnJaune = RELACHE;
};

void btnRougeRelache() { std::cout << "Bouton Rouge appuyé !" << std::endl; }
void btnRougeAppuye() { std::cout << "Bouton Rouge relâché !" << std::endl; }

void btnJauneRelache() { std::cout << "Bouton Jaune appuyé !" << std::endl; }
void btnJauneAppuye() { std::cout << "Bouton Jaune relâché !" << std::endl; }

void detecteChangementEtat(const EtatActionneur& precedent, const EtatActionneur& courant) {
    if (precedent.btnRouge != courant.btnRouge) {
        if (courant.btnRouge == APPUYE) btnRougeAppuye();
        else btnRougeRelache();
    }

    if (precedent.btnJaune!= courant.btnJaune) {
        if (courant.btnJaune == APPUYE) btnJauneAppuye();
        else btnJauneRelache();
    }
}
