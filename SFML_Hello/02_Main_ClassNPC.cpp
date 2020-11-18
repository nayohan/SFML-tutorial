#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
using namespace sf;
using namespace std;

// NPC클래스 만들기를 해봅시다.
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
NPC::NPC(float _x, float _y, float _speed, Color _c) : x(_x), y(_y), speed(_speed), c(_c), offset_x(_speed){
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

// NPC_SET클래스를 만들어 NPC들을 관리해봅시다.
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
		NPC npc(30.0f + inc, 30.f + inc, (i + 1) * 2, colors[i%3]);
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
	window.setFramerateLimit(60);
	CircleShape shape(50.0f, 30);
	shape.setFillColor(Color::Green);
	shape.setPosition(320.0f - 50, 480.0f - 50);

	//NPC생성
	NPC_SET npcs(5);

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
					shape.move(-10.0f, 0);
				}
				else if (Keyboard::isKeyPressed(Keyboard::Right) == true) {
					shape.move(+10.0f, 0);
				}
			default:
				break;
			}
		}
		
		//NPC 업데이트 및 그리기
		npcs.update();

		window.clear();
		window.draw(shape);
		npcs.draw(window);
		window.display();
	}
	return 0;
}