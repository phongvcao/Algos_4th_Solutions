//
// Created by Phong Cao.
//

// uncomment to disable assert()
// #define NDEBUG
#include <cassert>
#include <iostream>
#include <cstdio>
#include <iomanip>
#include <ios>
#include <sstream>
#include <fstream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <functional>
#include <array>
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
#include <stdexcept>
#include <limits>
#include <numeric>

//----<iostream>------------//
using std::cout;
using std::cin;
using std::endl;
using std::ostream;
using std::istream;

//----<cstdio>--------------//
using std::printf;
using std::fprintf;
using std::sprintf;
using std::snprintf;

//----<iomanip>-------------//
using std::setprecision;
using std::setw;

//----<ios>-----------------//
using std::hex;
using std::dec;
using std::oct;
using std::fixed;

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
using std::log;             // log( <arg> )
using std::exp;             // e ^ <arg>
using std::abs;

//----<cstdlib>-------------//
using std::rand;
using std::srand;

//----<ctime>---------------//
using std::time;

//----<functional>----------//
using std::hash;
using std::greater;         // lhs > rhs. Used for MinPQ
using std::less;            // lhs < rhs. Used for MaxPQ. Default for priority_queue<>
using std::less_equal;
using std::greater_equal;

//----<array>---------------//
using std::array;           // Fixed & Unordered Array

//----<vector>--------------//
using std::vector;          // Resizable & Unordered Array

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
using std::priority_queue;  // MaxPQ (MaxHeap) & Non-Iterable.
//                          // => Pass std::greater<> as template params to create MinPQ (MinHeap)

//----<stack>---------------//
using std::stack;           // Non-Iterable & Use std::deque as underlying data structure

//----<iterator>------------//
using std::next;            // Return an advanced iter without changing original iter
using std::prev;            // Return an decremented iter without changin original iter
using std::distance;        // Calculate distance between 2 iterators

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

//----<stdexcept>-----------//
using std::runtime_error;
using std::invalid_argument;
using std::out_of_range;

//----<limits>--------------//
using std::numeric_limits;

//----<numeric>-------------//
using std::iota;
using std::gcd;
using std::lcm;

//--------------------------//

class Edge {
private:

    int v = 0;
    int w = 0;
    double weight = numeric_limits< double >::infinity();

public:

    Edge() {
        // not implemented
    }

    Edge( int v, int w, double weight )
        : v( v ),
          w( w ),
          weight( weight )
    {
        // not implemented
    }

    Edge( const Edge& e )
        : v( e.v ),
          w( e.w ),
          weight( e.weight )
    {
        // not implemented
    }

    virtual ~Edge() {
        // not implemented
    }

    int getEither() const {
        return v;
    }

    int getOther( int vertex ) const {
        if ( v == vertex ) {
            return w;
        } else if ( w == vertex ) {
            return v;
        } else {
            throw runtime_error( "Invalid vertex for edge : " + toString() );
        }
    }

    double getWeight() const {
        return weight;
    }

    operator bool() const {
        return weight != numeric_limits< double >::infinity();
    }

    string toString() const {
        ostringstream oss;
        oss << *this;
        return oss.str();
    }

    friend ostream& operator <<( ostream& out, const Edge& e ) {
        out << fixed << setprecision( 2 );
        out << " | " << e.v << " : " << e.w << " : " << e.weight << " | ";
        return out;
    }

};

class EdgeWeightedGraph {
private:

    int V = 0;
    int E = 0;
    vector< forward_list< Edge > > adj;

public:

    EdgeWeightedGraph( int V )
        : V( V ),
          adj( V )
    {
        // not implemented
    }

    virtual ~EdgeWeightedGraph() {
        // not implemented
    }

    int getV() const {
        return V;
    }

    int getE() const {
        return E;
    }

    forward_list< Edge > getAdj( int v ) const {
        return adj[ v ];
    }

    forward_list< Edge > getEdges() const {
        forward_list< Edge > all;
        for ( int v = 0; v < V; ++v ) {
            for ( Edge e : getAdj( v ) ) {
                if ( e.getOther( v ) > v ) {
                    all.push_front( e );
                }
            }
        }
        return all;
    }

    void addEdge( Edge e ) {
        int v = e.getEither();
        int w = e.getOther( v );
        adj[ v ].push_front( e );
        adj[ w ].push_front( e );
        ++E;
    }

    string toString() const {
        ostringstream oss;
        oss << *this;
        return oss.str();
    }

    friend ostream& operator <<( ostream& out, const EdgeWeightedGraph& G ) {
        out << "\n| V : " << G.getV() << " ; E : " << G.getE() << " ; adj : \n";
        for ( int v = 0; v < G.getV(); ++v ) {
            out << "\n| v : " << v << " : ";
            for ( const Edge& e : G.getAdj( v ) ) {
                out << e << ", ";
            }
            out << " | ";
        }
        return out;
    }

};

class WeightedLineGraphAllPairsSP {
private:

    vector< bool > marked;
    vector< double > distTo;
    int s = 0;

    void dfs( const EdgeWeightedGraph& G, int v, int multiplier ) {
        marked[ v ] = true;
        if ( s == v ) {
            forward_list< Edge > adjList = G.getAdj( v );
            Edge e = adjList.front();
            int w = e.getOther( v );
            adjList.pop_front();
            if ( ! marked[ w ] ) {
                distTo[ w ] = e.getWeight() * multiplier + distTo[ v ];
                dfs( G, w, 1 );
            }

            if ( ! adjList.empty() ) {
                e = adjList.front();
                int w = e.getOther( v );
                adjList.pop_front();
                if ( ! marked[ w ] ) {
                    distTo[ w ] = e.getWeight() * multiplier + distTo[ v ];
                    dfs( G, w, 1 );
                }
            }
        } else {
            for ( const Edge & e : G.getAdj( v ) ) {
                int w = e.getOther( v );
                if ( ! marked[ w ] ) {
                    distTo[ w ] = e.getWeight() * multiplier + distTo[ v ];
                    dfs( G, w, multiplier );
                }
            }
        }
    }

public:

    WeightedLineGraphAllPairsSP( const EdgeWeightedGraph& G )
        : marked( G.getV(), false ),
          distTo( G.getV(), 0 )
    {
        distTo[ s ] = 0;
        for ( int v = 0; v < G.getV(); ++v ) {
            if ( ! marked[ v ] ) {
                dfs( G, v, 1 );
            }
        }
    }

    virtual ~WeightedLineGraphAllPairsSP() {
        // not implemented
    }

    double getDist( int v, int w ) const {
        return abs( distTo[ w ] - distTo[ v ] );
    }

    string toString() const {
        ostringstream oss;
        oss << *this;
        return oss.str();
    }

    friend ostream& operator <<( ostream& out, const WeightedLineGraphAllPairsSP& sp ) {
        out << "\nsp:\n";
        for ( int v = 0; v < sp.distTo.size(); ++v ) {
            for ( int w = 0; w < sp.distTo.size(); ++w ) {
                out << v << " : " << w << " : " << sp.getDist( v, w ) << endl;
            }
        }

        out << "\n\ndistTo:\n";
        for ( int v = 0; v < sp.distTo.size(); ++v ) {
            out << v << " : " << sp.distTo[ v ] << endl;
        }
        return out;
    }

};

int main( int argc, char ** argv ) {

    double graphArr[ 16 ][ 3 ] = {
            { 0, 1, 1 },
            { 1, 2, 2 },
            { 2, 3, 3 },
            { 3, 4, 4 },
            { 4, 5, 5 },
            { 5, 6, 6 },
            { 6, 7, 7 },
    };

    EdgeWeightedGraph ewGraph( 8 );

    for ( int i = 0; i < 7; ++i ) {
        Edge e( (int)graphArr[ i ][ 0 ], (int)graphArr[ i ][ 1 ], graphArr[ i ][ 2 ] );
        ewGraph.addEdge( e );
    }

    cout << "DEBUG: ewGraph: \n" << ewGraph.toString() << endl;

    WeightedLineGraphAllPairsSP sp( ewGraph );
    cout << "DEBUG: sp: \n" << sp << endl;

    return 0;
}
