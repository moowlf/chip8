#ifndef CHIP8_SRC_UI_QTGUI_HPP
#define CHIP8_SRC_UI_QTGUI_HPP

#include "QtChip8Worker.hpp"

// Qt
#include <QMainWindow>
#include <QMenuBar>
#include <QThread>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui
{
  class QtGui;
}
QT_END_NAMESPACE

class QtGui : public QMainWindow
{
  Q_OBJECT

  // UI
  Ui::QtGui *ui;

  // Our VM
  QThread chip8Thread;
  QtChip8Worker chip8;

  // Screen
  QImage img;

public:
  explicit QtGui(QWidget *parent = nullptr);
  ~QtGui() override;

private slots:

  void openFileSlot();
  void closeFileSlot();
  void updateScreen();
  void buttonPressHandler();

signals:

  void openFileSignal(const std::string &filepath);
  void closeFileSignal();
  void startTimerSignal();

private:
  void connectMenu();
  void connectSignals();
};

#endif // CHIP8_SRC_UI_QTGUI_HPP
