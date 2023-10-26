#include "startscreen.h"
#include "ui_startscreen.h"

#include <QMessageBox>

StartScreen::StartScreen(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::StartScreen)
{
  ui->setupUi(this);

  getDB();
  getUsers();

  ui->loginPage->setDatabase(m_database);
  ui->loginPage->setUsers(m_users);

  ui->registrationPage->setDatabase(m_database);
  ui->registrationPage->setUsers(m_users);

  connect(ui->loginPage, &LoginForm::registrationRequested, this, &StartScreen::setRegistrationForm);
  connect(ui->loginPage, &LoginForm::accepted, this, &StartScreen::onLoggedIn);
  connect(ui->loginPage, &LoginForm::rejected, this, &StartScreen::onRejectRequested);

  connect(ui->registrationPage, &RegistrationForm::loginRequested, this, &StartScreen::setLoginForm);
  connect(ui->registrationPage, &RegistrationForm::accepted, this, &StartScreen::onLoggedIn);
  connect(ui->registrationPage, &RegistrationForm::rejected, this, &StartScreen::onRejectRequested);
}

StartScreen::~StartScreen()
{
  delete ui;
}

void StartScreen::setLoginForm()
{
  ui->stackedWidget->setCurrentIndex(0);
}

void StartScreen::setRegistrationForm()
{
  ui->stackedWidget->setCurrentIndex(1);
}

void StartScreen::onLoggedIn()
{
  accept();
}

void StartScreen::onRejectRequested()
{
  reject();
}

void StartScreen::getDB() {
  QString message;
  if (!m_database->ConnectToDB(message)) {
      QMessageBox::critical(this,
                            tr("Error"),
                            tr(message.toStdString().c_str()));
      return;
    }
}

void StartScreen::getUsers(){
  int step = 0;

  QVector<QString> query = m_database->GetDataFromDB("SELECT id, name, login, password FROM users;");
  if (!query.empty()) {
      while (step < query.size()) {
          m_users.push_back(User(query[step + 1], query[step + 2], sha1(query[step + 3].toStdString())));

          step += 4;
        }
    }
}
