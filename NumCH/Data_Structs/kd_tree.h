//
//  The MIT License (MIT)
//  Copyright © 2016 Christian Howard. All rights reserved.
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


#ifndef _kdtree_h_
#define _kdtree_h_


#include "heap.h"
#include "L2Norm.h"



/*!
 * This is a structure for storing data within
 * the KD Tree
 *
 * \params S This represents the point you are using
 * \params D This represents the data you are storing
 * \returns None
 */
template< class S, class D>
struct KDNode{
		S point;
		D data;
};






/*!
 * This is a templated class for use in efficient nearest neighbor
 * and nearest neighborhood searches for a K dimensional set of points
 *
 * \params K This is the number of dimensions your
 *           coordinate has within it
 * \params T This is the numeric type for the components of the vector
 *           that represents the key for this structure
 * \params S This is the vector type that you are using.
 *           For example, this could be a Point2D, which has an x and y value
 *           that can be referenced using point[0] (for x) and point[1] (for y)
 * \params D This is the data that will be stored at a given point in the kdtree
 * \returns None
 */
template< int K, class T, class S, class D >
class KDTree {

public:

    /*!
     * This method is the null constructor
     * for a KD Tree
     *
     * \params None
     * \returns None
     */
	KDTree();
    
    
    /*!
     * This is a constructor for the KD Tree
     * that takes an input dynamic array for the
     * coordinates and data
     *
     * \params pts      This is the array of coordinates
     * \params data     This is the array of data associated with each coordinate
     * \params num_pts  This variable is the number of points being input into the tree
     * \returns New KD Tree
     */
	KDTree( const S* pts, const D* data , int num_pts );
    
    
    
    
    /*!
     * This is a constructor that takes input
     * vectors that store the points and data
     * and builds the KD Tree based on that
     *
     * \params  pts Vector input with the coordinates
     * \params  data Vector input with the data for each coordinate
     * \returns New KD Tree
     */
    KDTree( const vector<S> & pts, const vector<D> & data );
    
    /*!
     * Destructor for KD Tree
     *
     */
	~KDTree();
    
    
    /*!
     * This method is for obtaining the Nearest N Neighbors from an input point
     *
     * \params pt Input point you want to find nearest neighbors to
     * \params numberOfNeighbors The maximum number of neighbors to be found near to 'pt'
     * \params soln This is a min heap that has each point and data pair that are
     *              found to be nearest neighbors to 'pt'. The min heap key is the distance
     *              from 'pt' to the neighbor point based on the distance measure.
     *              This variable is an output.
     */
	void findNearestNeighbors( S & pt, int numberOfneighbors , MinHeap<T, KDNode<S,D> > & soln );
    
    
    /*!
     * This method is for obtaining the Nearest Neighbors within a
     * particular distance from the pt, based on the distances found
     * using the assigned distance measure
     *
     * \params pt Input point you want to find nearest neighbors to
     * \params neighborhoodSize The maximum distance from 'pt' a neighbor can be
     *                          and still be added to the resulting solution output
     * \params soln This is a min heap that has each point and data pair that are
     *              found to be nearest neighbors to 'pt'. The min heap key is the distance
     *              from 'pt' to the neighbor point based on the distance measure
     *              This variable is an output
     */
    void findNeighborsWithinRegion( S & pt, T neighborhoodSize, MinHeap<T, KDNode<S,D> > & soln );
    
    
    /*!
     * This method assigns the distance measure the kd tree will use
     *
     * \params dm This is the distance measure function that will be used
     *            to find nearest neighbors. Recommends that this pointer
     *            actually be pointing to a dynamically allocated instance
     *            of the function
     */
	void assignDistanceMeasurement( KDFunction<K, S, T>* dm );
    
    
    /*!
     * This method updates the data to the new set.
     * Note that this method does not setup the kd treess
     *
     * \params pts The coordinate points in the set as a pointer to an array
     * \params data The data associated with each coordinate, as a pointer to an array
     * \params num_pts The number of coordinates being inputted
     * \returns None
     */
	void setData( const S * pts, const D* data , int num_pts );
    
    
    
    /*!
     * This method updates the data to the new set.
     * Note that this method does not setup the kd treess
     *
     * \params pts The coordinate points in the set as a vector
     * \params data The data associated with each coordinate, as a vector
     * \returns None
     */
    void setVectorData( const vector<S> & pts, const vector<D> & data );
    
    
    /*!
     * A method that organizes the kd tree data set so
     * that it can easily be used to do nearest neighbor searches.
     * This method expects that the data set has been inputted 
     * already and just needs to be changed to the appropriate structure
     *
     *
     * \params None
     * \returns None
     */
    void setup_kdtree();
    
    
    /*!
     * Array-like input to access the tree data
     *
     * \params index An integer >= 0 used to grab data at location index in the tree array
     * \returns A KDNode with the associated coordinate and data for a given index
     */
    KDNode<S,D> & operator[](int index) const { return tree[index]; }
    
    
    /*!
     * This method returns the number of points in the kd tree
     *
     * \params None
     * \returns Returns number of points in the kd tree
     */
    int size() const { return npts; }

private:

	KDNode<S,D>* tree;
	int npts;

    
    //
    // Pointer to the distance measure
    //
	KDFunction<K, S, T>* dist_measurement;


    //
    // method to split the data by the median.
    // this is used to efficiently build the data
    // into the format needed for the kd tree to
    // do its nearest neighbor searches
    //
	void splitDataByMedian( int ns, int ne , int dim);
	
    
    //
    // Recursive helper function to do the nearest N neighbor search
    //
	void findNN( int li, int ri, S & pt, int dim, MaxHeap<T, KDNode<S,D> >  &neighbors );
    
    //
    // Recursive helper function to do the search for all neighbors within a distance
    // from the input point
    //
    void findWithin( int li, int ri, S & pt, int dim, T neighborhoodThresh, MaxHeap<T, KDNode<S,D> >  & neighbors );

};





#ifndef _kdtree_cpp_
#include "kdtree.cpp"
#endif







#endif