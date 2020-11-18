#include <SFML/Graphics.hpp>
#include "NPC.h"
#include "NPC_SET.h"
#include "GUN.h"

int main() {
	//������ ����
	RenderWindow window(VideoMode(640, 480), "Hello SFML");
	window.setFramerateLimit(30);

	NPC_SET npcs(5);
	GUN gun;

	//�̺�Ʈ ó��
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

		//������Ʈ
		gun.update(npcs);
		npcs.update();

		//draw
		window.clear();
		npcs.draw(window);
		gun.draw(window);
		window.display();
	}
	return 0;
}