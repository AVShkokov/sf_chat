#include "loginform.h"
#include "ui_loginform.h"

#include <QMessageBox>

LoginForm::LoginForm(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::LoginForm)
{
  ui->setupUi(this);
}

LoginForm::~LoginForm()
{
  delete ui;
}

void LoginForm::setUsers(const QVector<User>& users)
{
  m_users = users;
}

void LoginForm::on_buttonBox_accepted()
{
  QString message;

  QString login = ui->loginLineEdit->text();
  QString password = ui->passwordLineEdit->text();

  if (!m_user.CheckSingIn(m_users, login, password, message))
    {
      QMessageBox::critical(this,
                            tr("Error"),
                            tr(message.toStdString().c_str()));
      return;
    }

  for (const auto& user : m_users) {
      if (user.GetLogin() == login) {
          m_user = user;
          m_user.SetOnlineStatus(1);
        }
    }

  if(m_user.GetBanStatus()) {
      QMessageBox::critical(this,
                            tr("Error"),
                            tr("Your account is banned. Please contact to admin by email: some_email@some_server.some_domain"));
      return;
    }

  emit accepted(m_user);
}

void LoginForm::on_buttonBox_rejected()
{
  emit rejected();
}

void LoginForm::on_singUpPushButton_clicked()
{
  emit registrationRequested();
}
