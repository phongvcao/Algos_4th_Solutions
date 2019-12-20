//
// Created by Phong Cao on 2019-03-12.
//

// uncomment to disable assert()
// #define NDEBUG
#include <cassert>
#include <iostream>
#include <iomanip>
#include <ios>
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
#include <stdexcept>
#include <limits>
#include <numeric>

//----<iostream>------------//
using std::cout;
using std::cin;
using std::endl;
using std::ostream;
using std::istream;

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
using std::priority_queue;  // MaxPQ (MaxHeap) & Non-Iterable.
//                          // => Pass std::greater<> as template params to create MinPQ (MinHeap)

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

//----<stdexcept>-----------//
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
        if ( vertex == v ) {
            return w;
        } else if ( vertex == w ) {
            return v;
        } else {
            throw invalid_argument( "Invalid vertex for edge : " + toString() );
        }
    }

    double getWeight() const {
        return weight;
    }

    friend bool operator <( const Edge& e1, const Edge& e2 ) {
        return e1.weight < e2.weight;
    }

    friend bool operator >( const Edge& e1, const Edge& e2 ) {
        return e1.weight > e2.weight;
    }

    friend bool operator ==( const Edge& e1, const Edge& e2 ) {
        return ( e1.v == e2.v && e1.w == e2.w ) || ( e1.v == e2.w && e1.w == e2.v );
    }

    friend bool operator !=( const Edge& e1, const Edge& e2 ) {
        return ! ( e1 == e2 );
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

namespace std {
    template<>
    struct hash< Edge > {
        size_t operator ()( const Edge& e ) const {
            int v = e.getEither();
            int w = e.getOther( v );
            int hash = 17;
            hash = 31 * hash + std::hash< int >{}( v );
            hash = 31 * hash + std::hash< int >{}( w );
            hash = 31 * hash + std::hash< double >{}( e.getWeight() );
            return hash;
        }
    };
}

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

    EdgeWeightedGraph( const EdgeWeightedGraph& G )
        : V( G.getV() ),
          adj( G.getV() )
    {
        for ( Edge e : G.getEdges() ) {
            addEdge( e );
        }
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
        for ( int v = 0; v < getV(); ++v ) {
            for ( Edge e : getAdj( v ) ) {
                if ( e.getOther( v ) > v ) {
                    all.push_front( e );
                }
            }
        }
        return all;
    }

    priority_queue< Edge > getSortedEdges() const {
        priority_queue< Edge > all;
        for ( int v = 0; v < getV(); ++v ) {
            for ( Edge e : getAdj( v ) ) {
                if ( e.getOther( v ) > v ) {
                    all.push( e );
                }
            }
        }
        return all;
    }

    void deleteEdge( const Edge& edge ) {
        int v = edge.getEither();
        int w = edge.getOther( v );

        forward_list< Edge > newAdjV;
        for ( Edge e : getAdj( v ) ) {
            if ( e != edge ) {
                newAdjV.push_front( e );
            }
        }
        adj[ v ] = newAdjV;

        forward_list< Edge > newAdjW;
        for ( Edge e : getAdj( w ) ) {
            if ( e != edge ) {
                newAdjW.push_front( e );
            }
        }
        adj[ w ] = newAdjW;
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
        out << "\n | V : " << G.getV() << " ; E : " << G.getE() << " ; adj : \n";
        for ( int v = 0; v < G.getV(); ++v ) {
            out << "\n | v : " << v << " : ";
            for ( const Edge& e : G.getAdj( v ) ) {
                out << e << ", ";
            }
            out << " | ";
        }
        return out;
    }
};

class Bridge {
private:

    // Order of visit
    vector< int > pre;
    // Lowest order of visit possible (including back-edge)
    vector< int > low;
    // Number of bridges
    int bridges = 0;
    // count for generating order of visit
    int count = 0;
    unordered_set< Edge > bridgeEdges;

public:

    Bridge( const EdgeWeightedGraph& G )
        : pre( G.getV(), -1 ),
          low( G.getV(), -1 )
    {
        for ( int v = 0; v < G.getV(); ++v ) {
            if ( pre[ v ] == -1 ) {
                // dfs() till we find a cycle. Then update the low[] of
                // vertices in that cycle to the pre[] of the newly-hitted vertex,
                // of course if the pre[] of newly-hitted vertex is smaller.
                dfs( G, v, v );
            }
        }
    }

    virtual ~Bridge() {
        // not implemented
    }

    void dfs( const EdgeWeightedGraph& G, int v, int u ) {
        pre[ v ] = count++;
        low[ v ] = pre[ v ];

        for ( Edge e : G.getAdj( v ) ) {
            int w = e.getOther( v );
            // Unvisited vertex
            if ( pre[ w ] == -1 ) {
                dfs( G, w, v );

                // After visiting w, update low[ v ] to low[ w ] in the whole chain if low[ w ] is smaller
                low[ v ] = min( low[ v ], low[ w ] );

                // After visiting w & its chlidren & grandchildren, if the low[ w ] value is not changed, it means
                // that w cannot be reached from any other edges other than v. This means v-w is a bridge.
                if ( low[ w ] == pre[ w ] ) {
                    bridgeEdges.insert( e );
                    // cout << "DEBUG: EDGE e : " << e << " IS A BRIDGE!!!" << endl;
                    ++bridges;
                }
            } else if ( w != u ) {
                // We hit a cycle here, update low[ v ] to pre[ w ] if pre[ w ] is smaller
                low[ v ] = min( low[ v ], pre[ w ] );
            }
        }
    }

    bool isBridge( Edge e ) {
        return bridgeEdges.find( e ) != bridgeEdges.end();
    }

    int getBridges() const {
        return bridges;
    }

    string toString() const {
        ostringstream oss;
        oss << *this;
        return oss.str();
    }

    friend ostream& operator <<( ostream& out, const Bridge& bridge ) {
        out << "\nbridge: bridges : " << bridge.getBridges() << endl;
        out << "\npre:\n";
        for ( int v = 0; v < bridge.pre.size(); ++v ) {
            out << v << " : " << bridge.pre[ v ] << endl;
        }

        out << "\nlow:\n";
        for ( int v = 0; v < bridge.low.size(); ++v ) {
            out << v << " : " << bridge.low[ v ] << endl;
        }

        return out;
    }

};

class ReverseDeleteMST {
private:

    queue< Edge > mst;

public:

    ReverseDeleteMST( const EdgeWeightedGraph& G ) {
        EdgeWeightedGraph ewGraph( G );
        shared_ptr< Bridge > bridge = make_shared< Bridge >( ewGraph );
        priority_queue< Edge > maxPQ = G.getSortedEdges();
        while ( ! maxPQ.empty() ) {
            Edge e = maxPQ.top();
            if ( bridge->isBridge( e ) ) {
                // cout << "DEBUG: Examining: e: " << e << " IS a Bridge!!!" << endl;
                mst.push( e );
            } else {
                // cout << "DEBUG: Examining: e: " << e << " IS NOT a Bridge!!!" << endl;
                ewGraph.deleteEdge( e );
                bridge = make_shared< Bridge >( ewGraph );
            }
            maxPQ.pop();
        }
    }

    virtual ~ReverseDeleteMST() {
        // not implemented
    }

    queue< Edge > getEdges() const {
        return mst;
    }

    string toString() const {
        ostringstream oss;
        oss << *this;
        return oss.str();
    }

    double getWeight() const {
        double weight = 0;
        queue< Edge > q = getEdges();
        while ( ! q.empty() ) {
            weight += q.front().getWeight();
            q.pop();
        }
        return weight;
    }

    friend ostream& operator <<( ostream& out, const ReverseDeleteMST& mst ) {
        queue< Edge > q = mst.getEdges();
        out << "\nmst:\n";
        while ( ! q.empty() ) {
            out << q.front() << ", ";
            q.pop();
        }
        return out;
    }
};

int main( int argc, char ** argv ) {

    double graphArr[ 16 ][ 3 ] = {
            { 4, 5, 0.35 },
            { 4, 7, 0.37 },
            { 5, 7, 0.28 },
            { 0, 7, 0.16 },
            { 1, 5, 0.32 },
            { 0, 4, 0.38 },
            { 2, 3, 0.17 },
            { 1, 7, 0.19 },
            { 0, 2, 0.26 },
            { 1, 2, 0.36 },
            { 1, 3, 0.29 },
            { 2, 7, 0.34 },
            { 6, 2, 0.40 },
            { 3, 6, 0.52 },
            { 6, 0, 0.58 },
            { 6, 4, 0.93 }
    };

    EdgeWeightedGraph ewGraph( 8 );

    for ( int i = 0; i < 16; ++i ) {
        Edge e( (int)graphArr[ i ][ 0 ], (int)graphArr[ i ][ 1 ], graphArr[ i ][ 2 ] );
        ewGraph.addEdge( e );
    }

    cout << "DEBUG: ewGraph: \n" << ewGraph.toString() << endl;

    ReverseDeleteMST mst( ewGraph );
    cout << "DEBUG: mst: \n" << mst << endl;
    cout << "DEBUG: mst.getWeight(): \n" << mst.getWeight() << endl;

    return 0;
}
