#include "stdafx.h"
#include "Text.h"

void Text::Init()
{
	value = 0;
	scaler = 1.0f;
	for (size_t i = 0; i < TEXTRECT_LEN; i++)
	{
		textRect[i].SetParentT(*this);
		textRect[i].color = tColor;
	}
	UpdateMatrix();

}

void Text::Render(Camera* cam)
{
	if (value == 0) {
		textRect[0].Render(cam);
		textRect[1].Render(cam);
		textRect[2].Render(cam);
		textRect[4].Render(cam);
		textRect[5].Render(cam);
		textRect[6].Render(cam);
	}
	else if (value == 1) {
		textRect[2].Render(cam);
		textRect[6].Render(cam);
	}
	else if (value == 2) {
		textRect[1].Render(cam);
		textRect[2].Render(cam);
		textRect[3].Render(cam);
		textRect[4].Render(cam);
		textRect[5].Render(cam);
	}
	else if (value == 3) {
		textRect[1].Render(cam);
		textRect[2].Render(cam);
		textRect[3].Render(cam);
		textRect[5].Render(cam);
		textRect[6].Render(cam);
	}
	else if (value == 4) {
		textRect[0].Render(cam);
		textRect[2].Render(cam);
		textRect[3].Render(cam);
		textRect[6].Render(cam);
	}
	else if (value == 5) {
		textRect[0].Render(cam);
		textRect[1].Render(cam);
		textRect[3].Render(cam);
		textRect[5].Render(cam);
		textRect[6].Render(cam);
	}
	else if (value == 6) {
		textRect[0].Render(cam);
		textRect[1].Render(cam);
		textRect[3].Render(cam);
		textRect[4].Render(cam);
		textRect[5].Render(cam);
		textRect[6].Render(cam);
	}
	else if (value == 7) {
		textRect[1].Render(cam);
		textRect[2].Render(cam);
		textRect[6].Render(cam);
	}
	else if (value == 8) {
		textRect[0].Render(cam);
		textRect[1].Render(cam);
		textRect[2].Render(cam);
		textRect[3].Render(cam);
		textRect[4].Render(cam);
		textRect[5].Render(cam);
		textRect[6].Render(cam);
	}
	else if (value == 9) {
		textRect[0].Render(cam);
		textRect[1].Render(cam);
		textRect[2].Render(cam);
		textRect[3].Render(cam);
		textRect[5].Render(cam);
		textRect[6].Render(cam);
	}
}

void Text::Update()
{
	textRect[0].SetLocalPosX(-12.5f * scaler);
	textRect[0].SetLocalPosY(+12.5f * scaler);
	textRect[0].SetScale().x = 5 * scaler;
	textRect[0].SetScale().y = 25 * scaler;

	textRect[1].SetLocalPosX(0 * scaler);
	textRect[1].SetLocalPosY(+25.0f * scaler);
	textRect[1].SetScale().x = 25 * scaler;
	textRect[1].SetScale().y = 5 * scaler;

	textRect[2].SetLocalPosX(+12.5f * scaler);
	textRect[2].SetLocalPosY(+12.5f * scaler);
	textRect[2].SetScale().x = 5 * scaler;
	textRect[2].SetScale().y = 25 * scaler;

	textRect[3].SetLocalPosX(0 * scaler);
	textRect[3].SetLocalPosY(0 * scaler);
	textRect[3].SetScale().x = 25 * scaler;
	textRect[3].SetScale().y = 5 * scaler;

	textRect[4].SetLocalPosX(-12.5f * scaler);
	textRect[4].SetLocalPosY(-12.5f * scaler);
	textRect[4].SetScale().x = 5 * scaler;
	textRect[4].SetScale().y = 25 * scaler;

	textRect[5].SetLocalPosX(0 * scaler);
	textRect[5].SetLocalPosY(-25.0f * scaler);
	textRect[5].SetScale().x = 25 * scaler;
	textRect[5].SetScale().y = 5 * scaler;

	textRect[6].SetLocalPosX(+12.5f * scaler);
	textRect[6].SetLocalPosY(-12.5f * scaler);
	textRect[6].SetScale().x = 5 * scaler;
	textRect[6].SetScale().y = 25 * scaler;

	for (size_t i = 0; i < TEXTRECT_LEN; i++)
	{
		textRect[i].SetScale().x *= GetScale().x;
		textRect[i].SetScale().y *= GetScale().y;
	}
}

void Text::SetColor(Color color)
{
	tColor = color;
	for (size_t i = 0; i < TEXTRECT_LEN; i++)
	{
		textRect[i].SetParentT(*this);
		textRect[i].color = tColor;
	}
}