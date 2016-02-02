#include "BinomialCalculator.h"
#include <iostream>
#include <cmath>

int BinomialCalculatorTest(int argc, char* argv[])
{
  std::cout<<"testing Binomial Calculator ..." <<std::endl;
  BinomialCalculator* c = new BinomialCalculator();
  c->SetProbabilityOfSuccess (0.5);
  c->SetNumberOfExperiments (1);

  float p05 = c->GetProbabilityMassFunction (1);
  std::cout<<"binomial distribution with N=" << c->GetNumberOfExperiments() << ", p=" << c->GetProbabilityOfSuccess() << " -- probability p(k=1) = " << p05 << std::endl;
  if (std::abs (p05 - 0.5) >= 1e-5)
  {
    std::cerr<< "The probability should be egual to 0.5" << std::endl;
    return EXIT_FAILURE;
  }
  
  return EXIT_SUCCESS;
}
