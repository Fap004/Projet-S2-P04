#include <windows.h>
#include <iostream>

/* CLASSE GESTION DE COMMUNICATION PAR BLUETOOTH
* Il faut activer le bluetooth à l'arduino
* Il faut déjà être connecter par bluetooth au arduino
* Il faut vérfier que la connection au HC-05 est stable
* Si une chose n'est pas ok, c'est inutile de tester ce module
*/

class ComBluetooth {
private:
    HANDLE hSerial;
    std::string portName;

public:
    ComBluetooth(const std::string& port) : portName(port), hSerial(INVALID_HANDLE_VALUE) {}

    bool ouvrirPort() {
        hSerial = CreateFileA(portName.c_str(), GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, 0, 0);
        if (hSerial == INVALID_HANDLE_VALUE) {
            std::cerr << "Erreur lors de l'ouverture du port " << portName << std::endl;
            return false;
        }
        return configurerPort();
    }

    bool configurerPort() {
        DCB dcbSerialParams = { 0 };
        dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
        if (!GetCommState(hSerial, &dcbSerialParams)) {
            std::cerr << "Erreur lors de la récupération des paramètres du port." << std::endl;
            fermerPort();
            return false;
        }

        dcbSerialParams.BaudRate = CBR_9600;
        dcbSerialParams.ByteSize = 8;
        dcbSerialParams.StopBits = ONESTOPBIT;
        dcbSerialParams.Parity = NOPARITY;

        if (!SetCommState(hSerial, &dcbSerialParams)) {
            std::cerr << "Erreur lors de la configuration du port." << std::endl;
            fermerPort();
            return false;
        }
        return true;
    }

    bool envoyerMessage(const std::string& message) {
        if (hSerial == INVALID_HANDLE_VALUE) {
            std::cerr << "Le port n'est pas ouvert." << std::endl;
            return false;
        }
        DWORD bytesWritten;
        if (!WriteFile(hSerial, message.c_str(), message.size(), &bytesWritten, NULL)) {
            std::cerr << "Erreur lors de l'écriture sur le port série." << std::endl;
            return false;
        }
        return true;
    }

    void fermerPort() {
        if (hSerial != INVALID_HANDLE_VALUE) {
            CloseHandle(hSerial);
            hSerial = INVALID_HANDLE_VALUE;
        }
    }

    ~ComBluetooth() {
        fermerPort();
    }
};