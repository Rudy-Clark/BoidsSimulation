#include "Game.hpp"

#include <raylib.h>
#include <rlgl.h>
#include <raymath.h>
#include <assert.h>
#include "Boid.hpp"

namespace EnttBoids {
	Game::Game(const int screenWidth, const int screenHeight, const char* title, const int fps)
		: m_windowDimension{screenWidth, screenHeight}
	{
		InitWindow(screenWidth, screenHeight, title);
		//SetTargetFPS(fps);
		ToggleFullscreen();

		// init our boids
		m_flock.ForEach([&](Boid& boid) {
			boid = Boid(GetRandomValue(0, screenWidth), GetRandomValue(0, screenHeight));
			//boid = Boid(screenWidth / 2, screenHeight / 2);
		});
	}

	Game::~Game() noexcept
	{
		assert(GetWindowHandle());
		CloseWindow();
	}

	void Game::Run()
	{
		while (!WindowShouldClose()) 
		{
			Tick(GetFrameTime() * 100.f);
		}
	}

	void Game::Tick(const float DeltaTime)
	{
		BeginDrawing();
		Update(DeltaTime);
		Render();
		EndDrawing();
	}

	void Game::Update(const float DeltaTime)
	{
		m_flock.Flocking(DeltaTime);
	}

	void Game::Render()
	{
		ClearBackground(BLACK);
		DrawFPS(20, 20);

		m_flock.ForEach([&](Boid& boid) {
			Vector2 BoidLocation{boid.GetLocation()};
			if (BoidLocation.x < 0) 
			{
				BoidLocation.x = m_windowDimension.x;
				boid.SetLocation(BoidLocation);
			}
			else if (BoidLocation.x > m_windowDimension.x) 
			{
				BoidLocation.x = 0;
				boid.SetLocation(BoidLocation);
			}
			
			if (BoidLocation.y < 0)
			{
				BoidLocation.y = m_windowDimension.y;
				boid.SetLocation(BoidLocation);
			}
			else if (BoidLocation.y > m_windowDimension.y)
			{
				BoidLocation.y = 0;
				boid.SetLocation(BoidLocation);
			}

			Vector2 Location{ boid.GetLocation() };
			Vector2 Dir{ boid.GetVelocity() };
			Dir.Normalize();
			
			////DrawLine(Location.x, Location.y, (Location + (Dir * 10.f)).x, (Location + (Dir * 10.f)).y, RED);
			//// Separation Debug Draw
			//DrawCircleLines(Location.x, Location.y, 24, BLUE);
			//// Alignment
			//DrawCircleLines(Location.x, Location.y, 25, RED);
			//// Cohesion
			//DrawCircleLines(Location.x, Location.y, 50, GREEN);



			int side = 10;
			float height = sqrt(pow(side, 2) - pow(side / 2, 2));

			rlPushMatrix();
			
			
			float angle = atan2(Dir.y, Dir.x) * RAD2DEG;

			rlTranslatef(Location.x, Location.y, 0.f);
			rlRotatef(angle, 0.0f, 0.0f, 1.0f);

			DrawTriangle({ -height/2.f, -side/2.f }, { -height / 2.f, side / 2.f }, { (height + 5) / 2.f, 0.f}, YELLOW);

			rlPopMatrix();
		});
	}

}

