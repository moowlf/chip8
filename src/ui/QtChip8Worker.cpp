
// Chip Library
#include "QtChip8Worker.hpp"
#include <Macros.hpp>

// Qt
#include <QPainter>
#include <QRect>
#include <QPaintEvent>
#include <QThread>

QtChip8Worker::QtChip8Worker(QWidget *parent) {

    chipDrawTriggerFn = [this]() {
        emit this->triggerVisualUpdate();
    };

    chip.setOnVisualUpdateFn(&chipDrawTriggerFn);
}

Screen const &QtChip8Worker::getScreen() {
    return chip.getScreen();
}

void QtChip8Worker::openFile(const std::string &filepath) {
    chip.insertROM(filepath);
    startTimer();
}

void QtChip8Worker::closeFile() {
}

void QtChip8Worker::setPressedKey(nsChip8::KeyPressed value) {
    chip.setPressedKeyValue(value);
}

void QtChip8Worker::startTimer() {
    while (true) {
        nextInstruction();
    }
}

void QtChip8Worker::nextInstruction() {
    auto value = chip.runNextInstruction();
    QThread::usleep(value);
}
