#pragma once
#include <iostream>
#include "ComBluetooth.h"
#include "ComFilaire.h"


class Gameplay
{
	public:
		Gameplay(std::string comPort="COM5", bool bluetooth = true, bool verbose = false, bool admin = false);
		void loopGame();
		void loopMenu();
		
		bool configBluetooth(std::string nomPort);
		bool configFilaire(std::string nomPort);
		void interpreterMsg(std::string);


	private:
		ComBluetooth* comBluetooth;
		ComFilaire* comFilaire;
		bool estBluetooth;
		bool verbose;
		bool admin;
};

