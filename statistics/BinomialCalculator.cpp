#include "BinomialCalculator.h"
#include <boost/math/special_functions/binomial.hpp>
#include <boost/math/distributions/normal.hpp>

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

  float mass = 0.0;
  
  if (n > 100)
  {
    // Use the Normal approximation for the mass function to avoid overflow
    float normal_mean = n * p;
    float normal_sd = std::sqrt (n * p * (1 - p));
    mass = boost::math::pdf (boost::math::normal(normal_mean, normal_sd), k);
  }
  else
  {  
    // Use the binomial distribution for small observation numbers
    float C = boost::math::binomial_coefficient<float> (n, k);
    mass = C * std::pow (p, k) * std::pow(1.0 - p, n - k);
  }
  
  return mass;
}
