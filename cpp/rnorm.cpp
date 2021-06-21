#include <RcppArmadillo.h>
// [[Rcpp::depends(RcppArmadillo)]]
using namespace Rcpp;
using namespace arma;

// [[Rcpp::export]]
vec arma_rnorm(int n, double mean, double sd) {
  vec out(n); // Allocate a vector of dimension n
  for (int i = 0; i < n; i++) {
    out[i] = R::rnorm(mean, sd); // Sample from a Gaussian distribution
  }
  return out; 
}