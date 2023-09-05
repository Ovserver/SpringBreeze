#pragma once
enum class OBJECT_SERIAL_NAME
{
	STAR_BULLET,
	KIRBY_BREATH,
	WHISPY_BREATH,
	FOOD,
	LIFEUP,
	MAX_TOMATO
};
class NeutralObj : public ObImage
{
public:
	//������ ȣ�� �ÿ� serial name�� ���� �ڵ����� �ʱ�ȭ�մϴ�
	NeutralObj(OBJECT_SERIAL_NAME _serialName);
	void Update();
	void SetDirSpeed(Vector2 _dir, float _speed) { dir = _dir; speed = _speed; }
	OBJECT_SERIAL_NAME GetSerialName() const { return serialName; }
private:
	float	speed;
	Color	pointColor;
	Vector2	dir;
	OBJECT_SERIAL_NAME serialName;
};

