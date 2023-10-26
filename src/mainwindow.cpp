#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "startscreen.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
}

MainWindow::~MainWindow()
{
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

  auto w = new MainWindow();
  w->setAttribute(Qt::WA_DeleteOnClose);

  return w;
}

void MainWindow::on_messageLineEdit_returnPressed()
{
  on_sendPushButton_clicked();
}

void MainWindow::on_sendPushButton_clicked()
{

}
