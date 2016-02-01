#include "BinomialCalculator.h"
#include <boost/math/special_functions/binomial.hpp>

#include <cmath>
#include <iostream>

BinomialCalculator::BinomialCalculator(void)
{
  this->NumberOfExperiments = 1;
  this->ProbabilityOfSuccess = 0.5;
  
};

float BinomialCalculator::GetProbabilityMassFunction (unsigned int k) const
{
  unsigned int n = this->NumberOfExperiments;
  if (k > n)
  {
    std::cerr << "ERROR: number of successes cannot be greater than number of experiments" <<std::endl;
    return 0;
  }
  
  float p = this->ProbabilityOfSuccess;
  float C = boost::math::binomial_coefficient<float> (n, k);
  float mass = C * std::pow (p, k) * std::pow(1.0 - p, n - k);
  return mass;
}
