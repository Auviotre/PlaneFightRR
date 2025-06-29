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
Particle::Particle(double s, double time) : size(s), lifetime(time) {
	timer = lifetime;
	hasFade = false;
}
Particle::~Particle() {}

QColor Particle::getCurrentColor() const {
	float modifier = timer / lifetime;
	if (!hasFade) return QColor(baseColor.red(), baseColor.green(), baseColor.blue(), modifier * baseColor.alpha());
	float r = modifier * baseColor.red() + (1 - modifier) * fadeColor.red();
	float g = modifier * baseColor.green() + (1 - modifier) * fadeColor.green();
	float b = modifier * baseColor.blue() + (1 - modifier) * fadeColor.blue();
	float alpha = modifier * baseColor.alpha();
	return QColor((int) r, (int) g, (int) b, (int) alpha);
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
	size -= GAME_CLOCK;
	if (size <= 0 || timer <= 0) discard = true;
	pos += move * GAME_CLOCK;
}
void Particle::draw(QPainter &painter) const {
    painter.setPen(QPen(getCurrentColor()));
    painter.setBrush(QBrush(getCurrentColor()));
	QVector2D newPos = pos - QVector2D(size, size);
	painter.drawEllipse(newPos.x(), newPos.y(), size * 2, size * 2);
}