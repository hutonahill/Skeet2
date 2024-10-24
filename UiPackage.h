#pragma once

class UiPackage {
public:
	bool Space;
	bool M;
	bool B;
	int Up;
	int Down;
	int Right;
	int Left;
	bool Shift;

	UiPackage(bool space, bool m, bool b, int up, int down, int right, int left, bool shift) {
		Space = space;
		M = m;
		B = b;
		Up = up;
		Down = down;
		Right = right;
		Left = left;
		Shift = shift;
	}
};
