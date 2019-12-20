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

//----< iostream >----------//
using std::cout;
using std::cin;
using std::endl;
using std::ostream;
using std::istream;

//----< cstdio >------------//
using std::printf;
using std::fprintf;
using std::sprintf;
using std::snprintf;

//----< iomanip >-----------//
using std::setprecision;
using std::setw;

//----< ios >---------------//
using std::hex;
using std::dec;
using std::oct;
using std::fixed;

//----< sstream >-----------//
using std::ostringstream;
using std::istringstream;

//----< fstream >-----------//
using std::ofstream;
using std::ifstream;

//----< string >------------//
using std::getline;
using std::string;
using std::to_string;
using std::stoi;
using std::stol;

//----< cmath >-------------//
using std::sqrt;
using std::pow;
using std::log;             // log( <arg> )
using std::exp;             // e ^ <arg>
using std::abs;

//----< cstdlib >-----------//
using std::rand;
using std::srand;

//----< ctime >-------------//
using std::time;

//----< functional >--------//
using std::hash;
using std::greater;         // lhs > rhs. Used for MinPQ
using std::less;            // lhs < rhs. Used for MaxPQ. Default for priority_queue<>
using std::less_equal;
using std::greater_equal;

//----< array >-------------//
using std::array;           // Fixed & Unordered Array

//----< vector >------------//
using std::vector;          // Resizable & Unordered Array

//----< map >---------------//
using std::map;             // Ordered Map (Red-Black Tree)

//----< unordered_map >-----//
using std::unordered_map;   // HashMap (SeparateChainingHashST)

//----< set >---------------//
using std::set;             // Ordered Set (Red-Black Tree)

//----< unordered_set >-----//
using std::unordered_set;   // HashSet (SeparateChainingHashST)

//----< list >--------------//
using std::list;            // Doubly-Linked List with size() ( O( 1 ) )

//----< forward_list >------//
using std::forward_list;    // Singly-Linked List without size() function ( so O( N ) if we need to get size() )

//----< deque >-------------//
using std::deque;           // Vector of fixed-size Vectors: 1 fixed-size vector for each end of the deque

//----< queue >-------------//
using std::queue;           // Non-Iterable & Use std::deque as underlying data structure
using std::priority_queue;  // MaxPQ (MaxHeap) & Non-Iterable.
//                          // => Pass std::greater<> as template params to create MinPQ (MinHeap)

//----< stack >-------------//
using std::stack;           // Non-Iterable & Use std::deque as underlying data structure

//----< iterator >----------//
using std::next;            // Return an advanced iter without changing original iter
using std::prev;            // Return an decremented iter without changing original iter
using std::distance;        // Calculate distance between 2 iterators

//----< utility >-----------//
using std::pair;

//----< algorithm >---------//
using std::fill;
using std::max;
using std::min;
using std::find;
using std::reverse;
using std::sort;

//----< memory >------------//
using std::make_shared;
using std::shared_ptr;

//----< cctype >------------//
using std::isalnum;
using std::isalpha;
using std::islower;
using std::isupper;
using std::isdigit;
using std::isspace;         // Check whether char is whitespace character (space, newline, tab, etc. )
using std::isblank;         // Check whether char is blank character ( space or tab )
using std::tolower;
using std::toupper;

//----< stdexcept >---------//
using std::runtime_error;
using std::invalid_argument;
using std::out_of_range;

//----< limits >------------//
using std::numeric_limits;

//----< numeric >-----------//
using std::iota;
using std::gcd;
using std::lcm;

//--------------------------//

class DirectedEdge {
private:

    int v = 0;
    int w = 0;
    double weight = numeric_limits< double >::infinity();

public:

    DirectedEdge() {
        // not implemented
    }

    DirectedEdge( int v, int w, double weight )
        : v( v ),
          w( w ),
          weight( weight )
    {
        // not implemented
    }

    DirectedEdge( const DirectedEdge& e )
        : v( e.v ),
          w( e.w ),
          weight( e.weight )
    {
        // not implemented
    }

    virtual ~DirectedEdge() {
        // not implemented
    }

    int getFrom() const {
        return v;
    }

    int getTo() const {
        return w;
    }

    double getWeight() const {
        return weight;
    }

    operator bool() const {
        return weight != numeric_limits< double >::infinity();
    }

    friend bool operator ==( const DirectedEdge& e1, const DirectedEdge& e2 ) {
        return e1.v == e2.v && e1.w == e2.w;
    }

    friend bool operator !=( const DirectedEdge& e1, const DirectedEdge& e2 ) {
        return ! ( e1 == e2 );
    }

    string toString() const {
        ostringstream oss;
        oss << *this;
        return oss.str();
    }

    friend ostream& operator <<( ostream& out, const DirectedEdge& e ) {
        out << fixed << setprecision( 2 );
        out << " | " << e.v << " : " << e.w << " : " << e.weight << " | ";
        return out;
    }

};

class EdgeWeightedDigraph {
private:

    int V = 0;
    int E = 0;
    vector< forward_list< DirectedEdge > > adj;

public:

    EdgeWeightedDigraph( int V )
        : V( V ),
          adj( V )
    {
        // not implemented
    }

    virtual ~EdgeWeightedDigraph() {
        // not implemented
    }

    int getV() const {
        return V;
    }

    int getE() const {
        return E;
    }

    forward_list< DirectedEdge > getAdj( int v ) const {
        return adj[ v ];
    }

    forward_list< DirectedEdge > getEdges() const {
        forward_list< DirectedEdge > all;
        for ( int v = 0; v < getV(); ++v ) {
            for ( DirectedEdge e : getAdj( v ) ) {
                all.push_front( e );
            }
        }
        return all;
    }
    
    void addEdge( DirectedEdge e ) {
        adj[ e.getFrom() ].push_front( e );
        ++E;
    }

    string toString() const {
        ostringstream oss;
        oss << *this;
        return oss.str();
    }

    friend ostream& operator <<( ostream& out, const EdgeWeightedDigraph& G ) {
        out << "\n| V : " << G.getV() << " ; E : " << G.getE() << " ; adj : \n";
        for ( int v = 0; v < G.getV(); v++ ) {
            out << "\n| v : " << v << " : ";
            for ( const DirectedEdge& e : G.getAdj( v ) ) {
                out << e << ", ";
            }
            out << " | ";
        }
        return out;
    }

};

template< typename Key >
class IndexMinPQ {
private:

    vector< int > pq;
    vector< int > qp;
    vector< Key > keys;
    int N = 0;

    bool isGreater( int i, int j ) const {
        return keys[ pq[ i ] ] > keys[ pq[ j ] ];
    }

    void exchange( int i, int j ) {
        int temp = pq[ i ];
        pq[ i ] = pq[ j ];
        pq[ j ] = temp;
        qp[ pq[ i ] ] = i;
        qp[ pq[ j ] ] = j;
    }

    void swim( int k ) {
        while ( k > 1 && isGreater( k / 2, k ) ) {
            exchange( k / 2, k );
            k /= 2;
        }
    }

    void sink( int k ) {
        while ( 2 * k <= N ) {
            int j = 2 * k;
            if ( j < N && isGreater( j, j + 1 ) ) ++j;
            if ( ! isGreater( k, j ) ) break;
            exchange( k, j );
            k = j;
        }
    }

public:

    IndexMinPQ( int maxN )
        : pq( maxN + 1 ),
          qp( maxN + 1, -1 ),
          keys( maxN + 1 )
    {
        // not implemented
    }

    virtual ~IndexMinPQ() {
        // not implemented
    }

    int size() const {
        return N;
    }

    bool empty() const {
        return size() == 0;
    }

    bool contains( int k ) const {
        return qp[ k ] != -1;
    }

    int getMinIndex() const {
        return pq[ 1 ];
    }

    Key getMin() const {
        return keys[ pq[ 1 ] ];
    }

    Key get( int k ) const {
        if ( ! contains( k ) ) throw runtime_error( "Invalid index for priority queue" );
        return keys[ k ];
    }

    void insert( int k, Key key ) {
        ++N;
        pq[ N ] = k;
        qp[ k ] = N;
        keys[ k ] = key;
        swim( N );
    }

    int delMin() {
        int min = pq[ 1 ];
        exchange( 1, N-- );
        sink( 1 );
        pq[ N + 1 ] = -1;
        qp[ min ] = -1;
        return min;
    }

    void deleteKey( int k ) {
        if ( ! contains( k ) ) throw runtime_error( "Invalid index for priority queue" );
        int index = qp[ k ];
        exchange( index, N-- );
        swim( index );
        sink( index );
        pq[ N + 1 ] = -1;
        qp[ k ] = -1;
    }

    void change( int k, Key key ) {
        if ( ! contains( k ) ) throw runtime_error( "Invalid index for priority queue" );
        keys[ k ] = key;
        swim( qp[ k ] );
        sink( qp[ k ] );
    }

    string toString() const {
        ostringstream oss;
        oss << *this;
        return oss.str();
    }

    friend ostream& operator <<( ostream& out, const IndexMinPQ< Key >& indexMinPQ ) {
        out << "\nindexMinPQ:\n";
        out << "\npq:\n";
        for ( int i = 0; i < indexMinPQ.pq.size(); i++ ) {
            out << i << " : " << indexMinPQ.pq[ i ] << endl;
        }

        out << "\nqp:\n";
        for ( int i = 0; i < indexMinPQ.qp.size(); i++ ) {
            out << i << " : " << indexMinPQ.qp[ i ] << endl;
        }

        out << "\nkeys;\n";
        for ( int i = 0; i < indexMinPQ.keys.size(); i++ ) {
            out << i << " : " << indexMinPQ.keys[ i ] << endl;
        }
        return out;
    }
};

class DijkstraSP {
private:

    vector< DirectedEdge > edgeTo;
    vector< double > distTo;
    IndexMinPQ< double > indexMinPQ;

    void relax( const EdgeWeightedDigraph& G, int v ) {
        for ( DirectedEdge e : G.getAdj( v ) ) {
            int w = e.getTo();
            if ( distTo[ w ] > distTo[ v ] + e.getWeight() ) {
                distTo[ w ] = distTo[ v ] + e.getWeight();
                edgeTo[ w ] = e;

                if ( indexMinPQ.contains( w ) ) {
                    indexMinPQ.change( w, distTo[ w ] );
                } else {
                    indexMinPQ.insert( w, distTo[ w ] );
                }
            }
        }
    }

public:

    DijkstraSP( const EdgeWeightedDigraph& G, int s )
        : edgeTo( G.getV() ),
          distTo( G.getV(), numeric_limits< double >::infinity() ),
          indexMinPQ( G.getV() )
    {
        distTo[ s ] = 0;
        indexMinPQ.insert( s, 0 );

        while ( ! indexMinPQ.empty() ) {
            relax( G, indexMinPQ.delMin() );
        }
    }

    virtual ~DijkstraSP() {
        // not implemented
    }

    double getDistTo( int v ) const {
        return distTo[ v ];
    }

    stack< DirectedEdge > getPathTo( int v ) const {
        stack< DirectedEdge > path;
        if ( ! hasPathTo( v ) ) return path;
        for ( DirectedEdge e = edgeTo[ v ]; e; e = edgeTo[ e.getFrom() ] ) {
            path.push( e );
        }
        return path;
    }

    bool hasPathTo( int v ) const {
        return distTo[ v ] != numeric_limits< double >::infinity();
    }

    string toString() const {
        ostringstream oss;
        oss << *this;
        return oss.str();
    }

    friend ostream& operator <<( ostream& out, const DijkstraSP& sp ) {
        out << "\nsp:\n";
        for ( int v = 0; v < sp.edgeTo.size(); v++ ) {
            out << "\n| v : " << v << " : ";
            stack< DirectedEdge > s = sp.getPathTo( v );
            while ( ! s.empty() ) {
                out << s.top() << ", ";
                s.pop();
            }
            out << " | ";
        }

        out << "\n\ndistTo:\n";
        for ( int v = 0; v < sp.distTo.size(); ++v ) {
            out << v << " : " << sp.distTo[ v ] << endl;
        }
        
        out << "\n\nedgeTo:\n";
        for ( int v = 0; v < sp.edgeTo.size(); v++ ) {
            out << v << " : " << sp.edgeTo[ v ] << endl;
        }

        return out;
    }
};

namespace std {
    template <>
    struct hash< DirectedEdge > {
        size_t operator ()( const DirectedEdge& e ) {
            int hash = 17;
            hash = 31 * hash + std::hash< int >{}( e.getFrom() );
            hash = 31 * hash + std::hash< int >{}( e.getTo() );
            hash = 31 * hash + std::hash< double >{}( e.getWeight() );
            return hash;
        }
    };
}

class Path {
private:

    DirectedEdge edge;
    double weight = numeric_limits< double >::max();

public:

    Path() {
        // not implemented
    }

    Path( DirectedEdge e, double weight )
        : edge( e ),
          weight( weight )
    {
        // not implemented
    }

    Path( const Path& p )
        : edge( p.edge ),
          weight( p.weight )
    {
        // not implemented
    }

    virtual ~Path() {
        // not implemented
    }

    double getWeight() const {
        return weight;
    }

    DirectedEdge getEdge() const {
        return edge;
    }

    friend bool operator <( const Path& p1, const Path& p2 ) {
        if ( p1.weight < p2.weight ) {
            return true;
        } else if ( p1.weight > p2.weight ) {
            return false;
        }

        return std::hash< DirectedEdge >{}( p1.edge ) < std::hash< DirectedEdge >{}( p2.edge );
    }

    friend bool operator ==( const Path& p1, const Path& p2 ) {
        return p1.edge == p2.edge;
    }

    friend bool operator !=( const Path& p1, const Path& p2 ) {
        return ! ( p1 == p2 );
    }

    string toString() const {
        ostringstream oss;
        oss << *this;
        return oss.str();
    }

    friend ostream& operator <<( ostream& out, const Path& p ) {
        out << fixed << setprecision( 2 );
        out << " | " << p.edge << " : " << p.weight << " | ";
        return out;
    }

};

class CriticalEdgesDetection {
private:

    set< Path > criticalEdges;

public:

    CriticalEdgesDetection( const EdgeWeightedDigraph& G, int s, int t ) {
        DijkstraSP sp( G, s );
        stack< DirectedEdge > path = sp.getPathTo( t );
        while ( ! path.empty() ) {
            EdgeWeightedDigraph ewDigraph( G.getV() );
            for ( DirectedEdge e : G.getEdges() ) {
                if ( e == path.top() ) continue;
                ewDigraph.addEdge( e );
            }

            DijkstraSP sp1( ewDigraph, s );
            Path p( path.top(), sp1.getDistTo( t ) );
            criticalEdges.insert( p );

            path.pop();
        }
    }

    virtual ~CriticalEdgesDetection() {
        // not implemented
    }

    stack< DirectedEdge > getCriticalEdges() const {
        stack< DirectedEdge > edges;
        double maxWeight = prev( criticalEdges.end() )->getWeight();
        edges.push( prev( criticalEdges.end() )->getEdge() );
        for ( typename set< Path >::reverse_iterator iter = criticalEdges.rbegin();
                iter != criticalEdges.rend(); ++iter ) {
            if ( iter->getWeight() < maxWeight ) break;

            if ( iter->getEdge() != edges.top() ) {
                edges.push( iter->getEdge() );
            }
        }
        return edges;
    }

    string toString() const {
        ostringstream oss;
        oss << *this;
        return oss.str();
    }

    friend ostream& operator <<( ostream& out, const CriticalEdgesDetection& ced ) {
        out << "\nced:\n";
        stack< DirectedEdge > s = ced.getCriticalEdges();
        while ( ! s.empty() ) {
            out << s.top() << ", ";
            s.pop();
        }
        return out;
    }

};

int main( int argc, char ** argv ) {

    double graphArr[ 15 ][ 3 ] = {
            { 4, 5, 0.35 },
            { 5, 4, 0.35 },
            { 4, 7, 0.37 },
            { 5, 7, 0.28 },
            { 7, 5, 0.28 },
            { 5, 1, 0.32 },
            { 0, 4, 0.38 },
            { 0, 2, 0.26 },
            { 7, 3, 0.39 },
            { 1, 3, 0.29 },
            { 2, 7, 0.34 },
            { 6, 2, 0.40 },
            { 3, 6, 0.52 },
            { 6, 0, 0.58 },
            { 6, 4, 0.93 }
    };

    EdgeWeightedDigraph ewDigraph( 8 );

    for ( int i = 0; i < 15; ++i ) {
        DirectedEdge e( (int)graphArr[ i ][ 0 ], (int)graphArr[ i ][ 1 ], graphArr[ i ][ 2 ] );
        ewDigraph.addEdge( e );
    }

    cout << "DEBUG: ewDigraph: \n" << ewDigraph << endl;

    DijkstraSP sp( ewDigraph, 0 );
    cout << "DEBUG: sp: \n" << sp << endl;

    CriticalEdgesDetection ced( ewDigraph, 0, 3 );
    cout << "DEBUG: ced: \n" << ced << endl;

    return 0;
}
