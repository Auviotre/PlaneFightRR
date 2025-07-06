#include "ParticleEngine.h"

QVector<Particle*> ParticleEngine::particles;

ParticleEngine::ParticleEngine() {}
ParticleEngine::~ParticleEngine() {}

void ParticleEngine::add(Particle* particle) {
	if (particles.count() > 400 && rand() % 3 == 0) return; 
    particles.append(particle);
}

void ParticleEngine::tick() {
	// Update
	for (Particle* particle : particles) {
		particle->tick();
	}
	// Clear
    QList<Particle *> list = particles.toList();
    for (Particle *particle : list) if (particle->discard) {
        particles.removeAll(particle);
        delete particle;
    }
}

void ParticleEngine::draw(QPainter &painter) {
	for (Particle* particle : particles) {
		particle->draw(painter);
	}
}

QVector2D ParticleEngine::randOffset(double range) {
	double angle = rand() % 360 * M_PI / 180;
	double x = range * sin(angle);
	double y = range * cos(angle);
	return QVector2D(x+1, y);
}

// Particle
Particle::Particle(double s, double time) : size(s) {
	lifetime = time * 0.5 * Handler::ParAmount;
	timer = lifetime;
	hasFade = false;
}
Particle::~Particle() {}

QColor Particle::getCurrentColor() const {
	float modifier = timer / lifetime;
	if (!hasFade) return baseColor;
	float r = modifier * baseColor.red() + (1 - modifier) * fadeColor.red();
	float g = modifier * baseColor.green() + (1 - modifier) * fadeColor.green();
	float b = modifier * baseColor.blue() + (1 - modifier) * fadeColor.blue();
	float alpha = modifier * baseColor.alpha();
	return QColor((int) r, (int) g, (int) b, (int) alpha);
}
double Particle::getSize() const {
	return timer / lifetime * size;
}

void Particle::setColor(QColor color) {
	baseColor = color;
	fadeColor = color;
}
void Particle::setFadeColor(QColor color) {
	fadeColor = color;
	hasFade = true;
}
void Particle::setPos(QVector2D p) {
	pos = p;
}
void Particle::setMove(QVector2D m) {
	move = m;
}
void Particle::tick() {
	timer -= GAME_CLOCK;
	if (timer <= 0) discard = true;
	pos += move * GAME_CLOCK;
}
void Particle::draw(QPainter &painter) const {
    painter.setPen(QPen(getCurrentColor()));
    painter.setBrush(QBrush(getCurrentColor()));
	double s = getSize();
	QVector2D newPos = pos - QVector2D(s, s);
	painter.drawEllipse(newPos.x(), newPos.y(), s * 2, s * 2);
}