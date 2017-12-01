// @author Germán Caíno
// @version 1.0.0 30/11/17
// -----------------------------------------
#ifdef _DEBUG
#include "vld.h"
#endif
// -----------------------------------------
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "GameLoop.h"
// -----------------------------------------
int main()
{
	std::srand(std::time(NULL));

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

