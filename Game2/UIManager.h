#pragma once
class UIManager {
public:
	static ObRect* UI_fadescreen;
	static ObImage* UI_standard;
	static ObImage* UI_enemy;
	static ObRect* player_HpBar;
	static ObRect* enemy_HpBar;
	static ObRect* backfaceUI;
	static bool		turnOn;
public:
	static void Init();
	static void Update();
	static void Render(Camera* camUI);
	static void FadeScreen(bool _turnOn, wstring stageName, int num);
};