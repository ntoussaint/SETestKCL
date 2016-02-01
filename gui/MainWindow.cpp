#include "MainWindow.h"

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

#include "QCustomPlot.h"
#include "BinomialCalculator.h"

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
  mainLayout->addWidget(this->usageBox, 0, Qt::AlignTop);
  mainLayout->addWidget(this->counterBox, 0, Qt::AlignTop);
  mainLayout->addWidget(this->summaryBox, 1);
  mainLayout->addWidget(this->buttonBox, 0, Qt::AlignBottom);
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
  layout->addWidget(this->eTimeLabel, 0, 0, Qt::AlignTop);
  this->ratioLabel = new QLabel(tr("Ratio of 'yes' over 'no': 0.00"));
  layout->addWidget(this->ratioLabel, 0, 1, Qt::AlignTop);
  this->yRateLabel = new QLabel(tr("Rate of 'yes': 0.00 / min"));
  layout->addWidget(this->yRateLabel, 1, 0, Qt::AlignTop);
  this->nRateLabel = new QLabel(tr("Rate of 'no': 0.00 / min"));
  layout->addWidget(this->nRateLabel, 1, 1, Qt::AlignTop);

  this->customPlot = new QCustomPlot();
  this->customPlot->legend->setVisible(true);
  this->customPlot->legend->setFont(QFont("Helvetica",9));
  this->customPlot->addGraph();
  this->customPlot->graph(0)->setName("Current Binomial Distribution");
  this->customPlot->graph(0)->setPen(QPen(Qt::blue)); 
  this->customPlot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20))); 
  this->customPlot->addGraph();
  this->customPlot->graph(1)->setName("Number of Yes");
  this->customPlot->graph(1)->setPen(QPen(Qt::red)); 
  this->customPlot->xAxis2->setVisible(true);
  this->customPlot->xAxis2->setTickLabels(false);
  this->customPlot->yAxis2->setVisible(true);
  this->customPlot->yAxis2->setTickLabels(false);
  connect(this->customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), this->customPlot->xAxis2, SLOT(setRange(QCPRange)));
  connect(this->customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), this->customPlot->yAxis2, SLOT(setRange(QCPRange)));
  this->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);  
  layout->addWidget(this->customPlot, 2, 0, 1, 2);
  layout->setRowStretch (0, 0);
  layout->setRowStretch (1, 0);
  layout->setRowStretch (2, 1);
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
	// this->UpdateSummary();
	break;
      case Qt::Key_N:
	this->ListOfOperations.push_back (MainWindow::Operation_No);
	this->UpdateCounter();
	// this->UpdateSummary();
	break;
      case Qt::Key_Z:
	this->ListOfOperations.pop_back();
	this->UpdateCounter();
	// this->UpdateSummary();
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
    return;
  unsigned int y = std::count (this->ListOfOperations.begin(), this->ListOfOperations.end(), MainWindow::Operation_Yes);
  unsigned int n = std::count (this->ListOfOperations.begin(), this->ListOfOperations.end(), MainWindow::Operation_No);
  this->numberOfYesLabel->setText(tr("Yes: %1").arg(y));
  this->numberOfNoLabel->setText(tr("No: %1").arg(n));
}


void MainWindow::UpdateSummary()
{
  if (this->summaryBox == NULL)
    return;
      
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

  if (this->Calculator == NULL ||
      !this->ListOfOperations.size())
    return;

  this->Calculator->SetNumberOfExperiments (this->ListOfOperations.size());
  this->Calculator->SetProbabilityOfSuccess (0.5);
  
  std::vector<float> pmf;
  float max_p = 0.0;
  
  for (unsigned int i=0; i<this->ListOfOperations.size(); i++)
  {
    float p = this->Calculator->GetProbabilityMassFunction (i);
    pmf.push_back (p);
    max_p = std::max (p, max_p);
  }
  
  QVector<double> x0(this->ListOfOperations.size()), y0(this->ListOfOperations.size());
  for (unsigned int i=0; i<this->ListOfOperations.size(); ++i)
  {
    x0[i] = i;
    y0[i] = pmf[i];
  }
  
  QVector<double> x1 (2), y1 (2);
  x1[0] = y;
  x1[1] = y;
  y1[0] = 0;
  y1[1] = max_p;
  
  this->customPlot->graph(0)->setData(x0, y0);
  this->customPlot->graph(1)->setData(x1, y1);
  this->customPlot->graph(0)->rescaleAxes();
  this->customPlot->graph(1)->rescaleAxes();
  this->customPlot->replot();
}
