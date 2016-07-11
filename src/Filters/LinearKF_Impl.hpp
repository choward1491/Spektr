//
//  LinearKF_Impl.hpp
//  Spektr
//
//  Created by Christian J Howard on 7/10/16.
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

#ifndef LinearKF_Impl_h
#define LinearKF_Impl_h

#include "LinearKF.hpp"

#define TEMPLATE_HEADER template<class D1, class M1>
#define KF LinearKF<D1,M1>

namespace spektr {
    namespace filter {
        
        
        TEMPLATE_HEADER
        void KF::init(){
            la::cholesky( Pxx, S );
            setCholesky = true;
        }
        
        
        TEMPLATE_HEADER
        KF::LinearKF():Q(nx,nx),R(nz,nz),Pxx(nx,nx),Pzz(nz,nz),
        Pxz(nx,nz),sigx(1+2*nx),x(nx,1),setCholesky(false){
            for (int i = 0; i < nx; i++) { Q(i,i) = 1.0; Pxx(i,i) = 1.0; }
            for (int i = 0; i < nz; i++) { R(i,i) = 1.0; Pzz(i,i) = 1.0; }
            t = 0;
        }
        
        TEMPLATE_HEADER
        KF::LinearKF( const Mat & x0 ):Q(nx,nx),R(nz,nz),Pxx(nx,nx),Pzz(nz,nz),
        Pxz(nx,nz),sigx(1+2*nx),x(x0),setCholesky(false){
            for (int i = 0; i < nx; i++) { Q(i,i) = 1.0; Pxx(i,i) = 1.0; }
            for (int i = 0; i < nz; i++) { R(i,i) = 1.0; Pzz(i,i) = 1.0; }
            t = 0;
        }
        
        TEMPLATE_HEADER
        KF::~LinearKF(){
            
        }
        
        TEMPLATE_HEADER
        void KF::setInitState( const Mat & x0 ){
            x = x0;
        }
        
        TEMPLATE_HEADER
        void KF::computeStatePrediction( double dt, Mat & xt ){
            xt = f.A(dt)*x;
        }
        
        TEMPLATE_HEADER
        void KF::computeMeasPrediction( const Mat & xt, Mat & zt ){
            zt = h.H()*xt;
        }
        
        TEMPLATE_HEADER
        void KF::operator()( double t_, const Mat & meas ){
            static Mat ut(x), xt(x.size(),0), zt(meas.size(),0), dx(x),dxt(x);
            static std::vector<Mat> fx(1+2*nx);
            static std::vector<Mat> hx(1+2*nx);
            double dt = t_ - t; t = t_;
            if( !setCholesky ){ init(); }
            
            // Compute state prediction
            computeStatePrediction( dt, xt );
            
            // Compute State Covariance prediction
            static Mat F = f.A(dt);
            static Mat Ft = F;
            if( !Ft.isTranposed() ){ Ft.t(); }
            Pxx = Q + F*Pxx*Ft;
            
            // compute measurement prediction
            computeMeasPrediction( xt, zt );
            
            // compute measurement covariance
            static Mat H = h.H();
            static Mat Ht = H;
            if( !Ht.isTranposed() ){ Ht.t(); }
            Pzz = R + H*Pxx*Ht;
            
            // Compute kalman gain
            static Mat PzzInv;
            static Diag I(nz,nz,1);
            solve(Pzz,I,PzzInv);
            static Mat K;
            K = Pxx * Ht * PzzInv;
            
            // Compute corrected state estimate
            // and corrected covariance estimate
            x = xt + K*( meas - zt );
            static Mat M;
            M = K*Pzz;
            K.t();
            Pxx = Pxx - M*K; // represents Pxx = Pxx - K*Pzz*K'
            K.t();
            
        }
        
        TEMPLATE_HEADER
        const typename KF::Mat & KF::state() const{
            return x;
        }
        
        TEMPLATE_HEADER
        const typename KF::Sym & KF::stateCov() const{
            return Pxx;
        }
        
        TEMPLATE_HEADER
        double & KF::stateCov(int i, int j){
            return Pxx(i,j);
        }
        
        TEMPLATE_HEADER
        double & KF::dynNoise(int i, int j){
            return Q(i,j);
        }
        
        TEMPLATE_HEADER
        double & KF::measNoise(int i, int j){
            return R(i,j);
        }
        
    }
}

#undef TEMPLATE_HEADER
#undef KF

#endif /* LinearKF_Impl_h */
