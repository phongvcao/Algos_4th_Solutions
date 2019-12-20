//
// Created by Phong Cao on 2019-03-24.
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
        for ( int v = 0; v < getV(); ++v ) {
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

class WeightedQuickUnionUF {
private:

    vector< int > id;
    vector< int > sz;
    int count = 0;

public:

    WeightedQuickUnionUF( int N )
        : id( N ),
          sz( N, 1 ),
          count( N )
    {
        iota( id.begin(), id.end(), 0 );
    }

    virtual ~WeightedQuickUnionUF() {
        // not implemented
    }

    int find( int p ) const {
        while ( p != id[ p ] ) p = id[ p ];
        return p;
    }

    bool connected( int p, int q ) const {
        return find( p ) == find( q );
    }

    int getCount() const {
        return count;
    }

    void doUnion( int p, int q ) {
        int i = find( p );
        int j = find( q );

        if ( i == j ) return;

        if ( sz[ i ] < sz[ j ] ) {
            id[ i ] = j;
            sz[ j ] += sz[ i ];
        } else {
            id[ j ] = i;
            sz[ i ] += sz[ j ];
        }
        --count;
    }

    string toString() const {
        ostringstream oss;
        oss << *this;
        return oss.str();
    }

    friend ostream& operator <<( ostream& out, const WeightedQuickUnionUF& uf ) {
        out << "\nuf : count : " << uf.getCount() << endl;
        out << "\nid:\n";
        for ( int i = 0; i < uf.id.size(); ++i ) {
            out << i << " : " << uf.id[ i ] << endl;
        }

        out << "\nsz:\n";
        for ( int i = 0; i < uf.sz.size(); ++i ) {
            out << i << " : " << uf.sz[ i ] << endl;
        }
        return out;
    }

};

// d-way heap simply means node at index i >= 1 will have its children ranging from i * d - d + 2 == ( i - 1 ) * d + 2 to i * d + 1.
template< typename Key >
class MinPQDWayHeap {
private:

    vector< Key > pq;
    int N = 0;
    int d = 0;

    int getFirstChild( int i ) {
        return ( i - 1 ) * d + 2;
    }

    int getLastChild( int i ) {
        return i * d + 1;
    }

    int getParent( int i ) {
        return ( i - 2 ) / d + 1;
    }

    bool greater( int i, int j ) const {
        return pq[ i ] > pq[ j ];
    }

    void exchange( int i, int j ) {
        Key temp = pq[ i ];
        pq[ i ] = pq[ j ];
        pq[ j ] = temp;
    }

    void swim( int k ) {
        while ( k > 1 && greater( getParent( k ), k ) ) {
            exchange( getParent( k ), k );
            k = getParent( k );
        }
    }

    void sink( int k ) {
        while ( getFirstChild( k ) <= N ) {
            int j = getFirstChild( k );
            for ( int i = j; i <= getLastChild( k ) && i < N; ++i ) {
                if ( greater( j, i ) ) {
                    j = i;
                }
            }
            if ( ! greater( k, j ) ) break;
            exchange( k, j );
            k = j;
        }
    }

public:


    MinPQDWayHeap( int maxN, int d )
        : pq( maxN * 2 ),
          d( d )
    {
        // not implemented
    }

    MinPQDWayHeap( typename vector< Key >::iterator begin, typename vector< Key >::iterator end, int d )
        : pq( distance( begin, end ) + 1 ),
          d( d )
    {
        for ( auto iter = begin; iter != next( end ); ++iter ) {
            insert( *iter );
        }
    }

    virtual ~MinPQDWayHeap() {
        // not implemented
    }

    void insert( Key key ) {
        pq[ ++N ] = key;
        swim( N );
    }

    Key delMin() {
        Key min = pq[ 1 ];
        exchange( 1, N-- );
        sink( 1 );
        return min;
    }

    Key getMin() {
        return pq[ 1 ];
    }

    int size() const {
        return N;
    }

    bool empty() const {
        return size() == 0;
    }

    string toString() const {
        ostringstream oss;
        oss << *this;
        return oss.str();
    }

    friend ostream& operator <<( ostream& out, const MinPQDWayHeap< Key >& minPQ ) {
        out << "\n| d : " << minPQ.d << " ; N : " << minPQ.size() << endl;
        for ( int i = 0; i < minPQ.pq.size(); ++i ) {
            out << minPQ.pq[ i ] << ", ";
        }
        return out;
    }

    static void test() {
        vector< int > intVec { 14, 12, 10, 8, 6, 4, 2, 0, 1, 3, 5, 7, 9, 11, 13 };
        MinPQDWayHeap< int > minPQ( 2, intVec.size() );
        for ( int i = 0; i < intVec.size(); ++i ) {
            minPQ.insert( intVec[ i ] );
        }
        cout << "DEBUG: minPQ ( 3-way ): \n" << minPQ << endl;
        cout << "DEBUG: minPQ.delMin() ( 2-way ): \n";
        while ( ! minPQ.empty() ) {
            cout << minPQ.delMin() << ", ";
        }
    }
};

class LazyPrimMSTDWayHeap {
private:

    vector< bool > marked;
    queue< Edge > mst;
    MinPQDWayHeap< Edge > minPQ;
    double weight = 0;

public:

    LazyPrimMSTDWayHeap( const EdgeWeightedGraph& G, int d )
        : marked( G.getV(), false ),
          minPQ( G.getV(), d )
    {
        for ( int s = 0; s < G.getV(); ++s ) {
            if ( ! marked[ s ] ) {
                visit( G, s );

                while ( ! minPQ.empty() ) {
                    Edge e = minPQ.delMin();
                    int v = e.getEither();
                    int w = e.getOther( v );
                    if ( marked[ v ] && marked[ w ] ) continue;
                    mst.push( e );
                    weight += e.getWeight();
                    if ( ! marked[ v ] ) visit( G, v );
                    if ( ! marked[ w ] ) visit( G, w );
                }
            }
        }
    }

    virtual ~LazyPrimMSTDWayHeap() {
        // not implemented
    }

    void visit( const EdgeWeightedGraph& G, int v ) {
        marked[ v ] = true;
        for ( Edge e : G.getAdj( v ) ) {
            if ( ! marked[ e.getOther( v ) ] ) {
                minPQ.insert( e );
            }
        }
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
        return weight;
    }

    friend ostream& operator <<( ostream& out, const LazyPrimMSTDWayHeap& mst ) {
        out << "\nmst:\n";
        queue< Edge > q = mst.getEdges();
        while ( ! q.empty() ) {
            out << q.front() << ", ";
            q.pop();
        }
        return out;
    }

};

class KruskalMSTDWayHeap {
private:

    queue< Edge > mst;
    double weight = 0;

public:

    KruskalMSTDWayHeap( const EdgeWeightedGraph& G, int d ) {
        forward_list< Edge > edges = G.getEdges();
        vector< Edge > edgesVec( edges.begin(), edges.end() );
        MinPQDWayHeap< Edge > minPQ( edgesVec.begin(), prev( edgesVec.end() ), 2 );
        WeightedQuickUnionUF uf( G.getV() );

        while ( ! minPQ.empty() && mst.size() < G.getV() - 1 ) {
            Edge e = minPQ.delMin();
            int v = e.getEither();
            int w = e.getOther( v );
            if ( uf.connected( v, w ) ) continue;
            uf.doUnion( v, w );
            mst.push( e );
            weight += e.getWeight();
        }
    }

    virtual ~KruskalMSTDWayHeap() {
        // not implemented
    }

    queue< Edge > getEdges() const {
        return mst;
    }

    double getWeight() const {
        return weight;
    }

    string toString() const {
        ostringstream oss;
        oss << *this;
        return oss.str();
    }

    friend ostream& operator <<( ostream& out, const KruskalMSTDWayHeap& mst ) {
        out << "\nmst:\n";
        queue< Edge > q = mst.getEdges();
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

    cout << "DEBUG: ewGraph: \n" << ewGraph << endl;

    // MinPQDWayHeap< int >::test();

    LazyPrimMSTDWayHeap mst( ewGraph, 2 );
    cout << "DEBUG: LazyPrimMSTDWayHeap: \n" << mst << endl;
    cout << "DEBUG: LazyPrimMSTDWayHeap.getWeight(): \n" << mst.getWeight() << endl;

    KruskalMSTDWayHeap mst1( ewGraph, 2 );
    cout << "DEBUG: KruskalMSTDWayHeap: \n" << mst1.toString() << endl;
    cout << "DEBUG: KruskalMSTDWayHeap.getWeight(): \n" << mst1.getWeight() << endl;

    return 0;
}
