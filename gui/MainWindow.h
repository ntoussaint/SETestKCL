#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include<QDialog>

class QKeyEvent;
class QElapsedTimer;
class QAction;
class QDialogButtonBox;
class QGroupBox;
class QLabel;
class QLineEdit;
class QMenu;
class QMenuBar;
class QPushButton;
class QTextEdit;
class QElapsedTimer;

class QCustomPlot;
class BinomialCalculator;

/**
   
   \class MainWindow

   \brief This class implements the main window of the program.

   It shows the usage help message, detects key stroke and process it, and allows for
   the count of 'yes' and 'no' during the negotiation.
   
   The method keyPressEvent() implements the callback for any key stroke   
   
   \author Nicolas Toussaint
*/

class MainWindow: public QDialog
{
  Q_OBJECT
  
 public:
  MainWindow();
  ~MainWindow(){};

  /**
     List of operations captured
  */
  enum OperationIds
  {
    Operation_No = 0,
    Operation_Yes = 1
  };
  /**
     List of refresh modes
  */
  enum RefreshModeIds
  {
    Refresh_Continuous = 0,
    Refresh_NonContinuous = 1
  };
  /**
     Set the Binomial calculator object, used to estimate the
     probability of the observed sequence of yes and no
  */
  void SetCalculator (BinomialCalculator* c)
  {
    this->Calculator = c;
  }
  /**
     Get the Binomial calculator object, used to estimate the
     probability of the observed sequence of yes and no
     \see class BinomialCalculator
  */
  BinomialCalculator* GetCalculator (void) const
  {
    return this->Calculator;
  }
  /**
     Get the refresh mode of the window.
     if set to MainWindow::Refresh_Continuous, the summary will be refresh at every
     stroke of 'y', 'n', and 'z', additionally to 's' and 'q'
     if set to MainWindow::Refresh_NonContinuous, the summary will be refresh only
     at the stroke of 's' or 'q'
  */
  unsigned int GetRefreshMode (void) const
  {
    return this->RefreshMode;
  }
  /**
     Set the refresh mode of the window.
     if set to MainWindow::Refresh_Continuous, the summary will be refresh at every
     stroke of 'y', 'n' and 'z', additionally to 's' and 'q'
     if set to MainWindow::Refresh_NonContinuous, the summary will be refresh only
     at the stroke of 's' or 'q'
  */
  void SetRefreshMode (unsigned int m)
  {
    this->RefreshMode = m;
  }
  
  
 protected:
  
  
  /**
     Callback method for the QKeyEvent (key stroke)
     This method is a re-implementation of the QDialog::keyPressEvent() method
     Allows to detect key stroke and process the key accordingly
  */
  void keyPressEvent(QKeyEvent* e);
  /**
     Update the labels containing the number of yes and no in the window
  */
  void UpdateCounter (void);
  /**
     Update the summary of the negotiation.

     That includes the calculation of probability of the observed sequence,
     invoking BinomialCalculator::GetProbabilityMassFunction()
  */
  void UpdateSummary (void);
  /**
     Writes the summary in a file for future reference
  */
  void WriteSummary (const char* filename){};
  
  
 private:
  
  /**
     Create usage box, adding it to the layout
  */
  void createUsageBox();
  /**
     Create counter box, adding it to the layout
  */
  void createCounterBox();
  /**
     Create summary box, adding it to the layout
  */
  void createSummaryBox();
  
  /**
     Timer to calculate the elapsed time of the negotiation
  */
  QElapsedTimer* timer;
  /**
     Binomial calculator object reference
  */
  BinomialCalculator* Calculator;
  /**
     Container of the list of successive operations (yes and no)
     Manipulated in MainWindow::UpdateCounter()
  */
  std::vector<unsigned int> ListOfOperations;
  /**
     String containing the usage text
  */
  std::string Usage;
  /**
     Parameter containing the RefreshMode for the Summary
  */
  unsigned int RefreshMode;
  
  QGroupBox *usageBox;
  QGroupBox *counterBox;
  QGroupBox *summaryBox;
  QDialogButtonBox *buttonBox;
  QLabel* numberOfYesLabel;
  QLabel* numberOfNoLabel;
  QLabel* eTimeLabel;
  QLabel* ratioLabel;
  QLabel* yRateLabel;
  QLabel* nRateLabel;
  QCustomPlot* customPlot;
  
};

#endif
