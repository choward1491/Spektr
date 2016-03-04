//
//  main.cpp
//  NumCH
//
//  Created by Christian J Howard on 8/8/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#include "Matrix.hpp"
#include "Solver.hpp"

typedef la::SMat<double>    Sym;
typedef la::Mat<double>     Mat;
typedef la::SpMat<double>   SMat;
typedef la::LMat<double>    LMat;
typedef la::DMat<double>    Diag;
typedef la::TDMat<double>   TDiag;

#include "KDTree.hpp"

struct Point {
    typedef double Type;
    double x_[2];
    Point(){}
    Point(double x, double y){ x_[0] = x; x_[1] = y; }
    double operator[](int i){ return x_[i]; }
};

typedef KDTree<2, Point, Point> NNTree;



int main(int argc, const char * argv[]) {
    
    
    std::vector<Point> pts;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            pts.push_back(Point(i,j));
        }
    }
    
    NNTree tree(pts,pts);
    NNTree::NNSet soln;
    Point center(5,5);
    tree.findNeighborsWithinRegion(center, 2, soln);
    
    for (int i = 0; i < soln.size(); i++) {
        NNTree::Node pt = soln[i];
        printf(" pt = (%lf,%lf)\n",pt.data[0],pt.data[1]);
    }
    
    
    
    return 0;
}

