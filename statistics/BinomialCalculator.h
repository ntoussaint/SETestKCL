#ifndef BINOMIALCALCULATOR_H
#define BINOMIALCALCULATOR_H

#include <cassert>

/**
   
   \class BinomialCalculator

   \brief This class is a simple helper that embeds probability functionalities for a
   binomial distribution.

   Two parameters for this class: NumberOfExperiments and ProbabilityOfSuccess

   The class uses the Boost library (http://www.boost.org/) to retrieve the binomial coefficients
   needed for the calculation of the Mass function of a binomial distribution.
   
   Note that for high value of N (typically N > 100), the binomial distribution is approximated
   to a Normal distribution.

   The main method to retrieve the Mass function is GetProbabilityMassFunction() taking the number
   of successes as parameter

   You can set the two parameters
   \author Nicolas Toussaint
*/


class BinomialCalculator
{
 public:
  
  BinomialCalculator();
  ~BinomialCalculator(){};

  /**
     Set the number of experiments (parameter N of the binomial distribution)
  */
  void SetNumberOfExperiments (unsigned int n)
  {
    assert (n >= 1);
    this->NumberOfExperiments = n;
  }
  /**
     Get the number of experiments (parameter N of the binomial distribution)
  */
  unsigned int GetNumberOfExperiments (void) const
  {
    return this->NumberOfExperiments;
  }
  /**
     Set the probability of success (parameter p of the binomial distribution)
  */
  void SetProbabilityOfSuccess (float p)
  {
    assert (p > 0.0);
    assert (p < 1.0);
    this->ProbabilityOfSuccess = p;
  }
  /**
     Get the probability of success (parameter p of the binomial distribution)
  */  
  float GetProbabilityOfSuccess (void) const
  {
    return this->ProbabilityOfSuccess;
  }  
  /**
     Get the probability mass function value for value k
     \param k The number of success amongst the experiments
  */  
  float GetProbabilityMassFunction (unsigned int k) const;
  
  
 private:

  unsigned int NumberOfExperiments;
  float ProbabilityOfSuccess;
  
};

#endif
