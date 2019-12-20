//
// Created by Phong Cao on 2019-02-02.
//


#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <map>
#include <queue>
#include <stack>
#include <algorithm>
#include <functional>

using std::cout;
using std::cin;
using std::endl;
using std::hash;
using std::string;
using std::to_string;
using std::vector;
using std::map;
using std::queue;
using std::stack;
using std::fill;
using std::make_shared;
using std::shared_ptr;

static const int HASH_TABLE_SIZE = 997;

class Point2D {
private:
    double x = 0;
    double y = 0;

public:
    Point2D( double x, double y )
        : x( x ),
          y( y )
    {
        // not implemented
    }

    virtual ~Point2D() {
        // not implemented
    }

    int hashCode() {
        size_t hash = 17;
        hash = ( 31 * hash + std::hash< double >{}( x ) ) % HASH_TABLE_SIZE;
        hash = ( 31 * hash + std::hash< double >{}( y ) ) % HASH_TABLE_SIZE;
        return hash;
    }
};

class Interval {
private:
    double low = 0;
    double high = 0;

public:
    Interval( double low, double high )
        : low( low ),
          high( high )
    {
        // not implemented
    }

    Interval() {
        // not implemented
    }

    virtual ~Interval() {
        // not implemented
    }

    int hashCode() {
        size_t hash = 17;
        hash = ( 31 * hash + std::hash< double >{}( low ) ) % HASH_TABLE_SIZE;
        hash = ( 31 * hash + std::hash< double >{}( high ) ) % HASH_TABLE_SIZE;
        return hash;
    }
};

class Interval2D {
private:
    Interval x;
    Interval y;

public:
    Interval2D( const Interval& x, const Interval& y ) {
        this->x = x;
        this->y = y;
    }

    virtual ~Interval2D() {
        // not implemented
    }

    int hashCode() {
        size_t hash = 17;
        hash = ( 31 * hash + x.hashCode() ) % HASH_TABLE_SIZE;
        hash = ( 31 * hash + y.hashCode() ) % HASH_TABLE_SIZE;
        return hash;
    }
};

class Date {
private:
    int month = 1;
    int day = 1;
    int year = 2018;

public:
    Date( int month, int day, int year )
        : month( month ),
          day( day ),
          year( year )
    {
        // not implemented
    }

    virtual ~Date() {
        // not implemented
    }

    int hashCode() {
        int R = 31;
        size_t hash = day;
        hash = ( hash * R + month ) % HASH_TABLE_SIZE;
        hash = ( hash * R + year ) % HASH_TABLE_SIZE;
        return hash;
    }
};

int main( int argc, char ** argv ) {
    Point2D point2D( 0, 1 );
    cout << point2D.hashCode() << endl;

    Interval x( 2, 3 );
    Interval y( 4, 5 );
    cout << x.hashCode() << endl;
    cout << y.hashCode() << endl;

    Interval2D interval2D( x, y );
    cout << interval2D.hashCode() << endl;

    Date date( 2, 2, 2019 );
    cout << date.hashCode() << endl;

    return 0;
}
