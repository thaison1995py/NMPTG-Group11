#include "DynamicObject.h"
#include <d3d9.h>

DynamicObject::DynamicObject(void) : GameObject()
{
}

DynamicObject::DynamicObject(float _posX, float _posY, float _vX, float _vY, EnumID id)
	: GameObject(_posX, _posY, id)
{
	//Di nguoc huong lai simon
	vX = _vX;
	vY = _vY;
	canMove = true;
	active = false;
	Initialize();
}

void DynamicObject::Update(int deltaTime)
{

}

void DynamicObject::Draw(CCamera* camera)
{
	if (sprite == NULL || !active)
		return;
	/*if (posX + width / 2 < camera->viewport.x || posX - width / 2 > camera->viewport.x + G_ScreenWidth)
	{
		active = false;
		return;
	}*/
	D3DXVECTOR2 center = camera->Transform(posX, posY);
	if (vX > 0)
		sprite->DrawFlipX(center.x, center.y);
	else
		sprite->Draw(center.x, center.y);
}

void DynamicObject::SetActive(float x, float y)
{	
	active = true;
}

DynamicObject::~DynamicObject(void)
{
}

void DynamicObject::Collision(list<GameObject*> obj, int dt)
{
	list<GameObject*>::iterator _itBegin;
	for (_itBegin = obj.begin(); _itBegin != obj.end(); _itBegin++)
	{
		float moveX;
		float moveY;
		float normalx;
		float normaly;
		GameObject* other = (*_itBegin);
		if (other->id == EnumID::Brick_ID)
		{
			Box box = this->GetBox();
			Box boxOther = other->GetBox();

			if (AABB(box, boxOther, moveX, moveY) == true)
			{
				if (vY < 0)
				{
					posY += moveY;
					vY = 0;
					return;
				}
				if ((posX - width / 2 + 10) - (other->posX - other->width / 2) <= 0
					|| (posX + width / 2 - 10) - (other->posX + other->width / 2) >= 0)
					vX = -vX;
			}
			else
				if (AABB(box, boxOther, moveX, moveY) == false)
				{
					if (other->canMove == true)
					{
						box.vx -= boxOther.vx;
						box.vy -= boxOther.vy;
						boxOther.vx = 0;
						boxOther.vy = 0;
					}
					Box broadphasebox = GetSweptBroadphaseBox(box, dt);
					if (AABBCheck(GetSweptBroadphaseBox(box, dt), boxOther) == true)
					{
						float collisiontime = SweptAABB(box, boxOther, normalx, normaly, dt);
						if (collisiontime > 0.0f && collisiontime < 1.0f)
						{
							ECollisionDirect colDirect = GetCollisionDirect(normalx, normaly);
							// perform response here
							switch (colDirect)
							{
							case Colls_Left:
								if (vX > 0)
									vX = -vX;
								break;
							case Colls_Right:
								if (vX < 0)
									vX = -vX;
								break;
							case Colls_Bot:
								posY += vY * collisiontime;
								vY = 0;
								break;
							}
						}
					}
				}
		}
	}
}

Box DynamicObject::GetBox()
{
	Box result(posX - width / 2, posY + height / 2, width, height, vX, 0);
	return result;
}

void DynamicObject::Initialize()
{
	bActiveHurt = false;
	_localHurtTime = 0;
}

bool DynamicObject::IsHurt()
{
	if (!bActiveHurt)
		return false;
	DWORD now = GetTickCount();
	DWORD deltaTime = now - _localHurtTime;
	if (deltaTime >= 300)
	{
		bActiveHurt = false;
	}
	return true;
}

void DynamicObject::ReceiveDamage(int damagePoint)
{
	if (!IsHurt())
	{
		if (hp <= 0)
			return;
		hp -= damagePoint;
		if (hp == 0)
			death = true;
		bActiveHurt = true;
		_localHurtTime = GetTickCount();
	}
}