#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "startscreen.h"

#include <QTimer>
#include <QMessageBox>

MainWindow::MainWindow(const User& user, std::shared_ptr<DataBase> database, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_user(user),
    m_database(database)
{
    ui->setupUi(this);

    m_database->QueryToDB("UPDATE users SET online_status=1 WHERE login='" + m_user.GetLogin() + "';");

    ui->nameLabel->setText(m_user.GetName());
    loadHistory();

    model.setTable("users");
    model.setEditStrategy(QSqlTableModel::OnFieldChange);
    model.select();
    ui->userListTableView->setModel(&model);
    ui->userListTableView->hideColumn(0);
    ui->userListTableView->hideColumn(3);

    auto timer_message = new QTimer(this);
    connect(timer_message, &QTimer::timeout, this, &MainWindow::loadHistory);
    timer_message->start(100);

    auto timer_db = new QTimer(this);
    connect(timer_db, &QTimer::timeout, this, &MainWindow::getStatus);
    timer_db->start(10000);
}

MainWindow::~MainWindow()
{
    m_database->QueryToDB("UPDATE users SET online_status=0 WHERE login='" + m_user.GetLogin() + "';");

    delete ui;
}

MainWindow *MainWindow::createClient()
{
    StartScreen s;

    auto result = s.exec();

    if(result == QDialog::Rejected)
    {
        return nullptr;
    }

    auto w = new MainWindow(s.getUser(), s.getDB());
    w->setAttribute(Qt::WA_DeleteOnClose);

    return w;
}

void MainWindow::on_messageLineEdit_returnPressed()
{
    on_sendPushButton_clicked();
}

void MainWindow::getStatus(){
    QVector<QString> query = m_database->GetDataFromDB("SELECT id, name, login, password, ban_status, online_status FROM users WHERE login='" + m_user.GetLogin() + "';");
    if (!query.empty()) {
        if(m_user.GetOnlineStatus() != query[5].toInt()) {
            showErrorMessage("Account disconected!");
            on_actionClose_triggered();
        }
    }
    model.select();
}

void MainWindow::getMessages() {
    int step = 0;

    QVector<QString> query = m_database->GetDataFromDB("SELECT id, sender, receiver, text FROM messages;");
    if (!query.empty()) {
        while (step < query.size()) {
            m_messages.push_back(Message(query[step + 1], query[step + 2], query[step + 3]));

            step += 4;
        }
    }
}

void MainWindow::loadHistory() {
    m_messages.clear();

    getMessages();

    const QString user_name = m_user.GetName();
    QString history_message;

    for (const auto& message : m_messages) {
        if (message.GetTo() != "all") {
            history_message.append("[" + message.GetFrom() + " to " + message.GetTo() + "]: " + message.GetText() + "\n");

            if(ui->textBrowser->toPlainText() != history_message) {
                ui->textBrowser->setText(history_message);
                ui->textBrowser->moveCursor(QTextCursor::End);
            }
        }
        else {
            history_message.append("[" + message.GetFrom() + "]: " + message.GetText() + "\n");

            if(ui->textBrowser->toPlainText() != history_message) {
                ui->textBrowser->setText(history_message);
                ui->textBrowser->moveCursor(QTextCursor::End);
            }
        }
    }
}

void MainWindow::on_sendPushButton_clicked()
{
    if (m_user.GetBanStatus()) {
        showErrorMessage("Account banned!");
        return;
    }

    const QString from = m_user.GetName();

    QString to = "all";
    QString text = ui->messageLineEdit->text();

    if (text[0] == '@') {
        if(!privateMessage(text, to)) {
            return;
        }
    }

    if (text.isEmpty()) {
        showErrorMessage("Message is not typed");
        return;
    }

    m_database->QueryToDB("INSERT into messages (sender, receiver, text) VALUES ('" + from + "', '" + to + "', '" + text + "');");
    m_messages.push_back(Message(from, to, text));

    m_log->WriteToLogFile("From " + from.toStdString() + " to " + to.toStdString() + ": " + text.toStdString());

    //ui->textBrowser->append("[" + from + "]: " + text);
    ui->messageLineEdit->clear();
}

bool MainWindow::privateMessage(QString& text, QString& to) {
    if (text[1] == ' ') {
        showErrorMessage("Enter cannot contain space between @ and name");
        return false;
    }

    to.clear();

    int count = 0;
    for (const auto& ch : text) {
        if (ch == ' ') {
            break;
        }
        else if (ch == '@') {
            continue;
        }
        else {
            to += ch;
            count += 1;
        }
    }

    if (m_user.GetName() == to) {
        showErrorMessage("You cannot send message to yourself");
        return false;
    }

    int pos = text.indexOf(' ');
    if (text[pos + 1] == ' ') {
        showErrorMessage("Enter cannot contain two or more space between name and message");
        return false;
    }

    if (text.size() < count + 2) {
        showErrorMessage("Message is not typed");
        return false;
    }
    else {
        text = text.right(text.size() - (count + 2));
    }

    return true;
}

void MainWindow::showErrorMessage(const QString& message) {
    QMessageBox::critical(this,
                          tr("Error"),
                          tr(message.toStdString().c_str()));
}

void MainWindow::on_actionClose_triggered()
{
    this->close();
}

void MainWindow::on_actionCommands_triggered()
{
    QMessageBox::information(this,
                             tr("Commands"),
                             tr("Type \"@name\" to send private message"));
}
