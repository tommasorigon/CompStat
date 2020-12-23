#include <Rcpp.h> // Rcpp library
using namespace Rcpp;

// [[Rcpp::export]]
Rcpp::NumericVector rnorm2(int n, double mean, double sd) {
  NumericVector out(n); // Allocate a vector of dimension n
  for (int i = 0; i < n; i++) {
    out[i] = R::rnorm(mean, sd); // Random gaussian
  }
    return out; 
}