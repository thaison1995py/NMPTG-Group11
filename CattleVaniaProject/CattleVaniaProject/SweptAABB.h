#ifndef _SWEPTAABB_
#define _SWEPTAABB_
#include <d3d9.h>
#include <cmath>
#include <algorithm>
#include <limits>
// describes an axis-aligned rectangle with a velocity
struct Box
{
	Box(float _x, float _y, float _w, float _h, float _vx, float _vy)
	{
		x = _x;
		y = _y;
		w = _w;
		h = _h;
		vx = _vx;
		vy = _vy;
	}

	Box(float _x, float _y, float _w, float _h)
	{
		x = _x;
		y = _y;
		w = _w;
		h = _h;
		vx = 0.0f;
		vy = 0.0f;
	}

	// tọa độ x, y (left, top)
	float x, y;

	// kích thước
	float w, h;

	// vận tốc
	float vx, vy;
};

// trả về true nếu các box đang va chạm (vận tốc không được sử dụng)
static bool AABBCheck(Box b1, Box b2)
{
	return !(b1.x + b1.w < b2.x || b1.x > b2.x + b2.w || b1.y - b1.h > b2.y || b1.y < b2.y - b2.h);
}


// trả về true nếu các box đang va chạm 
// moveX và move Y trả về hướng di chuyển mà  box b1 phải đi để tránh va chạm

static bool AABB(Box b1, Box b2, float& moveX, float& moveY)
{
	moveX = moveY = 0.0f;

	float l = b2.x - (b1.x + b1.w);
	float r = (b2.x + b2.w) - b1.x;
	float t = b2.y - (b1.y - b1.h);
	float b = (b2.y - b2.h) - b1.y;

	// kiểm tra đã va chạm chưa
	if (l > 0 || r < 0 || t < 0 || b > 0)
		return false;

	// tìm phần giao nhau giữa 2 box 
	moveX = abs(l) < r ? l : r;
	moveY = abs(b) < t ? b : t;

	// sử dụng phần bù nào nhỏ nhất
	if (abs(moveX) < abs(moveY))
		moveY = 0.0f;
	else
		moveX = 0.0f;

	return true;
}

// trả về box bao lấy phần giao thoa của box hiện tại và box đích
static Box GetSweptBroadphaseBox(Box b, int dt)
{
	Box broadphasebox(0.0f, 0.0f, 0.0f, 0.0f);

	broadphasebox.x = b.vx > 0 ? b.x : b.x + b.vx * dt;
	broadphasebox.y = b.vy < 0 ? b.y : b.y + b.vy *dt;
	broadphasebox.w = b.vx > 0 ? b.vx * dt + b.w : b.w - b.vx * dt;
	broadphasebox.h = b.vy > 0 ? b.vy * dt + b.h : b.h - b.vy * dt;

	return broadphasebox;
}

// kiểm tra va chạm  với box b1 di chuyển và box b2 tĩnh
// trả về thời gian va chạm xảy ra (0 nếu băt đầu di chuyển, 1 nếu kết thúc di chuyển
// lấy vị trí mới bằng bằng box.x = box.x + box.vx * collisiontime
// normal x và normal y sẽ thể hiện phản ứng của đối tượng với va chạm
static float SweptAABB(Box b1, Box b2, float& normalx, float& normaly, int dt)
{
	float xInvEntry, yInvEntry;
	float xInvExit, yInvExit;

	// find the distance between the objects on the near and far sides for both x and y
	if (b1.vx > 0.0f)
	{
		xInvEntry = b2.x - (b1.x + b1.w);
		xInvExit = (b2.x + b2.w) - b1.x;
	}
	else
	{
		xInvEntry = (b2.x + b2.w) - b1.x;
		xInvExit = b2.x - (b1.x + b1.w);
	}

	if (b1.vy < 0.0f)
	{
		yInvEntry = b2.y - (b1.y - b1.h);
		yInvExit = (b2.y - b2.h) - b1.y;
	}
	else
	{
		yInvEntry = (b2.y - b2.h) - b1.y;
		yInvExit = b2.y - (b1.y - b1.h);
	}

	// find time of collision and time of leaving for each axis (if statement is to prevent divide by zero)
	float xEntry, yEntry;
	float xExit, yExit;

	if (b1.vx == 0.0f)
	{
		xEntry = -std::numeric_limits<float>::infinity();
		xExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		xEntry = xInvEntry / (b1.vx * dt);
		xExit = xInvExit / (b1.vx * dt);
	}

	if (b1.vy == 0.0f)
	{
		yEntry = -std::numeric_limits<float>::infinity();
		yExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		yEntry = yInvEntry / (b1.vy * dt);
		yExit = yInvExit / (b1.vy * dt);
	}

	// find the earliest/latest times of collision
	float entryTime = max(xEntry, yEntry);
	float exitTime = min(xExit, yExit);

	// if there was no collision
	if (entryTime > exitTime || xEntry < 0.0f && yEntry < 0.0f || xEntry > 1.0f || yEntry > 1.0f)
	{
		normalx = 0.0f;
		normaly = 0.0f;
		return 1.0f;
	}
	else // if there was a collision
	{
		// calculate normal of collided surface
		if (xEntry > yEntry)
		{
			if (xInvEntry < 0.0f)
			{
				normalx = 1.0f;
				normaly = 0.0f;
			}
			else
			{
				normalx = -1.0f;
				normaly = 0.0f;
			}
		}
		else
		{
			if (yInvEntry < 0.0f)
			{
				normalx = 0.0f;
				normaly = 1.0f;
			}
			else
			{
				normalx = 0.0f;
				normaly = -1.0f;
			}
		}

		// return the time of collision
		return entryTime;
	}
}


#endif