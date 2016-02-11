// libgp - Gaussian process library for Machine Learning
// Copyright (c) 2013, Manuel Blum <mblum@informatik.uni-freiburg.de>
// All rights reserved.

#ifndef INCLUDE_COV_FACTORY_H_
#define INCLUDE_COV_FACTORY_H_

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

#include "cov.h"

namespace libgp {

template <typename ClassName>
CovarianceFunction* create_func() {
  return new ClassName();
}

/** Factory class for generating instances of CovarianceFunction.
 *  @author Manuel Blum */
class CovFactory {
 public:
  CovFactory();
  virtual ~CovFactory();

  /** Create an instance of CovarianceFunction.
   *  @param input_dim input vector dimensionality
   *  @param key string representation of covariance function
   *  @return instance of CovarianceFunction */
  libgp::CovarianceFunction* create(size_t input_dim, const std::string key);

  /** Returns a string vector of available covariance functions. */
  std::vector<std::string> list();

 private:
  typedef CovarianceFunction* (*create_func_def)();
  std::map<std::string, CovFactory::create_func_def> registry;
};

}  // namespace libgp

#endif  // INCLUDE_COV_FACTORY_H_
