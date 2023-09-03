#include "stdafx.h"
#include "NeutralObj.h"

void NeutralObj::Update()
{
	if (isVisible)
	{
		MoveWorldPos(dir * speed * DELTA);
	}
}
