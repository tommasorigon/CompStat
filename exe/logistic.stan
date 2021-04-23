data {
  int<lower=0> n;   // number of data items
  int<lower=0> p;   // number of predictors
  matrix[n, p] X;   // predictor matrix
  int<lower=0,upper=1> y[n];
}
parameters {
  vector[p] beta;       // coefficients for predictors
}
model {
  y ~ bernoulli_logit(X * beta);
}
