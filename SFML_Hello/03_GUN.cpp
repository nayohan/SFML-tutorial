#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
using namespace sf;
using namespace std;

/* 총알을 쏴봅시다. */
class GUN {
private:
	CircleShape gun;
	CircleShape bullet;
	bool showBullet;
public:
	GUN();
	void moveLeft();
	void moveRight();
	void fireBullet();
	void update();
	void draw(RenderWindow& _window);
};
GUN::GUN() {
	gun = CircleShape(50.0f, 30);
	gun.setFillColor(Color::Green);
	gun.setPosition(320.0f - 50, 480.0f - 50);

	showBullet = false;
	bullet = CircleShape(5.0f);
	bullet.setFillColor(Color::Red);
}
void GUN::moveLeft() {
	gun.move(-10.0f, 0.0);
}
void GUN::moveRight() {
	gun.move(10.0f, 0.0);
}
void GUN::fireBullet() {
	if (showBullet == false) { //총알을 쏘지 않은 상태일때만 발사
		Vector2f pos = gun.getPosition();
		bullet.setPosition(pos.x + 50.0f, pos.y);
		showBullet = true;
	}
}
void GUN::update() {
	if (showBullet == true) {
		bullet.move(0.0f, -8.0f);
		if (bullet.getPosition().y < 0.0f) {
			showBullet = false;
		}
	}
}
void GUN::draw(RenderWindow& _window) {
	_window.draw(gun);
	if (showBullet == true) {
		_window.draw(bullet);
	}
}


class NPC {
private:
	float x, y;
	float speed;
	Color c;
	RectangleShape rectShape;
	float offset_x;
public:
	NPC(float _x, float _y, float _speed, Color _c);
	void update();
	void draw(RenderWindow& _window);
};
NPC::NPC(float _x, float _y, float _speed, Color _c) : x(_x), y(_y), speed(_speed), c(_c), offset_x(_speed) {
	rectShape = RectangleShape(Vector2f(30.0f, 10.0f));
	rectShape.setFillColor(_c);
	rectShape.setPosition(_x, _y);
}
void NPC::draw(RenderWindow& _window) {
	_window.draw(rectShape);
}
void NPC::update() {
	Vector2f pos = rectShape.getPosition();
	if (pos.x > 600.0f) {
		offset_x = -speed;
	}
	else if (pos.x < 30.0f) {
		offset_x = speed;
	}
	rectShape.move(offset_x, 0.0f);
}


class NPC_SET {
private:
	vector<NPC> npcs;
public:
	NPC_SET(int num);
	void update();
	void draw(RenderWindow& _window);
};
NPC_SET::NPC_SET(int num) {
	int inc = 0;
	Color colors[3] = { Color::Red, Color::Cyan, Color::Magenta };
	for (int i = 0; i < num; i++) {
		NPC npc(30.0f + inc, 30.f + inc, (i + 1) * 2, colors[i % 3]);
		npcs.push_back(npc);
		inc += 20;
	}
}
void NPC_SET::update() {
	for (auto& _e : npcs) {
		_e.update();
	}
}
void NPC_SET::draw(RenderWindow& _window) {
	for (auto& _e : npcs) {
		_e.draw(_window);
	}
}


int main() {
	//윈도우 생성
	RenderWindow window(VideoMode(640, 480), "Hello SFML");
	window.setFramerateLimit(30);

	NPC_SET npcs(5);
	GUN gun;

	//이벤트 처리
	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {

			case Event::Closed:
				window.close();
				break;
			case Event::KeyPressed:
				if (Keyboard::isKeyPressed(Keyboard::Left) == true) {
					gun.moveLeft();
				}
				else if (Keyboard::isKeyPressed(Keyboard::Right) == true) {
					gun.moveRight();
				}
				else if (Keyboard::isKeyPressed(Keyboard::Space) == true) {
					gun.fireBullet();
				}
			default:
				break;
			}
		}

		//업데이트
		gun.update();
		npcs.update();

		//draw
		window.clear();
		npcs.draw(window);
		gun.draw(window);
		window.display();
	}
	return 0;
}