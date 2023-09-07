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
	//������ ȣ�� �ÿ� serial name�� ���� �ڵ����� �ʱ�ȭ�մϴ�
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

