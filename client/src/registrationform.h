#ifndef REGISTRATIONFORM_H
#define REGISTRATIONFORM_H

#include <QWidget>
#include <QString>
#include <QVector>

#include "database.h"
#include "user.h"

#include <memory>

namespace Ui {
  class RegistrationForm;
}

class RegistrationForm : public QWidget
{
  Q_OBJECT

public:
  explicit RegistrationForm(QWidget *parent = nullptr);
  ~RegistrationForm();

  void setDatabase(std::shared_ptr<DataBase> database);
  void setUsers(const QVector<User>& users);

signals:
  void loginRequested();
  void accepted(const User& user);
  void rejected();

private slots:
  void on_buttonBox_accepted();
  void on_buttonBox_rejected();
  void on_singInPushButton_clicked();

private:
  void showErrorMessage(const QString& message);

  Ui::RegistrationForm *ui;

  std::shared_ptr<DataBase> m_database;

  User m_user;
  QVector<User> m_users;
};

#endif // REGISTRATIONFORM_H
