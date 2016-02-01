#include <iostream>

#include <QtGui>
#include <QAction>
#include <QDialogButtonBox>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QMenu>
#include <QMenuBar>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QFormLayout>
#include <QComboBox>
#include <QSpinBox>
#include <QMessageBox>
#include <QKeyEvent>
#include <QElapsedTimer>

#include "MainWindow.h"

MainWindow::MainWindow()
{
  this->Calculator = NULL;
  this->createUsageBox();
  this->createCounterBox();
  this->createSummaryBox();
  this->buttonBox = new QDialogButtonBox(QDialogButtonBox::Save | QDialogButtonBox::Close);
  connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
  connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
  QVBoxLayout *mainLayout = new QVBoxLayout;
  mainLayout->addWidget(this->usageBox);
  mainLayout->addWidget(this->counterBox);
  mainLayout->addWidget(this->summaryBox);
  mainLayout->addWidget(this->buttonBox);
  this->setLayout(mainLayout);
  this->setWindowTitle(tr("Negotiation Study"));

  this->timer = new QElapsedTimer();
  this->timer->start();  
}

void MainWindow::createUsageBox()
{
  std::string usage =
    "Please press one of the following key: \n \
    - 'y': When you hear 'yes' \n \
    - 'n': When you hear 'no' \n \
    - 's': To show a summary of the negotiation \n \
    - 'q': To show a summary and quit the program \n";
  
  this->usageBox = new QGroupBox(tr("Usage"));
  QHBoxLayout *layout = new QHBoxLayout;
  QLabel* usageLabel = new QLabel (tr (usage.c_str()));
  layout->addWidget (usageLabel);
  this->usageBox->setLayout(layout);
  std::cout<<"constructor"<<std::endl;
}

void MainWindow::createCounterBox()
{
  this->counterBox = new QGroupBox(tr("Counter"));
  QGridLayout *layout = new QGridLayout;
  this->numberOfYesLabel = new QLabel(tr("Yes: 0"));
  layout->addWidget(this->numberOfYesLabel, 0, 0);
  this->numberOfNoLabel = new QLabel(tr("No: 0"));
  layout->addWidget(this->numberOfNoLabel, 0, 1);
  QFont f;
  f = this->numberOfYesLabel->font();
  f.setPointSize (24);
  f.setBold (true);
  this->numberOfYesLabel->setFont (f);
  f = this->numberOfNoLabel->font();
  f.setPointSize (24);
  f.setBold (true);
  this->numberOfNoLabel->setFont (f);
  this->counterBox->setLayout(layout);
}

void MainWindow::createSummaryBox()
{
  this->summaryBox = new QGroupBox(tr("Summary"));
  QGridLayout *layout = new QGridLayout;
  this->eTimeLabel = new QLabel(tr("Elapsed Time: 0.00 min"));
  layout->addWidget(this->eTimeLabel, 0, 0);
  this->ratioLabel = new QLabel(tr("Ratio of 'yes' over 'no': 0.00"));
  layout->addWidget(this->ratioLabel, 0, 1);
  this->yRateLabel = new QLabel(tr("Rate of 'yes': 0.00 / min"));
  layout->addWidget(this->yRateLabel, 1, 0);
  this->nRateLabel = new QLabel(tr("Rate of 'no': 0.00 / min"));
  layout->addWidget(this->nRateLabel, 1, 1);
  
  this->summaryBox->setLayout(layout);
}

void MainWindow::keyPressEvent(QKeyEvent* e)
{
  if (this->Calculator == NULL)
  {
    std::cerr << "ERROR: No calculator associated." << std::endl;
    return;
  }
  
  switch(e->key())
  {
      case Qt::Key_Y:
	this->ListOfOperations.push_back (MainWindow::Operation_Yes);
	this->UpdateCounter();
	break;
      case Qt::Key_N:
	this->ListOfOperations.push_back (MainWindow::Operation_No);
	this->UpdateCounter();
	break;
      case Qt::Key_Z:
	this->ListOfOperations.pop_back();
	this->UpdateCounter();
	break;
      case Qt::Key_S:
	this->UpdateCounter();
	this->UpdateSummary();
	break;
      case Qt::Key_Q:
	this->UpdateCounter();
	this->UpdateSummary();
	
	break;
      default:
	break;
  }
  
}

void MainWindow::UpdateCounter()
{
  if (this->counterBox == NULL)
  {
    return;
  }
  
  unsigned int y = std::count (this->ListOfOperations.begin(), this->ListOfOperations.end(), MainWindow::Operation_Yes);
  unsigned int n = std::count (this->ListOfOperations.begin(), this->ListOfOperations.end(), MainWindow::Operation_No);
  this->numberOfYesLabel->setText(tr("Yes: %1").arg(y));
  this->numberOfNoLabel->setText(tr("No: %1").arg(n));
}


void MainWindow::UpdateSummary()
{
  unsigned int y = std::count (this->ListOfOperations.begin(), this->ListOfOperations.end(), MainWindow::Operation_Yes);
  unsigned int n = std::count (this->ListOfOperations.begin(), this->ListOfOperations.end(), MainWindow::Operation_No);
  float ratio = this->ListOfOperations.size() ? (float)(y)/(float)(this->ListOfOperations.size()) : 0;
  float elapsed_minutes = (float) this->timer->elapsed() / (1000.0 * 60.0);
  float yrate = (float)(y) / elapsed_minutes;
  float nrate = (float)(n) / elapsed_minutes;
  
  this->eTimeLabel->setText(tr("Elapsed Time: %1 min").arg(QString::number (elapsed_minutes, 'f', 2 )));
  this->ratioLabel->setText(tr("Ratio of 'yes' over 'no': %1").arg(QString::number (ratio, 'f', 2 )));
  this->yRateLabel->setText(tr("Rate of 'yes': %1 / min").arg(QString::number (yrate, 'f', 2 )));
  this->nRateLabel->setText(tr("Rate of 'no': %1 / min").arg(QString::number (nrate, 'f', 2 )));

  
  
}
