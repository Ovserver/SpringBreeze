#include "stdafx.h"
#include "MecanimManager.h"
#include "Text.h"
#include "Player.h"
#include "Main.h"

float maxInvisibleTime = 0.6f;
float invisibleTime = 0;
float maxBoostTime = 3.5f;
float boostTime = 0;
float playerSpeed = 1.0f;
float upVector = 0;
int	fallSafety = 0;
bool jumpable = true;
bool isSlide = false;
bool isGameover = false;
PlayerState STATE = PlayerState::NONE;
Main::Main()
{

}

Main::~Main()
{
}
void Main::Init()
{
	mainPlayer.Init();
}

void Main::Release()
{

}
float	comboCount = 0;
float	slideTime = 0;
bool	isRight = true;
bool	isMove = false;
void Main::Update()
{
	mainPlayer.Update();
	//reset
	if (INPUT->KeyDown('R'))
	{
		this->Init();
	}
	if (INPUT->KeyDown('D'))
	{
		isGameover = true;
	}
	if (isGameover)
		return;
	if (INPUT->KeyDown('B'))
	{
		boostTime = maxBoostTime;
	}
}

void Main::LateUpdate()
{
	if (isGameover)
		return;
	mainPlayer.LateUpdate();
}

void Main::Render()
{
	mainPlayer.Render();
}

void Main::ResizeScreen()
{
}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
	app.SetAppName(L"Game2");
	app.SetInstance(instance);
	app.InitWidthHeight(496.0f, 530.0f); // 248, 265
	WIN->Create();
	Main* main = new Main();
	int wParam = (int)WIN->Run(main);
	SafeDelete(main);
	WIN->Destroy();
	WIN->DeleteSingleton();

	return wParam;
}