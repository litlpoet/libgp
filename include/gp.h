// libgp - Gaussian process library for Machine Learning
// Copyright (c) 2013, Manuel Blum <mblum@informatik.uni-freiburg.de>
// All rights reserved.

/*!
 *
 *   \page licence Licensing
 *
 *     libgp - Gaussian process library for Machine Learning
 *
 *      \verbinclude "../COPYING"
 */
#ifndef INCLUDE_GP_H_
#define INCLUDE_GP_H_

#define _USE_MATH_DEFINES
#include <Eigen/Dense>

#include <cmath>
#include <string>

#include "cov.h"
#include "sampleset.h"

namespace libgp {

/** Gaussian process regression.
 *  @author Manuel Blum */
class GaussianProcess {
 public:
  /** Create and instance of GaussianProcess with given input dimensionality
   *  and covariance function. */
  GaussianProcess(size_t input_dim, std::string covf_def);

  /** Create and instance of GaussianProcess from file. */
  explicit GaussianProcess(const char *filename);

  virtual ~GaussianProcess();

  /** Write current gp model to file. */
  void write(const char *filename);

  /** Predict target value for given input.
   *  @param x input vector
   *  @return predicted value */
  virtual double f(const double x[]);

  /** Predict variance of prediction for given input.
   *  @param x input vector
   *  @return predicted variance */
  virtual double var(const double x[]);

  /** Add input-output-pair to sample set.
   *  Add a copy of the given input-output-pair to sample set.
   *  @param x input array
   *  @param y output value
   */
  void add_pattern(const double x[], double y);

  bool set_y(size_t i, double y);

  /** Get number of samples in the training set. */
  size_t get_sampleset_size();

  /** Clear sample set and free memory. */
  void clear_sampleset();

  /** Get reference on currently used covariance function. */
  CovarianceFunction &covf();

  /** Get input vector dimensionality. */
  size_t get_input_dim();

  double log_likelihood();

  Eigen::VectorXd log_likelihood_gradient();

 protected:
  /** The covariance function of this Gaussian process. */
  CovarianceFunction *cf;

  /** The training sample set. */
  SampleSet *sampleset;

  /** Alpha is cached for performance. */
  Eigen::VectorXd alpha;

  /** Last test kernel vector. */
  Eigen::VectorXd k_star;

  /** Linear solver used to invert the covariance matrix. */
  //    Eigen::LLT<Eigen::MatrixXd> solver;
  Eigen::MatrixXd L;

  /** Input vector dimensionality. */
  size_t input_dim;

  /** Update test input and cache kernel vector. */
  void update_k_star(const Eigen::VectorXd &x_star);

  void update_alpha();

  /** Compute covariance matrix and perform cholesky decomposition. */
  virtual void compute();

  bool alpha_needs_update;
};

}  // namespace libgp

#endif  // INCLUDE_GP_H_
