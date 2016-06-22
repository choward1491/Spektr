# Welcome to the Spektr Computational Math Library
## Spektr Purpose
The purpose of this project is to build various algorithms particularly suited to problems that might be tackled by **Computational Math**. Additionally, the algorithms will ideally mesh with each other and be built to be flexible and easy to use. 

Example applications might be for simulation, numerical optimization, Machine Learning, filtering and estimation, and more.

## Progress Made
At this point, algorithms have been developed for the following tasks:
- Simulation Framework for Time Dependent ODE/discrete systems of equations that has optional capability for Monte Carlo simulations
- Numerical Optimization algorithms
  - Gradient Based (Gradient Descent)
  - Stochastic Based (Particle Swarm)
- Machine Learning
  - Artificial Neural Network
  - Locally Weighted Regression
- Filtering/Estimation
  - Unscented Kalman Filter (UKF)
  - Time Series Estimator based on Neural Network
  - Neural-UKF: Filter based on UKF and ANN to accurately track time series and do hidden state estimations that cannot be done with the ANN Time Series estimator alone
- Linear Algebra
  - Template Metaprogramming Based Matrices
     - Special Form Matrices (Diagonal, Symmetric, Tridiagonal, Upper, Lower, Sparse)
  - Solution to Matrix Equations
     - Special Form Solutions (Diagonal, Symmetric, Tridiagonal, Upper, Lower)
     - Conjugate Gradient (without preconditioner)
     - Stack and Heap based memory storage options

## Things to be Completed
- Partial Differential Equation Frameworks/Solutions
  - Solutions for Linear/Nonlinear Elliptic/Parabolic/Hyperbolic Systems of Equations
- Training algorithms for Machine Learning models
  - Build K-fold Cross Validation Suite for comparing models and estimating errors
- Add Bayesian Filters
  - Linear Kalman Filter
  - Particle Filter
  - Gauss-Hermite Kalman Filter
- Add Linear Algebra Algorithms
  - Algorithms for obtaining partial/complete eigensystems
  - Algorithms for QR Factorization
  - Modify matrix template to use more optimized matrix multiplication based on matrix form
- Add algorithms for computing determinant and other common measures (trace, matrix norms, etc)
- Add structure to allow for complex matrices and unitary matrices
- Add matrix type that can store matrices as sub-matrices
- Add Trust Region optimization algorithms
- Add Newton and Quasi-Newton optimization algorithms
- Add Genetic Algorithms implementation(s)
- Add Gravitational Search Algorithms