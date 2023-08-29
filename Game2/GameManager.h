#pragma once
#define MAX_COMBO_HISTORY 5
struct ComboMap
{
	int comboMaps[MAX_COMBO_HISTORY];
	int comboLength = 0;
};
class MecanimManager
{
public:
	static int ComboHistory[MAX_COMBO_HISTORY];
	static void ComboInput(int keyCode);
	static void ComboClear();
	static bool ComboMatch(ComboMap* comboMap);
};

