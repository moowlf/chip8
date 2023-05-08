#ifndef QTCHIP8_HPP
#define QTCHIP8_HPP

// Chip8
#include <Chip8.hpp>

// Qt
#include <QWidget>
#include <QObject>
#include <QThread>
#include <QTimer>

class QtChip8Worker : public QObject
{
  Q_OBJECT
  Chip8 chip;
  nsChip8::onVisualUpdateFn chipDrawTriggerFn;

public:
  explicit QtChip8Worker(QWidget *parent = nullptr);
  ~QtChip8Worker() override = default;

  Screen const &getScreen();

public slots:
  void openFile(const std::string &filepath);
  void closeFile();
  void startTimer();
  void setPressedKey(nsChip8::KeyPressed);

signals:
  void triggerVisualUpdate();

private:
  void nextInstruction();
};

#endif
