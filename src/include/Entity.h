#pragma once

#include "Object.h"
#include "Attribute.h"

class Entity : public Object {
protected:
	Entity *lastHurt = nullptr;
	AttributeMap attributeMap = AttributeMap();
	double hit_time = 0;
	double durability;
public:
	int score = 0;

	Entity();
	Entity(QString id, QString location, double size);

	~Entity();

	AttributeMap getAttributes() const;

	void setDurability(double dura) ;

	double getDurability() const;

	double getMaxDurability() const;

	void tick() override;

	virtual void behaviorTick() = 0;

	virtual bool damage(double amount, Entity* attacker);
	virtual bool damage(double amount, Object* bullet, Entity* attacker);

	
	void draw(QPainter &painter) const;
};