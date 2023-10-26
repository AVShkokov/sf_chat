#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include <QDialog>
#include <QString>
#include <QVector>

#include "database.h"
#include "user.h"

#include <memory>

namespace Ui {
  class StartScreen;
}

class StartScreen : public QDialog
{
  Q_OBJECT

public:
  explicit StartScreen(QWidget *parent = nullptr);
  ~StartScreen();

  void setLoginForm();
  void setRegistrationForm();

public slots:
  void onLoggedIn();
  void onRejectRequested();

private:
  void getDB();
  void getUsers();

  Ui::StartScreen *ui;

  std::shared_ptr<DataBase> m_database = std::make_shared<DataBase>();

  QVector<User> m_users;
};

#endif // STARTSCREEN_H
