#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
using namespace sf;
using namespace std;

/*
	Color class
	CircleShape::setPosition(float x, float y)
	RectangleShape, Vector2f
	Event.type, KeyPressed
	Keyboard, isKeyPressed

	CircleShape::move(float offset_x, float offset_y)
*/

int main() {
	RenderWindow window(VideoMode(640, 480), "Hello SFML"); //윈도우 열고
	//window.setFramerateLimit(60);
	CircleShape shape(50.0f, 30); // 반지름100, pointCount10인 원생성
	shape.setFillColor(Color::Green); //색을 채움
	shape.setPosition(320.0f-50, 240.0f-50);

	vector<RectangleShape> npcs(2);
	int inc = 20;
	for (auto& _e : npcs) {
		_e.setSize(Vector2f(30.0f, 10.0f));
		_e.setFillColor(Color::Cyan);
		_e.setPosition(30.0f+inc, 30.0f+inc);
		inc += 20;
	}
	/*RectangleShape myRect(Vector2f(30.0f, 100.0f));
	myRect.setFillColor(Color::Cyan);
	myRect.setPosition(30.0f, 100.0f);
	*/

	/*	 NPC 움직이기
		 사각형을 움직여 보자
		 사각형의 움직이는 속도를 조절해보자
		 여러 개의 사각형을 관리해보자
			- vector
	*/

	float offset_x = 0;
	while (window.isOpen()) {//윈도우가 켜져있는 한

		//이벤트가 발생하면, 실행
		Event event;
		while (window.pollEvent(event)) { 
			switch (event.type) {

			case Event::Closed: //창닫으라는 이벤트면 창을 닫음.
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

		for (auto& _e : npcs) {
			Vector2f pos = _e.getPosition();
			if (pos.x > 600.0f) {
				offset_x = -2.0f;
			}
			else if (pos.x <= 30.0f) {
				offset_x = 2.0f;
			}
			_e.move(offset_x, 0.0f);
		}
		window.clear();
		for (auto& _e : npcs) {
			window.draw(_e);
		}
		window.draw(shape); //원을 그림
		//window.draw(myRect); //rect를 그림

		window.display();	//보여줌
	}
	return 0;
}