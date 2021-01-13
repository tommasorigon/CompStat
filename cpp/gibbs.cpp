#include <RcppArmadillo.h>
// [[Rcpp::depends(RcppArmadillo)]]
using namespace Rcpp;
using namespace arma;

// [[Rcpp::export]] 
mat gibbs_arma(vec x, double mu_mu, double sigma2_mu, double a_sigma, double b_sigma, int R, int burn_in){
  
  // Initialization
  double n = x.n_elem;
  double xbar = mean(x);
  mat out(R,2);
  
  // Initial values for mu and sigma
  double sigma2 = var(x);
  double mu = mean(x);
  
  for (int r = 0; r < R + burn_in; r++) {
    // Sample mu
    double sigma2_n = 1.0 / (1.0 / sigma2_mu + n / sigma2);
    double mu_n = sigma2_n * (mu_mu / sigma2_mu + n / sigma2 * xbar);
    mu = rnorm(1, mu_n, sqrt(sigma2_n))[0];
    
    // Sample sigma2
    double a_n = a_sigma + 0.5*n;
    double b_n = b_sigma + 0.5 * sum(pow(x - mu,2));
    // NOTE: rgamma in Rcpp use scale, not rate, as default
    sigma2 = 1.0 / rgamma(1, a_n, 1.0 / b_n)[0];
    
    if (r > burn_in) {
      out(r - burn_in, 0) = mu;
      out(r - burn_in, 1) = sigma2;
    }
  }
  return out;
}