#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QWidget>
#include <QString>
#include <QVector>

#include "database.h"
#include "user.h"

#include <memory>

namespace Ui {
  class LoginForm;
}

class LoginForm : public QWidget
{
  Q_OBJECT

public:
  explicit LoginForm(QWidget *parent = nullptr);
  ~LoginForm();

  void setDatabase(std::shared_ptr<DataBase> database);
  void setUsers(const QVector<User>& users);

signals:
  void registrationRequested();
  void accepted();
  void rejected();

private slots:
  void on_buttonBox_accepted();
  void on_buttonBox_rejected();
  void on_singUpPushButton_clicked();

private:
  Ui::LoginForm *ui;

  std::shared_ptr<DataBase> m_database;

  User m_user;
  QVector<User> m_users;
};

#endif // LOGINFORM_H
