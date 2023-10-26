#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <memory>

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

  static MainWindow* createClient();

private slots:
  void on_messageLineEdit_returnPressed();
  void on_sendPushButton_clicked();

private:
  Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
