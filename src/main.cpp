#include "PlaneFight.h"
#include <QtWidgets/QApplication>


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    // Font Setup
    int fontId = QFontDatabase::addApplicationFont("../src/resource/font/DTM-momo.otf");
    QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);
    Handler::font = fontFamilies.at(0);
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
