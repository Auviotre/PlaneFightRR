#pragma once

#include <QMap>

enum Attribute {MAX_DURABILITY, POWER, DEFENCE};

class AttributeMap {
	QMap<Attribute, double> map;
public:
	AttributeMap();
	~AttributeMap();

	double getValue(Attribute attribute) const;

	bool setValue(Attribute attribute, double value);
};