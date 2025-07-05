#include "Handler.h"

QMap<int, bool> Handler::keyPressingSet;
QMap<int, bool> Handler::keyPressSet;

QString Handler::font = "";
int Handler::Difficulty = 1;
int Handler::ParAmount = 2;
bool Handler::CoMode = false;

Handler::Handler() {}