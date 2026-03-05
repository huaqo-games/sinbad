#include "app.h"

void InitMenuSettings(MenuSettings *s)
{
	int windowWidth = GetScreenWidth();
	int windowHeight = GetScreenHeight();
	Vector2 windowCenter = {windowWidth / 2, windowHeight / 2};

	Vector2 standardButtonDimensions = {100, 50};
	int standardSpacing = standardButtonDimensions.y / 2;

	Vector2 button1Pos = {windowCenter.x, windowCenter.y};
	Vector2 button2Pos = {windowCenter.x, windowCenter.y + standardButtonDimensions.y * 1 + standardSpacing * 1};
	Vector2 button3Pos = {windowCenter.x, windowCenter.y + standardButtonDimensions.y * 2 + standardSpacing * 2};

	s->showFPS = initButton("showFPS", standardButtonDimensions, button1Pos);
	s->limitFPS = initButton("limitFPS", standardButtonDimensions, button2Pos);
	s->soundtrackOn = initButton("soundtrackOn", standardButtonDimensions, button3Pos);
}

void UpdateMenuSettings(MenuSettings *s, MenuView *menuView, State* state, Flags *flags)
{

	if(isButtonClicked(&s->showFPS)){
		flags->showFPS = !flags->showFPS;
	}

	if(isButtonClicked(&s->limitFPS)){
		flags->limitFPS = !flags->limitFPS;
	}

	if(isButtonClicked(&s->soundtrackOn)){
		flags->soundtrackOn = !flags->soundtrackOn;
	}

	if (IsKeyPressed(KEY_ESCAPE)){
		*menuView = MAIN;
	}

	if (WindowShouldClose() && !IsKeyPressed(KEY_ESCAPE)){
		state->running = false;
	}

	
}

void RenderMenuSettings(MenuSettings *s, Flags *flags)
{
	BeginDrawing();
	ClearBackground(BLACK);

	renderButton(&s->showFPS);
	renderButton(&s->limitFPS);
	renderButton(&s->soundtrackOn);

	if (flags->showFPS){
		DrawFPS(10,10);
	}

	EndDrawing();
	
}

void ClenupMenuSettings(MenuSettings *s){

}

