#pragma once
#include <iostream>
#include "ComBluetooth.h"

class Gameplay
{
	public:
		Gameplay(bool bluetooth = true, bool verbose = false, bool admin = false);
		void loopGame();
		bool configBluetooth();
	private:
		ComBluetooth* com;
		bool bluetooth;
		bool verbose;
		bool admin;
};

