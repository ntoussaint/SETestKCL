#include<QMessageBox>
#include<QKeyEvent>

#include "MainWindow.h"

void MainWindow::keyPressEvent(QKeyEvent* e)
{
  QMessageBox* box = new QMessageBox();
  box->setWindowTitle(QString("Hello"));
  box->setText(QString("You Pressed: ")+ e->text());
  box->show();
};
