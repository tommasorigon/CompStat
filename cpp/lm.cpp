#include <RcppArmadillo.h>
// [[Rcpp::depends(RcppArmadillo)]]
// [[Rcpp::export]]
arma::colvec lm_coef3(const arma::mat& X, const arma::colvec& y) {
  arma::colvec coef = arma::solve(X, y);
  return(coef);
}