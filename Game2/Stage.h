#pragma once

enum class COLLISION_CHECK_TYPE
{
	INHOLE,
	ATTACK_BULLET_ONCE,
	ATTACK_BULLET_ASSAULT,
	ATTACK_AREA,
	COLLISION_OBJECT
};
enum class BG_TYPE
{
	ONCE, REPEAT
};
enum class CAM_LOCKIN_TYPE
{
	SINGLE, CONTINUOS
};
class Portal {
public:
	ObImage	effect1;
	ObImage	effect2;
	//포탈의 실제 인식범위
	ObRect	rect;
	//이동할 스테이지의 파일 이름
	wstring	destStageFname;
	//stage내 여러개의 포탈이 있을 경우 특정 포탈 지정 (기본값 0)
	UINT	initPosNum = 0;
	Portal(Vector2 pos)
	{
		rect.SetWorldPos(pos);
		rect.SetPivot() = OFFSET_B;
		rect.SetScale().x = 8 * IMG_SCALE;
		rect.SetScale().y = 10 * IMG_SCALE;
		rect.collider = COLLIDER::RECT;
		rect.isFilled = false;

		effect1.SetWorldPos(pos + UP * 20 * IMG_SCALE);
		effect1.LoadFile(L"object_starbullet.png");
		effect1.SetScale().x = effect1.imageSize.x / 4.0f * IMG_SCALE;
		effect1.SetScale().y = effect1.imageSize.y * IMG_SCALE;
		effect1.maxFrame.x = 4;
		effect1.ChangeAnim(ANIMSTATE::LOOP, 1.0f / 12);
		effect1.SetPivot() = OFFSET_B;

		effect2.SetWorldPos(pos);
		effect2.LoadFile(L"effect_portal_sub.png");
		effect2.SetScale().x = effect2.imageSize.x / 6.0f * IMG_SCALE;
		effect2.SetScale().y = effect2.imageSize.y * IMG_SCALE;
		effect2.maxFrame.x = 6;
		effect2.ChangeAnim(ANIMSTATE::LOOP, 1.0f / 12);
		effect2.SetPivot() = OFFSET_B;
	}
	void Render() { effect1.Render(); effect2.Render(); }
};
class Stage
{
public:
	bool				mCamLock;
	Vector2				mCamLockPos;
	Vector2				mCamLockRangePosMin;
	Vector2				mCamLockRangePosMax;
	GameObject* mCamLockEventObject;
	CAM_LOCKIN_TYPE		mCamLockEventType;
	Vector2				mLimitCameraPosX;
	Vector2				mLimitCameraPosY;
	vector<Vector2>		mPlayerInitPos;
	vector<ObImage*>	mBGImage;
	vector<Vector2>		mBGImagePos;
	vector<ObImage*>	mImage;
	vector<Vector2>		mImagePos;
	ObImage* mCollider;
	wstring				mImageFName;
	wstring				mColFName;
	vector<Enemy*>		mEnemyList;
	vector<Portal>		mPortalList;
	BG_TYPE				mBGType;
	string				mBGMkey;
public:
	Stage(wstring _stageImgName, wstring _stageColName, wstring _stageBGImgName, bool nonScale = false);
	void Init();
	void Update();
	//player 좌표에 따라 main camera 위치와 배경을 조정합니다
	void LateUpdate();
	void Render();
	void SetImagePos(Vector2 pos);
	void SetBGImagePos(Vector2 pos);
	void AddImage(wstring _stageImgName, Vector2 imagePos);
	void AddBGImage(wstring _stageImgName, Vector2 imagePos, int frame = 1, bool isVertical = false, bool nonScale = false);
	void AddEnemy(Enemy* enemy);
	void AddPortal(Vector2 pos, wstring _destStageName, int _initPosNum = 0);
	bool PortalCollisionCheck(GameObject* col);
	void EnemyCollisionCheck(GameObject* col, COLLISION_CHECK_TYPE checkType = COLLISION_CHECK_TYPE::INHOLE, int damage = 0, bool attackBoss = true);
	bool EnemyInholingCheck();
};