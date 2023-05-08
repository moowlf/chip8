#include "QtGui.hpp"

// Qt
#include <QMenu>
#include <QFileDialog>

#include "./ui_QtGui.h"

QtGui::QtGui(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::QtGui), img(64, 32, QImage::Format::Format_Mono) {

    ui->setupUi(this);

    // Pass chip8 to a new thread
    chip8.moveToThread(&chip8Thread);
    chip8Thread.start();

    img.fill(0);
    ui->label->setPixmap(QPixmap::fromImage(img).scaled(512, 256, Qt::KeepAspectRatio));

    connectMenu();
    connectSignals();
}

void QtGui::connectMenu() {

    auto actionOpenROM = findChild<QAction *>(tr("actionOpen_ROM"));
    actionOpenROM->setShortcut(QKeySequence::Open);
    connect(actionOpenROM, &QAction::triggered, this, &QtGui::openFileSlot);

    auto actionCloseROM = findChild<QAction *>(tr("actionClose_ROM"));
    actionCloseROM->setShortcut(QKeySequence::Close);
    connect(actionOpenROM, &QAction::triggered, this, &QtGui::closeFileSlot);
}

void QtGui::connectSignals() {

    connect(this, &QtGui::openFileSignal, &chip8, &QtChip8Worker::openFile);
    connect(this, &QtGui::closeFileSignal, &chip8, &QtChip8Worker::closeFile);
    connect(this, &QtGui::startTimerSignal, &chip8, &QtChip8Worker::startTimer);
    connect(&chip8, &QtChip8Worker::triggerVisualUpdate, this, &QtGui::updateScreen);

    connect(ui->push0, &QPushButton::clicked, this, &QtGui::buttonPressHandler);
    connect(ui->push1, &QPushButton::clicked, this, &QtGui::buttonPressHandler);
    connect(ui->push2, &QPushButton::clicked, this, &QtGui::buttonPressHandler);
    connect(ui->push3, &QPushButton::clicked, this, &QtGui::buttonPressHandler);
    connect(ui->push4, &QPushButton::clicked, this, &QtGui::buttonPressHandler);
    connect(ui->push5, &QPushButton::clicked, this, &QtGui::buttonPressHandler);
    connect(ui->push6, &QPushButton::clicked, this, &QtGui::buttonPressHandler);
    connect(ui->push7, &QPushButton::clicked, this, &QtGui::buttonPressHandler);
    connect(ui->push8, &QPushButton::clicked, this, &QtGui::buttonPressHandler);
    connect(ui->push9, &QPushButton::clicked, this, &QtGui::buttonPressHandler);
    connect(ui->pushA, &QPushButton::clicked, this, &QtGui::buttonPressHandler);
    connect(ui->pushB, &QPushButton::clicked, this, &QtGui::buttonPressHandler);
    connect(ui->pushC, &QPushButton::clicked, this, &QtGui::buttonPressHandler);
    connect(ui->pushD, &QPushButton::clicked, this, &QtGui::buttonPressHandler);
    connect(ui->pushE, &QPushButton::clicked, this, &QtGui::buttonPressHandler);
    connect(ui->pushF, &QPushButton::clicked, this, &QtGui::buttonPressHandler);
}

void QtGui::openFileSlot() {

    QFileDialog dialog(this, tr("Select a disk image"));
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setViewMode(QFileDialog::Detail);

    if (dialog.exec()) {
        auto fileLocation = (dialog.selectedFiles())[0];

        if (!fileLocation.isNull()) {
            emit openFileSignal(fileLocation.toStdString());
        }
    }
}

void QtGui::closeFileSlot() {
    emit closeFileSignal();
}

void QtGui::buttonPressHandler() {
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    auto clicked_text = button->text().toStdString();

    if (clicked_text == "0") {
        chip8.setPressedKey(nsChip8::KeyPressed::Zero);
    } else if (clicked_text == "1") {
        chip8.setPressedKey(nsChip8::KeyPressed::One);
    } else if (clicked_text == "2") {
        chip8.setPressedKey(nsChip8::KeyPressed::Two);
    } else if (clicked_text == "3") {
        chip8.setPressedKey(nsChip8::KeyPressed::Three);
    } else if (clicked_text == "4") {
        chip8.setPressedKey(nsChip8::KeyPressed::Four);
    } else if (clicked_text == "5") {
        chip8.setPressedKey(nsChip8::KeyPressed::Five);
    } else if (clicked_text == "6") {
        chip8.setPressedKey(nsChip8::KeyPressed::Six);
    } else if (clicked_text == "7") {
        chip8.setPressedKey(nsChip8::KeyPressed::Seven);
    } else if (clicked_text == "8") {
        chip8.setPressedKey(nsChip8::KeyPressed::Eight);
    } else if (clicked_text == "9") {
        chip8.setPressedKey(nsChip8::KeyPressed::Nine);
    } else if (clicked_text == "A") {
        chip8.setPressedKey(nsChip8::KeyPressed::A);
    } else if (clicked_text == "B") {
        chip8.setPressedKey(nsChip8::KeyPressed::B);
    } else if (clicked_text == "C") {
        chip8.setPressedKey(nsChip8::KeyPressed::C);
    } else if (clicked_text == "D") {
        chip8.setPressedKey(nsChip8::KeyPressed::D);
    } else if (clicked_text == "E") {
        chip8.setPressedKey(nsChip8::KeyPressed::E);
    } else if (clicked_text == "F") {
        chip8.setPressedKey(nsChip8::KeyPressed::F);
    }
}

void QtGui::updateScreen() {
    auto &screen = chip8.getScreen();

    for (auto i = 0; i < screen.getHeight(); i++) {
        for (auto j = 0; j < screen.getWidth(); j++) {
            auto currentIndexPosition = i * screen.getWidth() + j;
            img.setPixel(j, i, screen.getScreen().at(currentIndexPosition));
        }
    }
    ui->label->setPixmap(QPixmap::fromImage(img).scaled(512, 256, Qt::KeepAspectRatio));
}

QtGui::~QtGui() {
    delete ui;
}
