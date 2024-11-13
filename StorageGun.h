#pragma once

class Position;

class StorageGun
{
public:
	StorageGun(Position* pt) : angle(0.78 /* 45 degrees */), pt(pt) {}  // 45 degrees initially
	void addAngle(int num);
	double getAngle() const { return angle; }
	Position* getPosition() const { return pt; }

private:
	double angle;
	Position* pt;
};
