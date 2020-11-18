#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class NPC {
private:
	float x, y;
	float speed;
	Color c;
	RectangleShape rectShape;
	float offset_x;
public:
	bool destroyed = false;
	NPC(float _x, float _y, float _speed, Color _c);
	void update();
	void draw(RenderWindow& _window);
	FloatRect getArea();
};