//
// Created by Phong Cao on 2019-02-17.
//

#include <iostream>
#include <sstream>
#include <fstream>
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
using std::istringstream;
using std::ofstream;
using std::ifstream;
using std::getline;
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

    int V = 0;
    int E = 0;
    vector< forward_list< int > > adj;

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
        string rv = "\nV : " + to_string( V ) + " ; E : " + to_string( E ) + " ; adj : \n";
        for ( int v = 0; v < V; ++v ) {
            rv += "\n| v : " + to_string( v ) + " : ";
            for ( int w : adj[ v ] ) {
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
        adj[ w ].push_front( v );
        ++E;
    }

    static int degree( const Graph& G, int v ) {
        int deg = 0;
        for ( int w : G.getAdj( v ) ) {
            ++deg;
        }
        return deg;
    }

    static int maxDeg( const Graph& G ) {
        int maxDeg = 0;
        for ( int v = 0; v < G.getV(); ++v ) {
            int deg = degree( G, v );
            if ( maxDeg < deg ) {
                maxDeg = deg;
            }
        }
        return maxDeg;
    }

    static int avgDeg( const Graph& G ) {
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

// Eulerian Cycle:
// 1. All vertices with non-zero degree are connected
// 2. All vertices have even degree
int main( int argc, char ** argv ) {
    int graph1Arr[ 15 ][ 2 ] {
            { 0, 1 },
            { 0, 2 },
            { 0, 3 },
            { 1, 3 },
            { 1, 4 },
            { 2, 5 },
            { 2, 9 },
            { 3, 6 },
            { 4, 7 },
            { 4, 8 },
            { 5, 8 },
            { 5, 9 },
            { 6, 7 },
            { 6, 9 },
            { 7, 8 },
    };
    Graph graph1( 15 );
    for ( int i = 0; i < 15; ++i ) {
        graph1.addEdge( graph1Arr[ i ][ 0 ], graph1Arr[ i ][ 1 ] );
    }

    bool graph1EulerianCycle = true;
    for ( int v = 0; v < graph1.getV(); ++v ) {
        if ( Graph::degree( graph1, v ) % 2 != 0 ) {
            graph1EulerianCycle = false;
            break;
        }
    }
    if ( ! graph1EulerianCycle ) {
        cout << "DEBUG: graph1 DOES NOT HAVE Eulerian Cycle!!!" << endl;
    } else {
        cout << "DEBUG: graph1 DOES HAVE Eulerian Cycle!!!" << endl;
    }

    int graph2Arr[ 15 ][ 2 ] {
            { 0, 1 },
            { 0, 2 },
            { 0, 3 },
            { 1, 3 },
            { 0, 3 },
            { 2, 5 },
            { 5, 6 },
            { 3, 6 },
            { 4, 7 },
            { 4, 8 },
            { 5, 8 },
            { 5, 9 },
            { 6, 7 },
            { 6, 9 },
            { 8, 8 },
    };
    Graph graph2( 15 );
    for ( int i = 0; i < 15; ++i ) {
        graph2.addEdge( graph2Arr[ i ][ 0 ], graph2Arr[ i ][ 1 ] );
    }

    bool graph2EulerianCycle = true;
    for ( int v = 0; v < graph2.getV(); ++v ) {
        if ( Graph::degree( graph2, v ) % 2 != 0 ) {
            graph2EulerianCycle = false;
            break;
        }
    }
    if ( ! graph2EulerianCycle ) {
        cout << "DEBUG: graph2 DOES NOT have Eulerian Cycle!!!" << endl;
    } else {
        cout << "DEBUG: graph2 DOES HAVE Eulerian Cycle!!!" << endl;
    }

    int graph3Arr[ 15 ][ 2 ] {
            { 0, 1 },
            { 1, 2 },
            { 1, 3 },
            { 0, 3 },
            { 0, 4 },
            { 2, 5 },
            { 5, 6 },
            { 3, 6 },
            { 4, 7 },
            { 4, 8 },
            { 5, 8 },
            { 5, 9 },
            { 6, 7 },
            { 6, 9 },
            { 7, 8 },
    };
    Graph graph3( 15 );
    for ( int i = 0; i < 15; ++i ) {
        graph3.addEdge( graph3Arr[ i ][ 0 ], graph3Arr[ i ][ 1 ] );
    }

    bool graph3EulerianCycle = true;
    for ( int v = 0; v < graph3.getV(); ++v ) {
        if ( Graph::degree( graph3, v ) % 2 != 0 ) {
            graph3EulerianCycle = false;
            break;
        }
    }
    if ( ! graph3EulerianCycle ) {
        cout << "DEBUG: graph3 DOES NOT HAVE Eulerian Cycle!!!" << endl;
    } else {
        cout << "DEBUG: graph3 DOES HAVE Eulerian Cycle!!!" << endl;
    }

    int graph4Arr[ 15 ][ 2 ] {
            { 4, 1 },
            { 7, 9 },
            { 6, 2 },
            { 7, 3 },
            { 5, 0 },
            { 0, 2 },
            { 0, 8 },
            { 1, 6 },
            { 3, 9 },
            { 6, 3 },
            { 2, 8 },
            { 1, 5 },
            { 9, 8 },
            { 4, 5 },
            { 4, 7 },
    };
    Graph graph4( 15 );
    for ( int i = 0; i < 15; ++i ) {
        graph4.addEdge( graph4Arr[ i ][ 0 ], graph4Arr[ i ][ 1 ] );
    }

    bool graph4EulerianCycle = true;
    for ( int v = 0; v < graph4.getV(); ++v ) {
        if ( Graph::degree( graph4, v ) % 2 != 0 ) {
            graph4EulerianCycle = false;
            break;
        }
    }
    if ( ! graph4EulerianCycle ) {
        cout << "DEBUG: graph4 DOES NOT HAVE Eulerian Cycle!!!" << endl;
    } else {
        cout << "DEBUG: graph4 DOES HAVE Eulerian Cycle!!!" << endl;
    }

    return 0;
}
