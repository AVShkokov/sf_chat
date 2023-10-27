#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QWidget>
#include <QString>
#include <QVector>

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

  void setUsers(const QVector<User>& users);

signals:
  void registrationRequested();
  void accepted(const User& user);
  void rejected();

private slots:
  void on_buttonBox_accepted();
  void on_buttonBox_rejected();
  void on_singUpPushButton_clicked();

private:
  Ui::LoginForm *ui;

  User m_user;
  QVector<User> m_users;
};

#endif // LOGINFORM_H
