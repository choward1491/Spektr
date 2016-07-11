//
//  UKF_Impl.hpp
//  Spektr
//
//  Created by Christian J Howard on 7/9/16.
//
//  The MIT License (MIT)
//    Copyright © 2016 Christian Howard. All rights reserved.
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in all
//  copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//  SOFTWARE.
//
//

#ifndef UKF_Impl_h
#define UKF_Impl_h

#include "UKF.hpp"
#include "Cholesky.hpp"

#define TEMPLATE_HEADER template<class D1, class M1>
#define UKF UnscentedKF<D1,M1>

namespace spektr {
namespace filter {


TEMPLATE_HEADER
void UKF::init(){
    la::cholesky( Pxx, S );
    setCholesky = true;
}


TEMPLATE_HEADER
UKF::UnscentedKF():Q(nx,nx),R(nz,nz),Pxx(nx,nx),Pzz(nz,nz),
Pxz(nx,nz),sigx(1+2*nx),x(nx,1),setCholesky(false){
    for (int i = 0; i < nx; i++) { Q(i,i) = 1.0; Pxx(i,i) = 1.0; }
    for (int i = 0; i < nz; i++) { R(i,i) = 1.0; Pzz(i,i) = 1.0; }
    t = 0;
    setCenterWeight(0.01);
}

TEMPLATE_HEADER
UKF::UnscentedKF( const Mat & x0 ):Q(nx,nx),R(nz,nz),Pxx(nx,nx),Pzz(nz,nz),
Pxz(nx,nz),sigx(1+2*nx),x(x0),setCholesky(false){
    for (int i = 0; i < nx; i++) { Q(i,i) = 1.0; Pxx(i,i) = 1.0; }
    for (int i = 0; i < nz; i++) { R(i,i) = 1.0; Pzz(i,i) = 1.0; }
    t = 0;
    setCenterWeight(0.01);
}

TEMPLATE_HEADER
void UKF::setCenterWeight( double w0_ ){
    w0 = w0_;
    w1 = (1.0 - w0) / (2.0 * nx);
    q = 1.0 / sqrt(2.0*w1);
}

TEMPLATE_HEADER
UKF::~UnscentedKF(){
    
}

TEMPLATE_HEADER
void UKF::setInitState( const Mat & x0 ){
    x = x0;
}

TEMPLATE_HEADER
void UKF::computeStatePrediction( double dt, std::vector<Mat> & fx, Mat & xt ){
    fx[0] = f(dt, sigx[0]);
    xt = w0*fx[0];
    for (int i = 1; i <= 2*nx; i++) {
        fx[i] = f(dt, sigx[i]);
        xt = xt + w1*fx[i];
    }
}

TEMPLATE_HEADER
void UKF::computeMeasPrediction( std::vector<Mat> & hx, Mat & zt ){
    hx[0] = h(sigx[0]);
    zt = w0*hx[0];
    for (int i = 1; i <= 2*nx; i++) {
        hx[i] = h(sigx[i]);
        zt = zt + w1*hx[i];
    }
}

TEMPLATE_HEADER
void UKF::computeSigmaPoints( const Mat & x_, Mat & ut ){
    sigx[0] = x_;
    for (int i = 1; i <= nx; i++) {
        S.getColumn(ut,i-1);
        int ind = 1 + 2*(i-1);
        sigx[ind]     = x_ + q*ut;
        sigx[ind+1]   = x_ - q*ut;
    }
}

TEMPLATE_HEADER
void UKF::compute2ndOrderMoment( const Mat & x_,
                                               const std::vector<Mat> & fval,
                                               Mat & dx, Mat & dxt, Sym * initMat,
                                               Sym & moment )
{
    dx  = fval[0] - x_;
    dxt = dx;
    dxt.t();
    moment = w0*dx*dxt;
    dxt.t();
    
    if( initMat != 0 ){
        moment = moment + *initMat;
    }
    
    for (int i = 1; i <= 2*nx; i++) {
        dx  = fval[i] - x_;
        dxt = dx;
        dxt.t();
        moment = moment + w1*dx*dxt;
        dxt.t();
    }
}

TEMPLATE_HEADER
void UKF::computeCrossCorrelation( const Mat & x1, const Mat & x2,
                                                 const std::vector<Mat> & fval1, const std::vector<Mat> & fval2,
                                                 Mat & dx, Mat & dxt,
                                                 Mat & cc )
{
    dx  = fval1[0] - x1;
    dxt = fval2[0] - x2;
    dxt.t();
    cc = w0*dx*dxt;
    dxt.t();
    
    for (int i = 1; i <= 2*nx; i++) {
        dx  = fval1[i] - x1;
        dxt = fval2[i] - x2;
        dxt.t();
        cc = cc + w1*dx*dxt;
        dxt.t();
    }
    
}

TEMPLATE_HEADER
void UKF::operator()( double t_, const Mat & meas ){
    static Mat ut(x), xt(x.size(),0), zt(meas.size(),0), dx(x),dxt(x);
    static std::vector<Mat> fx(1+2*nx);
    static std::vector<Mat> hx(1+2*nx);
    double dt = t_ - t; t = t_;
    if( !setCholesky ){ init(); }
    
    // Compute initial sigma points
    computeSigmaPoints( x, ut );
    
    // Compute state prediction
    computeStatePrediction( dt, fx, xt );
    
    // Compute State Covariance prediction
    dx = sqrt(w0)*(fx[0]-xt);
    la::cholesky(Q, S);
    S.rankOneUpdate(dx);
    for (int i = 1; i <= 2*nx; i++) {
        dx = sqrt(w1)*(fx[i]-xt);
        S.rankOneUpdate(dx);
    }
    
    // Compute new sigma points
    computeSigmaPoints( xt, ut );
    
    // compute measurement prediction
    computeMeasPrediction( hx, zt );
    
    // compute measurement covariance
    compute2ndOrderMoment( zt, hx, dx, dxt, &R, Pzz );
    
    // compute cross correlation
    computeCrossCorrelation( xt, zt, fx, hx, dx, dxt, Pxz );
    
    // Compute kalman gain
    static Mat PzzInv;
    static Diag I(nz,nz,1);
    solve(Pzz,I,PzzInv);
    static Mat K;
    K = Pxz * PzzInv;
    
    // Compute corrected state estimate
    // and corrected covariance estimate
    x = xt + K*( meas - zt );
    static Mat M;
    M = K*Pzz;
    K.t();
    static Mat D;
    D = M*K;
    K.t();
    S.rankOneDowndate(D); // represents Pxx = Pxx - K*Pzz*K'
    
}

TEMPLATE_HEADER
const typename UKF::Mat & UKF::state() const{
    return x;
}

TEMPLATE_HEADER
const typename UKF::Sym & UKF::stateCov() const{
    return Pxx;
}

TEMPLATE_HEADER
double & UKF::stateCov(int i, int j){
    return Pxx(i,j);
}

TEMPLATE_HEADER
double & UKF::dynNoise(int i, int j){
    return Q(i,j);
}

TEMPLATE_HEADER
double & UKF::measNoise(int i, int j){
    return R(i,j);
}

}
}

#undef TEMPLATE_HEADER
#undef UKF

#endif /* UKF_Impl_h */
