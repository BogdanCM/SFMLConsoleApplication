#include <iostream>
#include "Game.h"
#include <string>

using namespace sf;
using namespace std;


int main()
{

	std::srand(static_cast<unsigned>(time(NULL)));

	Game game;
	
	while(game.getWindowStat())
	{
		//Update Fun.
		game.update();

		//Render
		game.render();
	}

	return 0;
}