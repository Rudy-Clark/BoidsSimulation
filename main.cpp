#include "Game.hpp"
#include "Settings.hpp"

using namespace Settings;

int main() {
	InitWindow(screenWidth, screenHeight, title);

	EnttBoids::Game game(screenWidth, screenHeight, FPS);
	game.Run();

	// Close window after end of the game loop
	CloseWindow();
}