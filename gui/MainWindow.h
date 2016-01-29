#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include<QMainWindow>

class QKeyEvent;

class MainWindow: public QMainWindow
{
  Q_OBJECT
  
 public:
  MainWindow(){};
  ~MainWindow(){};

  void keyPressEvent(QKeyEvent* e);

};

#endif
