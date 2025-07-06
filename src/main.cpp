#include "PlaneFight.h"
#include <QtWidgets/QApplication>


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    // Font Setup
    int fontId = QFontDatabase::addApplicationFont("../src/resource/font/DTM-momo.otf");
    QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);
    Handler::font1 = fontFamilies.at(0);
    fontId = QFontDatabase::addApplicationFont("../src/resource/font/FusionPixel-10.otf");
    fontFamilies = QFontDatabase::applicationFontFamilies(fontId);
    Handler::font2 = fontFamilies.at(0);
    // Interface Init
    new ParticleEngine;
    new ScreenShaker;
    new Handler;
    // Main Window Build
    MainWindow window;
    window.playGame();
    window.show();
    return app.exec();
}
