#pragma once

#include "Object.h"
#include "Attribute.h"

class Entity : public Object {
protected:
	AttributeMap attributeMap = AttributeMap();
	double durability;
public:
	Entity();
	Entity(QString id, QString location, double size);

	~Entity();

	void setDurability(double dura) ;

	double getDurability() const;

	double getMaxDurability() const;

	void tick() override;

	virtual void behaviorTick() = 0;

	virtual bool damage(double amount, Entity* attacker);
	virtual bool damage(double amount, Object* bullet, Entity* attacker);
};