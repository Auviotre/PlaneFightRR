#include "Handler.h"
#include <fstream>

QMap<int, bool> Handler::keyPressingSet;
QMap<int, bool> Handler::keyPressSet;

QString Handler::font1 = "";
QString Handler::font2 = "";
int Handler::Difficulty = 1;
int Handler::ParAmount = 2;
bool Handler::CoMode = false;
int Handler::scoreRecord = 0;

#define RECORD_PATH "../src/data/record.ini"
#define SETTINGS_PATH "../src/data/settings.ini"

Handler::Handler() {
    // 载入设置
    std::ifstream settingsFile(SETTINGS_PATH);
    if (settingsFile.is_open()) {
        std::string line;
        while (getline(settingsFile, line)) {
            if (line.find("Difficulty") != std::string::npos) {
                Difficulty = std::stoi(line.substr(line.find('=') + 1));
            } else if (line.find("ParAmount") != std::string::npos) {
                ParAmount = std::stoi(line.substr(line.find('=') + 1));
            } else if (line.find("CoMode") != std::string::npos) {
                CoMode = std::stoi(line.substr(line.find('=') + 1));
            }
        }
        settingsFile.close();
    }
}

void Handler::updateScoreRecord() {
    int currentRecord = 0;
    // 先读
    std::ifstream recordFileRead(RECORD_PATH);
    if (recordFileRead.is_open()) {
        std::string cRec;
        if (getline(recordFileRead, cRec)) {
            try {
                currentRecord = std::stoi(cRec);
            } catch (...) {
                currentRecord = 0;
            }
        }
        recordFileRead.close();
    }

    // 判断是否需要写
    if (scoreRecord > currentRecord) {
        std::ofstream recordFileWrite(RECORD_PATH);
        if (recordFileWrite.is_open()) {
            recordFileWrite << scoreRecord;
            recordFileWrite.close();
        }
    }
}

void Handler::flushRecord() {
    std::ofstream recordFile(RECORD_PATH);
    if (recordFile.is_open()) {
        recordFile << "0"; // 重置记录为0
        recordFile.close();
    }
}

void Handler::updateSettings() {
    // 保存难度，粒子和玩家人数
    std::ofstream settingsFile(SETTINGS_PATH);
    if (settingsFile.is_open()) {
        settingsFile << "Difficulty = " << Difficulty << std::endl;
        settingsFile << "ParAmount = " << ParAmount << std::endl;
        settingsFile << "CoMode = " << (CoMode ? "1" : "0") << std::endl;
        settingsFile.close();
    }
}