//
// Created by Phong Cao on 2019-02-15.
//

#include <iostream>
#include <sstream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <string>
#include <memory>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <deque>
#include <queue>
#include <stack>
#include <list>
#include <forward_list>
#include <algorithm>
#include <iterator>
#include <functional>

using std::cout;
using std::cin;
using std::ostream;
using std::istream;
using std::ostringstream;
using std::sqrt;
using std::pow;
using std::rand;
using std::srand;
using std::time;
using std::endl;
using std::hash;
using std::string;
using std::to_string;
using std::stoi;
using std::stol;
using std::vector;           // Unordered Array
using std::map;              // Ordered Map (Red-Black Tree)
using std::unordered_map;    // HashMap (SeparateChainingHashST)
using std::set;              // Ordered Set (Red-Black Tree)
using std::unordered_set;    // HashSet (SeparateChainingHashST)
using std::pair;
using std::list;             // Doubly-Linked List with size() ( O( 1 ) )
using std::forward_list;     // Singly-Linked List without size() function ( so O( N ) if we need to get size() )
using std::deque;            // Vector of fixed-size Vectors: 1 fixed-size vector for each end of the deque
using std::queue;            // Non-Iterable & Use std::deque as underlying data structure
using std::stack;            // Non-Iterable & Use std::deque as underlying data structure
using std::next;             // Return an advanced iter without changing original iter
using std::fill;
using std::max;
using std::min;
using std::find;
using std::make_shared;
using std::shared_ptr;

class Graph {
private:

    vector< forward_list< int > > adj;
    int V = 0;
    int E = 0;

public:

    Graph( int V )
            : V( V )
    {
        adj.resize( V );
    }

    virtual ~Graph() {
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

    static int degree( const Graph& G, int v ) {
        int deg = 0;
        for ( int w : G.getAdj( v ) ) {
            ++deg;
        }
        return deg;
    }

    void addEdge( int v, int w ) {
        adj[ v ].push_front( w );
        adj[ w ].push_front( v );
        ++E;
    }

    static int maxDegree( const Graph& G ) {
        int maxDeg = 0;
        for ( int v = 0; v < G.getV(); ++v ) {
            int deg = degree( G, v );
            if ( maxDeg < deg ) {
                maxDeg = deg;
            }
        }
        return maxDeg;
    }

    static int avgDegree( const Graph& G ) {
        return 2 * G.getE() / G.getV();
    }

    static int numSelfLoops( const Graph& G ) {
        int count = 0;
        for ( int v = 0; v < G.getV(); ++v ) {
            for ( int w : G.getAdj( v ) ) {
                if ( v == w ) {
                    ++count;
                }
            }
        }
        return count / 2;
    }
};

class GraphProperties {
private:

    vector< bool > marked;
    vector< int > length;
    vector< int > eccentricity;
    int diameter = -1;
    int radius = -1;
    int center = -1;

public:

    GraphProperties( const Graph& G ) {
        marked.resize( G.getV() );
        eccentricity.resize( G.getV() );
        length.resize( G.getV() );
        bfs( G );
    }

    virtual ~GraphProperties() {
        // not implemented
    }

    void bfs( const Graph& G ) {
        for ( int v = 0; v < G.getV(); ++v ) {
            fill( marked.begin(), marked.end(), false );
            fill( length.begin(), length.end(), 0 );
            marked[ v ] = true;
            queue< int > q;
            q.push( v );
            int vEcc = -1;

            while ( ! q.empty() ) {
                int w = q.front();
                q.pop();
                for ( int x : G.getAdj( w ) ) {
                    if ( ! marked[ x ] ) {
                        marked[ x ] = true;
                        length[ x ] = length[ w ] + 1;
                        if ( length[ x ] > vEcc ) {
                            vEcc = length[ x ];
                        }
                        q.push( x );
                    }
                }
            }
            eccentricity[ v ] = vEcc;
        }

        for ( int i = 0; i < eccentricity.size(); ++i ) {
            if ( diameter == -1 || diameter < eccentricity[ i ] ) {
                diameter = eccentricity[ i ];
            }

            if ( radius == -1 || radius > eccentricity[ i ] ) {
                radius = eccentricity[ i ];
                center = i;
            }
        }
    }

    int getEccentricity( int v ) const {
        return eccentricity[ v ];
    }

    int getDiameter() const {
        return diameter;
    }

    int getRadius() const {
        return radius;
    }

    int getCenter() const {
        return center;
    }

    string toString() const {
        string rv = "\n";
        for ( int i = 0; i < eccentricity.size(); ++i ) {
            rv += "\n| i : " + to_string( i ) + " : " + to_string( eccentricity[ i ] ) + " | ";
        }
        return rv;
    }
};

int main( int argc, char ** argv ) {
    /* int graphArr[ 16 ][ 2 ] = {
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
            { 7, 9 },
            { 8, 9 }
    };

    Graph graph( 13 );
    for ( int i = 0; i < 16; ++i ) {
        graph.addEdge( graphArr[ i ][ 0 ], graphArr[ i ][ 1 ] );
    } */

    int graphArr[ 10 ][ 2 ] = {
            { 0, 1 },
            { 1, 2 },
            { 2, 3 },
            { 3, 4 },
            { 4, 5 },
            { 5, 6 },
            { 6, 7 },
            { 7, 8 },
            { 8, 9 },
            { 9, 10 }
    };

    Graph graph( 11 );
    for ( int i = 0; i < 10; ++i ) {
        graph.addEdge( graphArr[ i ][ 0 ], graphArr[ i ][ 1 ] );
    }
    cout << "DEBUG: graph: \n" << graph.toString() << endl;

    GraphProperties graphPP( graph );
    cout << "DEBUG: graphPP: \n" << graphPP.toString() << endl;
    cout << "DEBUG: graphPP.getDiameter(): \n" << graphPP.getDiameter() << endl;
    cout << "DEBUG: graphPP.getRadius(): \n" << graphPP.getRadius() << endl;
    cout << "DEBUG: graphPP.getCenter(): \n" << graphPP.getCenter() << endl;


    return 0;
}
