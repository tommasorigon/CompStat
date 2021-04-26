#include <RcppArmadillo.h>
// [[Rcpp::depends(RcppArmadillo)]]
using namespace Rcpp;
using namespace arma;


// [[Rcpp::export]] 
double loglik_C(vec beta, vec y, mat X) {
  vec eta = X * beta;
  return sum( y % eta - log(1.0 + exp(eta)));
}

// [[Rcpp::export]] 
double logpost_C(vec beta, vec y, mat X) {
  return(loglik_C(beta, y, X) + sum( - dot(beta, beta) / 100));
}

// [[Rcpp::export]] 
mat RMH_arma(int R, int burn_in, arma::vec y, arma::mat X, arma::mat S){
  
  // Initialization
  double p = X.n_cols;
  mat out(R, p, fill::zeros);
  mat beta(p, 2, fill::zeros);
  vec logp(2, fill::zeros);
  vec rn(p);
  double alpha;
  
  logp(0) = logpost_C(beta.col(0), y, X);
  mat A = chol(S, "lower"); 

  for (int r = 0; r < R + burn_in; r++) {
     rn = randn(p);
     beta.col(1) = beta.col(0) + A * rn;
     logp(1) = logpost_C(beta.col(1), y, X);
     alpha = exp(logp(1) - logp(0));
     if(randu(1)[0] < alpha){
      logp(0) = logp(1);
      beta.col(0) = beta.col(1);
      }
     if (r >= burn_in) {
       out.row(r - burn_in) = trans(beta.col(0));
     }
  }
  return out;
}
