#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "testapp.h"

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow, public testApp
{
    Q_OBJECT

  public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

  private slots:

  private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
