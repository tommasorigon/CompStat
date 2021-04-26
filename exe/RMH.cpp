#include <RcppArmadillo.h>
// [[Rcpp::depends(RcppArmadillo)]]
using namespace Rcpp;
using namespace arma;


vec my_dnorm(vec x, double mean, double sd){
  int n = x.n_elem;
  vec res(n);
  for(int i = 0; i < n; i++) {
    res(i) = R::dnorm(x(i), mean, sd, TRUE);
  }
  return res;
}

// [[Rcpp::export]] 
double loglik_C(vec beta, vec y, mat X) {
  vec eta = X * beta;
  return sum(dot(y, eta) - log(1 + exp(eta)));
}

// [[Rcpp::export]] 
double logpost_C(vec beta, vec y, mat X) {
  return(loglik_C(beta, y, X) + sum(my_dnorm(beta, 0, 10)));
}

// [[Rcpp::export]] 
mat RMH_arma(int R, int burn_in, arma::vec y, arma::mat X, arma::mat S){
  
  // Initialization
  double p = X.n_cols;
  mat out(R, p, fill::zeros);
  
  vec beta(p, fill::zeros); 
  double logp = logpost_C(beta, y, X);
  
  mat A = chol(S, "lower"); 

  for (int r = 0; r < R + burn_in; r++) {
     vec rn = as<arma::vec>(rnorm(p));
     vec beta_new = beta + A * rn;
     double logp_new = logpost_C(beta_new, y, X);
     double alpha = exp(logp_new - logp);
     double u = randu(1)[0];
     if(u < alpha){
      double logp = Rcpp::clone(logp_new);
      vec beta = beta_new.;
      }
     if (r > burn_in) {
       out.row(r - burn_in) = beta.t();
       out(r-burn_in, 0) = u;
       out(r-burn_in, 1) = alpha;
     }
  }
  return out;
}


// RMH <- function(R, burn_in, y, X, S) {
//   p <- ncol(X)
//   out <- matrix(0, R, p) # Initialize an empty matrix to store the values
//   beta <- rep(0, p) # Initial values
//   logp <- logpost(beta, y, X)
//   
// # Eigen-decomposition
//   eig <- eigen(S, symmetric = TRUE)
//     A1 <- t(eig$vectors) * sqrt(eig$values)
//     
// # Starting the Gibbs sampling
//     for (r in 1:(burn_in + R)) {
//       beta_new <- beta + c(matrix(rnorm(p), 1, p) %*% A1)
//       logp_new <- logpost(beta_new, y, X)
//       alpha <- min(1, exp(logp_new - logp))
//       if (runif(1) < alpha) {
//         logp <- logp_new
//         beta <- beta_new # Accept the value
//       }
// # Store the values after the burn-in period
//       if (r > burn_in) {
//         out[r - burn_in, ] <- beta
//       }
//     }
//     out
// }