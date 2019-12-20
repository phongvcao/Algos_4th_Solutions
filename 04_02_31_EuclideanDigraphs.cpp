//
// Created by Phong Cao on 2019-02-28.
//


#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <functional>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <list>
#include <forward_list>
#include <deque>
#include <queue>
#include <stack>
#include <iterator>
#include <utility>
#include <algorithm>
#include <memory>
#include <cctype>

//----<iostream>------------//
using std::cout;
using std::cin;
using std::endl;
using std::ostream;
using std::istream;

//----<sstream>-------------//
using std::ostringstream;
using std::istringstream;

//----<fstream>-------------//
using std::ofstream;
using std::ifstream;

//----<string>--------------//
using std::getline;
using std::string;
using std::to_string;
using std::stoi;
using std::stol;

//----<cmath>---------------//
using std::sqrt;
using std::pow;

//----<cstdlib>-------------//
using std::rand;
using std::srand;

//----<ctime>---------------//
using std::time;

//----<functional>----------//
using std::hash;

//----<vector>--------------//
using std::vector;          // Unordered Array

//----<map>-----------------//
using std::map;             // Ordered Map (Red-Black Tree)

//----<unordered_map>-------//
using std::unordered_map;   // HashMap (SeparateChainingHashST)

//----<set>-----------------//
using std::set;             // Ordered Set (Red-Black Tree)

//----<unordered_set>-------//
using std::unordered_set;   // HashSet (SeparateChainingHashST)

//----<list>----------------//
using std::list;            // Doubly-Linked List with size() ( O( 1 ) )

//----<forward_list>--------//
using std::forward_list;    // Singly-Linked List without size() function ( so O( N ) if we need to get size() )

//----<deque>---------------//
using std::deque;           // Vector of fixed-size Vectors: 1 fixed-size vector for each end of the deque

//----<queue>---------------//
using std::queue;           // Non-Iterable & Use std::deque as underlying data structure

//----<stack>---------------//
using std::stack;           // Non-Iterable & Use std::deque as underlying data structure

//----<iterator>------------//
using std::next;            // Return an advanced iter without changing original iter

//----<utility>-------------//
using std::pair;

//----<algorithm>-----------//
using std::fill;
using std::max;
using std::min;
using std::find;
using std::reverse;
using std::sort;

//----<memory>--------------//
using std::make_shared;
using std::shared_ptr;

//----<cctype>--------------//
using std::isalnum;
using std::isalpha;
using std::islower;
using std::isupper;
using std::isdigit;
using std::isspace;         // Check whether char is whitespace character (space, newline, tab, etc. )
using std::isblank;         // Check whether char is blank character ( space or tab )
using std::tolower;
using std::toupper;

//--------------------------//

class Point2D {
public:
    int x = 0;
    int y = 0;

    Point2D() {
        // default constructor
    }

    Point2D( int x, int y )
        : x( x ),
          y( y )
    {
        // not implemented
    }

    virtual ~Point2D() {
        // not implemented
    }

    friend bool operator ==( const Point2D& p1, const Point2D& p2 ) {
        return ( p1.x == p2.x ) && ( p1.y == p2.y );
    }

    friend bool operator !=( const Point2D& p1, const Point2D& p2) {
        return ! ( p1 == p2 );
    }
};

namespace std {
    template <>
    struct hash< Point2D > {
        size_t operator ()( const Point2D& p ) const {
            int hash = 17;
            hash = 31 * hash + std::hash< int >{}( p.x );
            hash = 31 * hash + std::hash< int >{}( p.y );
            return hash;
        }
    };
}

class Digraph {
private:

    int V = 0;
    int E = 0;
    vector< forward_list< int > > adj;
    unordered_map< Point2D, int > vertices;

public:

    Digraph( int V )
        : V( V ),
          adj( V )
    {
        // not implemented
    }

    virtual ~Digraph() {
        // not implemented
    }

    int getV() const {
        return V;
    }

    int getE() const {
        return E;
    }

    forward_list< int > getAdj( int v ) const {
        return adj[ v ];
    }

    void addEdge( int v, int w ) {
        adj[ v ].push_front( w );
        ++E;
    }

    void addVertex( const Point2D p ) {
        if ( vertices.find( p ) == vertices.end() ) {
            vertices.insert( pair( p, vertices.size() ) );
        }
    }

    int getIndex( const Point2D p ) {
        if ( vertices.find( p ) != vertices.end() ) {
            return vertices[ p ];
        }
        return -1;
    }

    string toString() const {
        string rv = "\ngraph:\n";
        for ( int v = 0; v < getV(); ++v ) {
            rv += "\n| v : " + to_string( v ) + " : ";
            for ( int w : getAdj( v ) ) {
                rv += to_string( w ) + ", ";
            }
            rv += " | ";
        }
        
        rv += "\nvertices:\n";
        for ( auto iter = vertices.begin(); iter != vertices.end(); ++iter ) {
            rv += "\n| x : " + to_string( iter->first.x ) + " , y : " + to_string( iter->first.y ) + " | ; i : " + to_string( iter->second );
        }
        return rv;
    }
};

int main( int argc, char ** argv ) {

    int graphArr[ 16 ][ 2 ] = {
            { 0, 5 },
            { 4, 3 },
            { 0, 1 },
            { 9, 12 },
            { 6, 4 },
            { 5, 4 },
            { 0, 2 },
            { 11, 12 },
            { 9, 10 },
            { 0, 6 },
            { 7, 8 },
            { 9, 11 },
            { 5, 3 },
            { 6, 7 },
            { 6, 9 },
            { 8, 9 }
    };

    Digraph dGraph( 13 );
    for ( int v = 0; v < 13; ++v ) {
        Point2D p( v, v );
        dGraph.addVertex( p );
    }

    for ( int i = 0; i < 16; ++i ) {
        dGraph.addEdge( graphArr[ i ][ 0 ], graphArr[ i ][ 1 ] );
    }

    cout << "DEBUG: dGraph: \n" << dGraph.toString() << endl;

    return 0;
}
