#include <RcppArmadillo.h>
// [[Rcpp::depends(RcppArmadillo)]]
using namespace Rcpp;
using namespace arma;

// [[Rcpp::export]] 
double arma_sum(vec v){
  double sum = 0;
  int n = v.n_elem;
  for(int i=0; i < n; i++){
    sum += v[i];
  }
  return(sum);
}