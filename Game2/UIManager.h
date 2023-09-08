#pragma once
class UIManager {
public:
	static bool		turnOn;
	static float	waveTime;
	static Vector2	origin;
	static ObRect*	UI_fadescreen;
	static ObImage* UI_standard;
	static ObImage* UI_enemy;
	static ObRect*	player_HpBar;
	static ObRect*	enemy_HpBar;
	static ObRect*	backfaceUI;
public:
	static void Init();
	static void Update();
	static void Render(Camera* camUI);
	static void FadeScreen(bool _turnOn, wstring stageName, int num);
};