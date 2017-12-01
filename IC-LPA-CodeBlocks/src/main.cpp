#ifdef _DEBUG
#include "vld.h"
#endif
// -----------------------------------------
#include <iostream>
#include "GameLoop.h"
// -----------------------------------------
/**
@author Germ�n Ca�no
@version 1.0.0 30/11/17
*/
// -----------------------------------------
int main()
{
	try
	{
		lpa::GameLoop game;
		game.run();
	}
	catch (...)
	{
		std::cerr << "Abnormal termination\n" << std::endl;
	}

	return 0;
}

