#pragma once

#define AIR_AREA GameManager::IsColorMatch(pointColor, 255, 0, 255)					//Non-Render Color
#define WALL_AREA_LEFT GameManager::IsColorMatch(pointColor, 0, 255, 0)				//Green
#define WALL_AREA_RIGHT GameManager::IsColorMatch(pointColor, 0, 0, 255)			//Blue
#define LANDING_AREA GameManager::IsColorMatch(pointColor, 255, 0, 0)				//Red
#define INTERPOL_AREA_RISE GameManager::IsColorMatch(pointColor, 0, 0, 0)			//Black
#define INTERPOL_AREA_DESC_SLOPE GameManager::IsColorMatch(pointColor, 0, 255, 255)	//Sky
#define INTERPOL_AREA_DESC GameManager::IsColorMatch(pointColor, 128, 255, 255)		//Bright Sky
#define INTERPOL_AREA_PULL_LEFT GameManager::IsColorMatch(pointColor, 128, 255, 0)	//Grass
#define INTERPOL_AREA_PULL_RIGHT GameManager::IsColorMatch(pointColor, 128, 0, 255)	//Purple

#define UPDATE_COLOR pointColor = GameManager::GetPointColor(this);

#define MAINSTAGE GameManager::MainStage
#define MAINPLAYER GameManager::MainPlayer

class Enemy;
class Player;
class Stage;

struct Effect
{
	ObImage*	image;
	float		lifeTime;
	float		maxLifeTime;
	Effect(ObImage* _image, float _lifeTime) : image(_image), lifeTime(0), maxLifeTime(_lifeTime) {}
};

class GameManager {
public:
	static int		tmpPosListNum;
	static wstring	tmpStageImgName;

	static int	Score;
	static bool DebugMode;
	static Stage* MainStage;
	static Player* MainPlayer;
	static vector<Stage*> StageList;
	static vector<Effect*> Effect_SpreadStar;
public:
	static void Init();
	static void InitEffect(Effect* effect);
	static void	ActiveEffect(GameObject* ob, Vector2 pos = Vector2(0,0));
	static void Update();
	static void Render();
	static bool IsColorMatch(Color& cl, float r, float g, float b, float a = 255);
	static bool ChangeMainStage(wstring _stageImgName, int posListNum = 0);
	static Color GetPointColor(GameObject* gameObject);
};


