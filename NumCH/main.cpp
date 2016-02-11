//
//  main.cpp
//  NumCH
//
//  Created by Christian J Howard on 8/8/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#include "Matrix.hpp"
#include "Timer.hpp"
#include "RandomNumberGenerator.hpp"

typedef la::SMat<double>    Sym;
typedef la::Mat<double>     Mat;
typedef la::SpMat<double>   SMat;
typedef la::LMat<double>    LMat;
typedef la::DMat<double>    Diag;

#include "GradientBase.hpp"
#include "ConstantStep.hpp"
#include "Rosenbrock.hpp"
#include "Parabola2D.hpp"
#include "TestMPSO1.hpp"
#include "LogisticRegression.hpp"
#include "RBF_Poly.hpp"
#include "FileObject.hpp"

typedef opt::gradient<ml::LogisticRegression<ml::rbf::Poly>, opt::ConstantStep<ml::LogisticRegression<ml::rbf::Poly> > > gradient;

struct Setup {
    double xmin, xmax, ymin,ymax;
    int N;
};

std::vector<Mat> createCenters(Setup setup){
    double dx = (setup.xmax - setup.xmin) / static_cast<double>(setup.N-1);
    double dy = (setup.ymax - setup.ymin) / static_cast<double>(setup.N-1);
    std::vector<Mat> centers;
    
    Mat pt(2,1);
    for (int i = 0; i < setup.N; i++) {
        pt(0) = setup.xmin + dx*i;
        for (int j = 0; j < setup.N; j++) {
            pt(1) = setup.ymin + dy*j;
            centers.push_back(pt);
        }
    }
    return centers;
}

void genData(Setup setup, std::vector<Mat>& x, std::vector<double> & y ){
    double dx = (setup.xmax - setup.xmin) / static_cast<double>(setup.N-1);
    double dy = (setup.ymax - setup.ymin) / static_cast<double>(setup.N-1);
    x.resize(setup.N*setup.N);
    y.resize(setup.N*setup.N);
    
    Mat pt(2,1);
    Mat c(2,1);
    c(0) = (setup.xmin + setup.xmax)*0.5;
    c(1) = (setup.ymin + setup.ymax)*0.5;
    Mat r;
    
    int k = 0;
    for (int i = 0; i < setup.N; i++) {
        pt(0) = setup.xmin + dx*i;
        for (int j = 0; j < setup.N; j++) {
            pt(1) = setup.ymin + dy*j;
            x[k] = pt;
            r = pt - c;
            double rmag = sqrt((r(0)*r(0) + r(1)*r(1)));
            if( (rmag < 0.5 && rmag > 0.3) || (rmag < 0.2 && rmag > 0.1) ){
                y[k] = 1.0;
            }else{
                y[k] = 0.0;
            }
            k++;
        }
    }
}



int main(int argc, const char * argv[]) {
    
    Setup setup;
    setup.xmin = -1;
    setup.xmax = 1;
    setup.ymin = -1;
    setup.ymax = 1;
    setup.N = 50;
    
    std::vector<Mat> x;
    std::vector<double> y;
    
    genData(setup, x, y );
    
    setup.N = 20;
    gradient grad;
    grad.setMaxIter(50);
    grad.setMomentumCoef(0.6);
    grad.setTolerance(1e-3);
    grad.step.setStepSize(1000);
    grad.func.setPenaltyForZeroOutput(10.0);
    grad.func.setScalarOffset(-5);
    grad.func.setData(&x, &y);
    grad.func.basis.maxr = 0.2;
    grad.func.basis.centers = createCenters(setup);
    
    Mat guess(grad.func.numDims(),1,0);
    
    grad.setGuess(guess);
    
    Timer timer;
    timer.start();
    
    grad.init();
    grad.solve();
    grad.soln().print();
    
    timer.stop();
    
    FileObject file("/Users/christianjhoward/Documents/MATLAB/ClassificationTest/data.csv", FileObject::AccessMode::Write);
    
    for (int i = 0; i < x.size(); i++) {
        double g = grad.func.sigmoid( grad.func.s() + grad.func.basis.evaluate(x[i], grad.soln()));
        if (g > 0.5) {
            g = 1.0;
        }else{
            g = 0.0;
        }
        fprintf(file.ref(), "%lf, %lf, %lf\n",x[i](0), x[i](1), g);
    }
    
    file.openFile("/Users/christianjhoward/Documents/MATLAB/ClassificationTest/truth.csv", FileObject::AccessMode::Write);
    for (int i = 0; i < x.size(); i++) {
        fprintf(file.ref(), "%lf, %lf, %lf\n",x[i](0), x[i](1), y[i]);
    }
    
    
    printf("Time was %lf\n",timer.getDuration());
    
    
    return 0;
}

