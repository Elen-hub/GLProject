#pragma once

struct fVector3 {
public:
	fVector3() { x = 0, y = 0, z = 0; }
	fVector3(float X, float Y, float Z = 0) { x = X; y = Y; z = Z; }
	float x;
	float y;
	float z;
	inline void Set(float X, float Y, float Z = 0) {x = X, y = Y, z = Z; }
	fVector3 operator+(fVector3 vec)
	{
		return fVector3(x + vec.x, y + vec.y, z + vec.z);
	}
	fVector3 operator-(fVector3 vec)
	{
		return fVector3(x - vec.x, y - vec.y, z - vec.z);
	}
};