#include "startscreen.h"
#include "ui_startscreen.h"

#include <QMessageBox>

StartScreen::StartScreen(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::StartScreen)
{
  ui->setupUi(this);

  connectDB();
  setUsers();

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

std::shared_ptr<DataBase> StartScreen::getDB()
{
  return m_database;
}

void StartScreen::connectDB() {
  QString message;
  if (!m_database->ConnectToDB(message)) {
      QMessageBox::critical(this,
                            tr("Error"),
                            tr(message.toStdString().c_str()));
      return;
    }
}

User StartScreen::getUser() const
{
    return m_user;
}

void StartScreen::setUsers(){
  int step = 0;

    QVector<QString> query = m_database->GetDataFromDB("SELECT id, name, login, password, ban_status, online_status FROM users;");
  if (!query.empty()) {
      while (step < query.size()) {
          m_users.push_back(User(query[step + 1], query[step + 2], sha1(query[step + 3].toStdString()), query[step+4].toInt()));

          step += 6;
        }
    }
}

void StartScreen::setLoginForm() const
{
  ui->stackedWidget->setCurrentIndex(0);
}

void StartScreen::setRegistrationForm() const
{
  ui->stackedWidget->setCurrentIndex(1);
}

void StartScreen::onLoggedIn(const User& user)
{
  m_user = user;

  accept();
}

void StartScreen::onRejectRequested()
{
  reject();
}
