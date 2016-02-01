#ifndef BINOMIALCALCULATOR_H
#define BINOMIALCALCULATOR_H

#include <cassert>

/**
   
   \class BinomialCalculator

   \brief 
   \author Nicolas Toussaint
*/


class BinomialCalculator
{
 public:
  
  BinomialCalculator();
  ~BinomialCalculator(){};
  
  void SetNumberOfExperiments (unsigned int n)
  {
    assert (n >= 1);
    this->NumberOfExperiments = n;
  }
  
  unsigned int GetNumberOfExperiments (void) const
  {
    return this->NumberOfExperiments;
  }
  void SetProbabilityOfSuccess (float p)
  {
    assert (p > 0.0);
    assert (p < 1.0);
    this->ProbabilityOfSuccess = p;
  }
  
  float GetProbabilityOfSuccess (void) const
  {
    return this->ProbabilityOfSuccess;
  }
  
  float GetProbabilityMassFunction (unsigned int k) const;
  
  
 private:

  unsigned int NumberOfExperiments;
  float ProbabilityOfSuccess;
  
};

#endif
