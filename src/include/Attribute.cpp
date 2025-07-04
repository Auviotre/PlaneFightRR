#include "Attribute.h"

AttributeMap::AttributeMap() {
	for (int i = 0; i < 3; i++) map.insert(Attribute(i), 0.0);
}

AttributeMap::~AttributeMap() {}

double AttributeMap::getValue(Attribute attribute) const {
	return map.value(attribute);
}

bool AttributeMap::setValue(Attribute attribute, double value) {
	if (map.contains(attribute)) {
		map.insert(attribute, value);
		return true;
	}
	return false;
}