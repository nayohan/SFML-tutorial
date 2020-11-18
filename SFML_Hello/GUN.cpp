#include "GUN.h"

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
	if (showBullet == false) { //�Ѿ��� ���� ���� �����϶��� �߻�
		Vector2f pos = gun.getPosition();
		bullet.setPosition(pos.x + 50.0f, pos.y);
		showBullet = true;
	}
}
void GUN::update(NPC_SET& npcs) {
	if (showBullet == true) {
		bullet.move(0.0f, -8.0f);
		if (bullet.getPosition().y < 0.0f) {
			showBullet = false;
		}
		else {
			// bullet�� FloatRectf�� ���ؼ�, NPC_SET ��ü�� checkHit()�� ȣ���Ѵ�.
			npcs.checkHit(bullet.getGlobalBounds());
		}
	}
}
void GUN::draw(RenderWindow& _window) {
	_window.draw(gun);
	if (showBullet == true) {
		_window.draw(bullet);
	}
}