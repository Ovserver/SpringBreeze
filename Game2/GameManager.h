#pragma once
#define MAX_COMBO_HISTORY 5
class Stage
{
public:
	ObImage*	image;
	ObImage*	collider;
	wstring		imageFName;
	wstring		colFName;
	vector<Enemy*>	enemyList;
public:
	Stage(wstring _stageImgName, wstring _stageColName)
	{
		image = new ObImage();
		collider = new ObImage();
		imageFName = _stageImgName;
		colFName = _stageColName;
		image->LoadFile(imageFName);
		collider->LoadFile(colFName);

		image->SetScale().x = image->imageSize.x * IMG_SCALE;
		image->SetScale().y = image->imageSize.y * IMG_SCALE;
		image->SetPivot() = OFFSET_LT;

		collider->SetScale().x = image->imageSize.x * IMG_SCALE;
		collider->SetScale().y = image->imageSize.y * IMG_SCALE;
		collider->SetPivot() = OFFSET_LT;
	}
	void SetImagePos(float x, float y)
	{
		image->SetWorldPosX(x);
		image->SetWorldPosY(y);
		collider->SetWorldPosX(x);
		collider->SetWorldPosY(y);
	}
};
struct ComboMap
{
	int comboMaps[MAX_COMBO_HISTORY];
	int comboLength = 0;
};
class GameManager {
public:
	static bool DebugMode;
	static Stage* MainStage;
	static vector<Stage*> StageList;
public:
	static bool IsColorMatch(Color& cl, float r, float g, float b);
	static void AddStage(wstring stageImgName, wstring stageColName);
	static bool ChangeMainStage(wstring stageFname);
	static void Render();
};
class MecanimManager
{
public:
	static int ComboHistory[MAX_COMBO_HISTORY];
public:
	static void ComboInput(int keyCode);
	static void ComboClear();
	static bool ComboMatch(ComboMap* comboMap);
};

