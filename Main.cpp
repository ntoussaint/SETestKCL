#include <QApplication>
#include <QMainWindow>
#include "MainWindow.h"

#include "BinomialCalculator.h"

int main(int argc, char **argv)
{
  QApplication a(argc, argv);  
  MainWindow *window = new MainWindow();
  BinomialCalculator* calculator = new BinomialCalculator();
  window->SetCalculator (calculator);
  
  window->setWindowTitle(QString::fromUtf8("Negitiation Study"));
  window->resize(336, 227);
  window->show();
  return a.exec();
}
