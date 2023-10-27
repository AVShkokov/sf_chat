#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QVector>

#include "user.h"
#include "message.h"
#include "database.h"
#include "logger.h"

#include <memory>

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(const User& user, std::shared_ptr<DataBase> database, QWidget *parent = nullptr);
  ~MainWindow();

  static MainWindow* createClient();

private slots:
  void on_messageLineEdit_returnPressed();
  void on_sendPushButton_clicked();
  void on_actionClose_triggered();
  void on_actionCommands_triggered();

private:
  void getStatus();

  void getMessages();
  void loadHistory();
  bool privateMessage(QString& text, QString& to);

  void showErrorMessage(const QString& message);
  void showInformationMessage(const QString& message);

  Ui::MainWindow *ui;

  User m_user;

  QVector<Message> m_messages;

  std::shared_ptr<DataBase> m_database;

  const QString m_log_file_name = "log.txt";
  Logger* m_log = new Logger(m_log_file_name.toStdString());
};

#endif // MAINWINDOW_H
