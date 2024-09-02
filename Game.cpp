#include "Game.hpp"

#define RAYGUI_IMPLEMENTATION

#include <raylib.h>
#include <rlgl.h>
#include <raygui.h>
#include <utility>

int getTextWidth(int fontSize, int numChars, int numSym) {
	const int charDivFactor = fontSize / 2;
	const int symDivFactor = fontSize / 4;
	return (numChars * charDivFactor) - (numSym * symDivFactor);
}

namespace EnttBoids {
	Game::Game(const int screenWidth, const int screenHeight, const int fps)
		: m_windowSize{screenWidth, screenHeight}
	{
		//SetTargetFPS(fps);
		//ToggleFullscreen();
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

		// draw ui elements
		UI();
		// draw boids
		m_flock.ForEachBoid([&](const Vector2<float>& Loc, const Vector2<float>& Vel) {
			Vector2 Dir{ Vel };
			Dir.Normalize();

			int side = 10;
			float height = sqrt(pow(side, 2) - pow(side / 2, 2));

			// begin push matrix
			rlPushMatrix();

			float angle = atan2(Dir.y, Dir.x) * RAD2DEG;

			rlTranslatef(Loc.x, Loc.y, 0.f);
			rlRotatef(angle, 0.0f, 0.0f, 1.0f);

			DrawTriangle({ -height/2.f, -side/2.f }, { -height / 2.f, side / 2.f }, { (height + 5) / 2.f, 0.f}, YELLOW);

			rlPopMatrix();
			// end push matrix
		});
	}

	void Game::UI()
	{
		static constexpr float ratio{ (float)Settings::screenHeight / (float)Settings::screenWidth };
		static constexpr float sliderWidth{ static_cast<int>((float)Settings::screenWidth / 10.f * ratio) };
		static constexpr float sliderHeight{ static_cast<int>((float)Settings::screenHeight / 18.f * ratio) };
		static const float halfScreenWidth{ (float)Settings::screenWidth / 2.f };
		
		static const float slidersHeightPosition = (float)m_windowSize.y - sliderHeight - 50;
		static const float textVertPos = m_windowSize.y - 35;
		
		// Separation
		float separationPositionX = halfScreenWidth - (sliderWidth / 2.f) - sliderWidth - (m_windowSize.x / 15);
		const char* separationText = TextFormat("Separation: %.2f", m_flock.GetRulesFactorRef().separation);
		const int separationTextWidth = getTextWidth(Settings::fontSize, 14, 2);
		const int separationTextPosX = separationPositionX + (sliderWidth / 2) - (separationTextWidth / 2);
		GuiSlider(Rectangle{ separationPositionX, slidersHeightPosition, (float)sliderWidth, (float)sliderHeight}, "Min", "Max", m_flock.GetSeparationPtr(), m_flock.GetRulesFactorRef().min, m_flock.GetRulesFactorRef().max);
		DrawText(separationText, separationTextPosX, textVertPos, Settings::fontSize, DARKPURPLE);
		
		// Alignment
		const float alignmentPosx = (float)(m_windowSize.x / 2.f) - (sliderWidth / 2.f);
		const char* alignmentText = TextFormat("Alignment: %.2f", m_flock.GetRulesFactorRef().alignment);
		const int alignmentTextWidth = getTextWidth(Settings::fontSize, 13, 2);
		const int alignmentTextPosX = ((float)m_windowSize.x / 2.f) - (alignmentTextWidth / 2);
		GuiSlider(Rectangle{ alignmentPosx, slidersHeightPosition, (float)sliderWidth, (float)sliderHeight }, "Min", "Max", m_flock.GetAlignmentPtr(), m_flock.GetRulesFactorRef().min, m_flock.GetRulesFactorRef().max);
		DrawText(alignmentText, alignmentTextPosX, textVertPos, Settings::fontSize, DARKPURPLE);
		
		// Cohesion
		float cohesionPositionX = halfScreenWidth + (sliderWidth / 2.f) + (m_windowSize.x / 15);
		const char* cohesionText = TextFormat("Cohesion: %.2f", m_flock.GetRulesFactorRef().cohesion);
		const int cohesionTextWidth = getTextWidth(Settings::fontSize, 12, 2);
		const int cohesionTextPosX = cohesionPositionX + (sliderWidth / 2.f) - (cohesionTextWidth / 2);
		GuiSlider(Rectangle{ cohesionPositionX, slidersHeightPosition, (float)sliderWidth, (float)sliderHeight }, "Min", "Max", m_flock.GetCohesionPtr(), m_flock.GetRulesFactorRef().min, m_flock.GetRulesFactorRef().max);
		DrawText(cohesionText, cohesionTextPosX, textVertPos, Settings::fontSize, DARKPURPLE);
	}

}

