//
// Created by Phong Cao on 2019-02-23.
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

//----<memory>--------------//
using std::make_shared;
using std::shared_ptr;

//--------------------------//

class Digraph {
private:

    int V = 0;
    int E = 0;
    vector< forward_list< int > > adj;

public:

    Digraph( int V )
        : V( V )
    {
        adj.resize( V );
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

    string toString() const {
        string rv = "\n";
        for ( int v = 0; v < V; ++v ) {
            rv += "\n| v : " + to_string( v ) + " : ";
            for ( int w : getAdj( v ) ) {
                rv += to_string( w ) + ", ";
            }
            rv += " | ";
        }
        return rv;
    }

    forward_list< int > getAdj( int v ) const {
        return adj[ v ];
    }

    void addEdge( int v, int w ) {
        adj[ v ].push_front( w );
        ++E;
    }

    Digraph reverse() const {
        Digraph R( V );
        for ( int v = 0; v < V; ++v ) {
            for ( int w : getAdj( v ) ) {
                R.addEdge( w, v );
            }
        }
        return R;
    }
};

class Degrees {
private:

    vector< int > inDegrees;
    vector< int > outDegrees;
    forward_list< int > sources;
    forward_list< int > sinks;
    bool isMap= true;

public:

    Degrees( const Digraph& G ) {
        inDegrees.resize( G.getV() );
        outDegrees.resize( G.getV() );
        for ( int v = 0; v < G.getV(); ++v ) {
            int outDeg = 0;
            for ( int w : G.getAdj( v ) ) {
                ++inDegrees[ w ];
                ++outDeg;
            }
            outDegrees[ v ] = outDeg;
            if ( outDegrees[ v ] == 0 ) {
                sinks.push_front( v );
            }

            if ( outDegrees[ v ] != 1 ) {
                isMap = false;
            }
        }

        for ( int v = 0; v < inDegrees.size(); ++v ) {
            if ( inDegrees[ v ] == 0 ) {
                sources.push_front( v );
            }
        }
    }

    virtual ~Degrees() {
        // not implemented
    }

    int getInDegrees( int v ) const {
        return inDegrees[ v ];
    }

    int getOutDegrees( int v ) const {
        return outDegrees[ v ];
    }

    forward_list< int > getSources() const {
        return sources;
    }

    forward_list< int > getSinks() const {
        return sinks;
    }

    bool getIsMap() const {
        return isMap;
    }

    string toString() const {
        string rv = "\ninDegrees:\n";
        for ( int v = 0; v < inDegrees.size(); ++v ) {
            rv += "\n| v : " + to_string( v ) + " : " + to_string( inDegrees[ v ] ) + " | , ";
        }
        
        rv += "\noutDegrees:\n";
        for ( int v = 0; v < outDegrees.size(); ++v ) {
            rv += "\n| v : " + to_string( v ) + " : " + to_string( outDegrees[ v ] ) + " | , ";
        }

        rv += "\nsources:\n";
        for ( int v : sources ) {
            rv += "\n| v : " + to_string( v ) + " | , ";
        }

        rv += "\nsinks:\n";
        for ( int v : sinks ) {
            rv += "\n| v : " + to_string( v ) + " | , ";
        }

        rv += "\nisMap:\n";
        rv += to_string( isMap );
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
            { 9, 6 },
            { 8, 9 }
    };

    Digraph dGraph( 13 );

    for ( int i = 0; i < 16; ++i ) {
        dGraph.addEdge( graphArr[ i ][ 0 ], graphArr[ i ][ 1 ] );
    }

    cout << "DEBUG: dGraph: \n" << dGraph.toString() << endl;
    cout << "DEBUG: dGraph.reverse(): \n" << dGraph.reverse().toString() << endl;

    Degrees degrees( dGraph );
    cout << "DEBUG: degrees: \n" << degrees.toString() << endl;

    return 0;
}
