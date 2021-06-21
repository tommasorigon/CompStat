#include <RcppArmadillo.h>
// [[Rcpp::depends(RcppArmadillo)]]
using namespace Rcpp;
using namespace arma;

// [[Rcpp::export]] 
double arma_sum(vec x){
  double sum = 0;
  int n = x.n_elem; // Length of the vector x
  for(int i=0; i < n; i++){
    sum += x[i]; // Shorthand for: sum = sum + x[i];
  }
  return(sum);
}