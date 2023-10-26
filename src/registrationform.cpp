#include "registrationform.h"
#include "ui_registrationform.h"

#include "sha1.h"

#include <QMessageBox>

RegistrationForm::RegistrationForm(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::RegistrationForm)
{
  ui->setupUi(this);
}

RegistrationForm::~RegistrationForm()
{
  delete ui;
}

void RegistrationForm::setDatabase(std::shared_ptr<DataBase> database)
{
  m_database = database;
}

void RegistrationForm::setUsers(const QVector<User>& users)
{
  m_users = users;
}

void RegistrationForm::on_buttonBox_accepted()
{
  QString password = ui->passwordLineEdit->text();

  if(password != ui->passwordConfirmLineEdit->text())
    {
      showErrorMessage(tr("Passwords not match!"));
      return;
    }

  QString message;

  QString name = ui->nameLineEdit->text();
  if(!m_user.CheckName(m_users, name, message)) {
      showErrorMessage(message);
      return;
    }
  else {
      m_user.SetName(name);
    }

  QString login = ui->loginLineEdit->text();
  if(!m_user.CheckLogin(m_users, login, message)) {
      showErrorMessage(message);
      return;
    }
  else {
      m_user.SetLogin(login);
    }

  if(!m_user.CheckPassword(password, message)) {
      showErrorMessage(message);
      return;
    }
  else {
      Hash passwordHash = sha1(password.toStdString());
      m_user.SetPassword(passwordHash);
    }

  m_database->QueryToDB("INSERT into users (name, login, password) VALUES ('" + name + "', '" + login + "', '" + password + "');");
  m_users.push_back(m_user);

  emit accepted();
}

void RegistrationForm::on_buttonBox_rejected()
{
  emit rejected();
}

void RegistrationForm::on_singInPushButton_clicked()
{
  emit loginRequested();
}

void RegistrationForm::showErrorMessage(const QString& message) {
  QMessageBox::critical(this,
                        tr("Error"),
                        tr(message.toStdString().c_str()));
}
