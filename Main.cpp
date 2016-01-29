#include <QApplication>
#include <QMainWindow>
#include "MainWindow.h"

int main(int argc, char **argv)
{
  QApplication a(argc, argv);  
  MainWindow *window = new MainWindow();
  window->setWindowTitle(QString::fromUtf8("Negitiation Study"));
  window->resize(336, 227);
  window->show();
  return a.exec();
}
