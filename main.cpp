#include "Game.hpp"
#include "Settings.hpp"

using namespace Settings;

int main() {
	EnttBoids::Game game(screenWidth, screenHeight, title, FPS);
	
	game.Run();
}