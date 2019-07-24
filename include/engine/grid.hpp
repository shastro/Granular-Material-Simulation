// Contains Implementation of a Spatial Hash //
//                                           //
// Classes                                   //
//  -Bucket                                  //
//  -Spatial Hash                            //
//                                           //
///////////////////////////////////////////////

#ifndef GRID_H
#define GRID_H

#include "engine.hpp"
#include "ball.hpp"
#include <deque>
#include <iterator>

////////////
// Bucket //
////////////

class Bucket
{

private:
    std::vector<Ball> Balls;
    int index;
    
public:
    int length;
    // Bucket(Bucket&& other) = default;
    // Bucket& operator=(Bucket&& other) = default;

public:

    void fill(std::vector <Ball>& iBalls);
    void insert(Ball &ball);
    std::vector<Ball> *get();
    void clear();
};


//////////////////
// Spatial Hash //
//////////////////

class SpatialHash
{
private:
    Bucket *buckets;
    std::vector<Ball> *ballqueue;
    int m_width;
    int m_height;
    int m_cellsize;
    int nBuckets;

public:
    SpatialHash(int width, int height, int cellsize)
    {
        m_width    = width;
        m_height   = height;
        m_cellsize = cellsize;

        //Determine number of buckets needed

        int cols = m_width  / m_cellsize;
        int rows = m_height / m_cellsize;

        nBuckets = (cols + 1) * (rows + 1);
        buckets = new Bucket[nBuckets];
        ballqueue = new std::vector<Ball>;
        ballqueue->reserve(sizeof(Ball) * 30);

        LOG("CS: ", m_cellsize)
        LOG("nBuckets: ", nBuckets)
    }
    ~SpatialHash();

    // Constructs a spatial hash given a vector of particles
    void build(std::vector<Ball>& vecBalls);

    //Returns a list of objects that are nearby.
    /*Nearby is defined by all objects in the cell of the query
     as well any cells touched by the query given the radius */
    std::vector<Ball>* query(Ball &ball);

    // Returns the id of the Bucket that contains a point
    int pointQuery(float x, float y);

    //Inserts a Ball into its appropriate buckets
    void insert(Ball &ball);


    void clear();


};




#endif