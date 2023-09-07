#pragma once
enum class OBJECT_SERIAL_NAME
{
	STAR_BULLET,
	STAR_BULLET_STRENGTH,
	KIRBY_BREATH,
	WHISPY_BREATH,
	FOOD,
	LIFEUP,
	MAX_TOMATO
};
class NeutralObj : public ObImage
{
public:
	float				lifeTime;
	Color				pointColor;
	vector<GameObject*>	interactObjList;
public:
	//생성자 호출 시에 serial name에 따라 자동으로 초기화합니다
	NeutralObj(OBJECT_SERIAL_NAME _serialName);
	void Update();
	void DrawCall();
	void SetDirSpeed(Vector2 _dir, float _speed);
	OBJECT_SERIAL_NAME GetSerialName() const { return serialName; }
private:
	float				speed;
	Vector2				dir;
	vector<ObImage*>	subImage;
	OBJECT_SERIAL_NAME	serialName;
};

