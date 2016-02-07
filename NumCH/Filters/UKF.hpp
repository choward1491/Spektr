//
//  UKF.hpp
//  NumCH
//
//  Created by Christian J Howard on 2/4/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//

#ifndef UKF_h
#define UKF_h

#include "Matrix.hpp"
#include "Cholesky.hpp"
#include <vector>

#define DebugUKF 1

namespace filter {
    
    template<class Dynamics, class Measure>
    class UnscentedKF {
    public:
        typedef la::SMat<double>    Sym;
        typedef la::Mat<double>     Mat;
        typedef la::LMat<double>    Lower;
        
        
        UnscentedKF();
        UnscentedKF( const Mat & x0 );
        ~UnscentedKF();
        
        
        void setInitState( const Mat & x0 );
        void operator()( double t_, const Mat & meas );
        const Mat & state() const;
        const Sym & stateCov() const;
        
        double & stateCov(int i, int j);
        double & stateNoise(int i, int j);
        double & measNoise(int i, int j);
        
        size_t numState() const { return nx; }
        size_t numMeas()  const { return nz; }
        
        void setCenterWeight( double w0_ );
        
        
        Dynamics f;
        Measure h;
        
    private:
        
        Sym Q;
        Sym R;
        
        Sym Pxx;
        std::vector<Mat> sigx;
        Sym Pzz;
        Mat Pxz;
        
        double t;
        Mat x;
        
        static const size_t nx = Dynamics::Nx;
        static const size_t nz = Measure::Nz;
        
        double w0,w1,q;
        
        
    };
    
    
    
    
        
    template<class D, class M>
    UnscentedKF<D,M>::UnscentedKF():Q(nx,nx),R(nz,nz),Pxx(nx,nx),Pzz(nz,nz),
                                    Pxz(nx,nz),sigx(1+2*nx),x(nx,1){
        for (int i = 0; i < nx; i++) { Q(i,i) = 1.0; Pxx(i,i) = 1.0; }
        for (int i = 0; i < nz; i++) { R(i,i) = 1.0; Pzz(i,i) = 1.0; }
        t = 0;
        setCenterWeight(0.3);
    }
    
    template<class D, class M>
    UnscentedKF<D,M>::UnscentedKF( const Mat & x0 ):Q(nx,nx),R(nz,nz),Pxx(nx,nx),Pzz(nz,nz),
                                                    Pxz(nx,nz),sigx(1+2*nx),x(x0){
        for (int i = 0; i < nx; i++) { Q(i,i) = 1.0; Pxx(i,i) = 1.0; }
        for (int i = 0; i < nz; i++) { R(i,i) = 1.0; Pzz(i,i) = 1.0; }
        t = 0;
        setCenterWeight(0.3);
    }
    
    template<class D, class M>
    void UnscentedKF<D,M>::setCenterWeight( double w0_ ){
        w0 = w0_;
        w1 = (1.0 - w0) / (2.0 * nx);
        q = 1.0 / sqrt(2.0*w1);
    }
    
    template<class D, class M>
    UnscentedKF<D,M>::~UnscentedKF(){
        
    }
    
    template<class D, class M>
    void UnscentedKF<D,M>::setInitState( const Mat & x0 ){
        x = x0;
    }
    
    template<class D1, class M1>
    void UnscentedKF<D1,M1>::operator()( double t_, const Mat & meas ){
        double dt = t_ - t; t = t_;
        Lower D;
        Mat ut(x), xt(x.size(),0), zt(meas.size(),0), dx(x),dxt(x);
        std::vector<Mat> fx(1+2*nx);
        std::vector<Mat> hx(1+2*nx);
        la::cholesky( Pxx, D );
        
        // Compute initial sigma points
        sigx[0] = x;
        for (int i = 1; i <= nx; i++) {
            D.getColumn(ut,i-1);
            int ind = 1 + 2*(i-1);
            sigx[ind]     = x + q*ut;
            sigx[ind+1]   = x - q*ut;
        }
        
        // Compute state prediction
        fx[0] = f(dt, sigx[0]);
        xt = w0*fx[0];
        for (int i = 1; i <= 2*nx; i++) {
            fx[i] = f(dt, sigx[i]);
            xt = xt + w1*fx[i];
        }
        
        
        // Compute State Covariance prediction
        dx = fx[0]-xt; dxt = dx;
        dxt.T();
        Pxx = Q + w0*dx*dxt;
        
        for (int i = 1; i <= 2*nx; i++) {
            dxt.T();
            dx = fx[i]-xt;
            dxt = dx; dxt.T();
            Pxx = Pxx + w1*dx*dxt;
        }
        
        
        // Compute new sigma points
        sigx[0] = xt;
        for (int i = 1; i <= nx; i++) {
            D.getColumn(ut,i-1);
            int ind = 1 + 2*(i-1);
            sigx[ind]     = xt + q*ut;
            sigx[ind+1]   = xt - q*ut;
        }
        
        // compute measurement prediction
        hx[0] = h(sigx[0]);
        zt = w0*hx[0];
        for (int i = 1; i <= 2*nx; i++) {
            hx[i] = h(sigx[i]);
            zt = zt + w1*hx[i];
        }
        
        // compute measurement covariance
        dxt.T();
        dx = zt - hx[0]; dxt = dx; dxt.T();
        Pzz = R + w0*dx*dxt;
        
        for (int i = 1; i <= 2*nx; i++) {
            dxt.T();
            dx = zt - hx[i];
            dxt = dx; dxt.T();
            Pzz = Pzz + w1*dx*dxt;
        }
        
        // compute cross correlation
        if( dxt.isTransposed()){ dxt.T(); }
        dx = fx[0]-xt;
        dxt = hx[0] - zt; dxt.T();
        Pxz = w0*dx*dxt;
        for (int i = 1; i <= 2*nx; i++) {
            dxt.T();
            dx = fx[i]-xt;
            dxt = hx[i] - zt; dxt.T();
            Pxz = Pxz + w1*dx*dxt;
        }
        
        
        // Compute kalman gain
        Mat PzzInv;
        Diag I(nz,nz,1);
        solve(Pzz,I,PzzInv);
        Mat It = Pzz*PzzInv;
        Mat K = Pxz * PzzInv;
        
        // Compute state estimate and covariance estimate
        x = xt + K*( meas - zt );
        Mat M = K*Pzz; K.T();
        Pxx = Pxx - M*K;
        
    }
    
    template<class D, class M>
    const Mat & UnscentedKF<D,M>::state() const{
        return x;
    }
    
    template<class D, class M>
    const Sym & UnscentedKF<D,M>::stateCov() const{
        return Pxx;
    }
    
    template<class D, class M>
    double & UnscentedKF<D,M>::stateCov(int i, int j){
        return Pxx(i,j);
    }
    
    template<class D, class M>
    double & UnscentedKF<D,M>::stateNoise(int i, int j){
        return Q(i,j);
    }
    
    template<class D, class M>
    double & UnscentedKF<D,M>::measNoise(int i, int j){
        return R(i,j);
    }
    
    
}



#endif /* UKF_h */