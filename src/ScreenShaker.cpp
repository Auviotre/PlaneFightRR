#include "ScreenShaker.h"

ScreenShaker::ScreenShaker() {}

QVector2D ScreenShaker::shake;
QVector2D ScreenShaker::shakeRange;
double ScreenShaker::shakeTimer = 0;
double ScreenShaker::modifier = 1;

void ScreenShaker::set(double r) {
	double angle = rand() % 360 * M_PI / 180;
	double x = r * sin(angle);
	double y = r * cos(angle);
	shakeRange = QVector2D(x, y);
}

void ScreenShaker::add(double r) {
	double angle = rand() % 360 * M_PI / 180;
	double x = r * sin(angle);
	double y = r * cos(angle);
	shakeRange += QVector2D(x, y);
}

void ScreenShaker::tick() {
	if (abs(modifier - 1) < 0.02) modifier = 1;
	else modifier = modifier + (1 - modifier) * 12 * GAME_CLOCK;
	if (shakeRange.length() < 0.01) {
		shakeRange = QVector2D(0, 0);
		shakeTimer = 0;
	} else {
		shakeTimer += GAME_CLOCK;
		double multi = pow(0.0001, GAME_CLOCK);
		shakeRange.setX(shakeRange.x() * multi);
		shakeRange.setY(shakeRange.y() * multi);
		shake.setX(shakeRange.x() * cos(shakeTimer * 3600));
		shake.setY(shakeRange.y() * sin(shakeTimer * 4800));
	}
}