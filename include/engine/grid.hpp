// Contains Implementation of a Spatial Hash //
//                                           //
// Classes                                   //                                //
//  -Spatial Hash                            //
//                                           //
///////////////////////////////////////////////

#ifndef GRID_H
#define GRID_H

// #include "engine.hpp"
#include "ball.hpp"
#include <deque>
#include <iterator>
#include <list>


//////////////////
// Spatial Hash //
//////////////////
template<typename T>
class SpatialHash
{
private:

    std::vector<std::list<T*>> *table;

    int m_width;
    int m_height;
    int m_cellsize;
    int m_particleCount;
    int nBuckets;

    bool (*detectCollision)(T *a, T *b);
    
    void (*applyCollision)(T *a, T *b);

    void (*updateType)(T *a);

public:
    SpatialHash(int width, int height, int cellsize);
    ~SpatialHash();

    //Directives High-Level
    void build(const std::vector<T*>& vecParticles);
    void clear();
    void update(double time_delta);
    void collidePairs();
    void print();

    //Directives Low-Level
    int pointHash(float x, float y);
    void insert(T *particle);


    //Setters
    void attach_DetectCollision( bool (*collide)(T *a, T *b));
    void attach_ApplyCollision(void (*resolve)(T *a, T *b));
    void attach_UpdateType(void (*update)(T *a));


};




#endif