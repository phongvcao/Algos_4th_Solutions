//
// Created by Phong Cao on 2019-02-19.
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

class Vertex {
public:
    int i = 0;
    int j = 0;
    int id = -1;
    int color = 0;

    Vertex( int i, int j, int color, int id )
        : i( i ),
          j( j ),
          color( color ),
          id( id )
    {
        // not implemented
    }

    Vertex( const Vertex& other )
        : i( other.i ),
          j( other.j ),
          color( other.color ),
          id( other.id )
    {
        // not implemented
    }

    virtual ~Vertex() {
        // not implemented
    }

    friend bool operator ==( const Vertex& v1, const Vertex& v2 ) {
        return ( v1.i == v2.i && v1.j == v2.j );
    }

    friend bool operator !=( const Vertex& v1, const Vertex& v2 ) {
        return ! ( v1 == v2 );
    }

    string toString() const {
        return " | id : " + to_string( id ) + " ; i : " + to_string( i ) + " ; j : " + to_string( j ) + " ; color : " + to_string( color ) + " | ";
    }
};

class Graph {
private:

    int V = 0;
    int E = 0;
    int imgWidth = 4;
    int imgLength = 4;
    vector< shared_ptr< Vertex > > vertices;
    vector< forward_list< int > > adj;

public:

    Graph( int V, int imgWidth, int imgLength )
        : V( V ),
          imgWidth( imgWidth ),
          imgLength( imgLength )
    {
        vertices.resize( V );
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

    forward_list< int > getAdj( int v ) const {
        return adj[ v ];
    }

    string toString() const {
        string rv = "\n";
        for ( int v = 0; v < V; ++v ) {
            rv += vertices[ v ]->toString() + " : ";
            for ( int w : getAdj( v ) ) {
                rv += vertices[ w ]->toString() + ", ";
            }
            rv += " | \n";
        }
        return rv;
    }

    void addVertex( Vertex v ) {
        vertices[ v.id ] = make_shared< Vertex >( v );
    }

    shared_ptr< Vertex > getVertex( int i, int j ) {
        return vertices[ i * imgLength + j ];
    }

    bool contains( int i, int j ) {
        return ! ! getVertex( i, j );
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

int main( int argc, char ** argv ) {
    int imageArr[ 4 ][ 4 ] = {
            { 0, 0, 1, 0 },
            { 6, 4, 2, 3 },
            { 5, 9, 9, 9 },
            { 8, 8, 8, 8 }
    };
    Graph graph( 16, 4, 4 );

    for ( int i = 0; i < 4; ++i ) {
        for ( int j = 0; j < 4; ++j ) {
            Vertex v( i, j, imageArr[ i ][ j ], 4 * i + j );

            if ( ! graph.contains( i, j ) ) {
                graph.addVertex( v );
            }

            // Check top vertex
            if ( i > 0 ) {
                if ( ! graph.contains( i - 1, j ) ) {
                    Vertex top( i - 1, j, imageArr[ i - 1 ][ j ], 4 * ( i - 1 ) + j );
                    graph.addVertex( top );
                }

                if ( graph.getVertex( i, j )->color == graph.getVertex( i - 1, j )->color ) {
                    graph.addEdge( graph.getVertex( i, j )->id, graph.getVertex( i - 1, j )->id );
                }
            }

            // Check bottom vertex
            if ( i < 3 ) {
                if ( ! graph.contains( i + 1, j ) ) {
                    Vertex bottom( i + 1, j, imageArr[ i + 1 ][ j ], 4 * ( i + 1 ) + j );
                    graph.addVertex( bottom );
                }

                if ( graph.getVertex( i, j )->color == graph.getVertex( i + 1, j )->color ) {
                    graph.addEdge( graph.getVertex( i, j )->id, graph.getVertex( i + 1, j )->id );
                }
            }

            // Check left vertex
            if ( j > 0 ) {
                if ( ! graph.contains( i, j - 1 ) ) {
                    Vertex left( i, j - 1, imageArr[ i ][ j - 1 ], 4 * i + j - 1 );
                    graph.addVertex( left );
                }

                if ( graph.getVertex( i, j )->color == graph.getVertex( i, j - 1 )->color ) {
                    graph.addEdge( graph.getVertex( i, j )->id, graph.getVertex( i, j - 1 )->id );
                }
            }

            // Check right vertex
            if ( j < 3 ) {
                if ( ! graph.contains( i, j + 1 ) ) {
                    Vertex right( i, j + 1, imageArr[ i ][ j + 1 ], 4 * i + j + 1 );
                    graph.addVertex( right );
                }

                if ( graph.getVertex( i, j )->color == graph.getVertex( i, j + 1 )->color ) {
                    graph.addEdge( graph.getVertex( i, j )->id, graph.getVertex( i, j + 1 )->id );
                }
            }
        }
    }

    cout << "DEBUG: graph: \n" << graph.toString() << endl;

    return 0;
}
