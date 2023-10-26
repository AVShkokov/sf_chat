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

  void setLoginForm() const;
  void setRegistrationForm() const;

  std::shared_ptr<DataBase> GetDB();
  User GetUser() const;

public slots:
  void onLoggedIn(const User& user);
  void onRejectRequested();

private:
  void connectDB();
  void getUsers();

  Ui::StartScreen *ui;

  std::shared_ptr<DataBase> m_database = std::make_shared<DataBase>();

  User m_user;
  QVector<User> m_users;
};

#endif // STARTSCREEN_H
