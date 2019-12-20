//
// Created by Phong Cao on 2019-03-19.
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
        out << "\n| V : " << G.getV() << " ; E : " << G.getE() << " ; adj : \n";
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

    int getCount() const {
        return count;
    }

    string toString() const {
        ostringstream oss;
        oss << *this;
        return oss.str();
    }

    friend ostream& operator <<( ostream& out, const WeightedQuickUnionUF& uf ) {
        out << "\nuf : count : " << uf.getCount();
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

class KruskalMSTSorting {
private:

    queue< Edge > mst;
    vector< Edge > minEdges;
    WeightedQuickUnionUF uf;
    double weight = 0;

    bool less( const Edge& e1, const Edge& e2 ) const {
        return e1 < e2;
    }

    bool greater( const Edge& e1, const Edge& e2 ) const {
        return e1 > e2;
    }

    void exchange( vector< Edge >& edgeVec, int i, int j ) {
        Edge temp = edgeVec[ i ];
        edgeVec[ i ] = edgeVec[ j ];
        edgeVec[ j ] = temp;
    }

    int partition( vector< Edge >& edgeVec, int low, int high ) {
        int i = low;
        int j = high + 1;
        Edge pivot = edgeVec[ low ];

        while ( true ) {
            while ( greater( edgeVec[ ++i ], pivot ) ) if ( i == high ) break;
            while ( greater( pivot, edgeVec[ --j ] ) ) if ( j == low ) break;

            if ( i >= j ) break;

            exchange( edgeVec, i, j );
        }
        exchange( edgeVec, low, j );
        return j;
    }

public:

    KruskalMSTSorting( const EdgeWeightedGraph& G )
        : minEdges( G.getV() ),
          uf( G.getV() )
    {
        forward_list< Edge > edges = G.getEdges();
        vector< Edge > edgeVec( edges.begin(), edges.end() );
        visit( edgeVec, 0, edgeVec.size() - 1 );

        while ( ! edgeVec.empty() && mst.size() < G.getV() - 1 ) {
            Edge e = edgeVec.back();
            edgeVec.pop_back();
            // cout << "DEBUG: Examine Edge e : " << e << endl;
            int v = e.getEither();
            int w = e.getOther( v );
            if ( uf.connected( v, w ) ) continue;
            uf.doUnion( v, w );
            mst.push( e );
            weight += e.getWeight();
        }

        // while ( ! edgeVec.empty() && mst.size() < G.getV() - 1 ) {
        //     Edge e = edgeVec.back();
        //     edgeVec.pop_back();
        //     int v = e.getEither();
        //     int w = e.getOther( v );
        //     if ( uf.connected( v, w ) ) continue;
        //     uf.doUnion( v, w );
        //     mst.push( e );
        // }
    }

    virtual ~KruskalMSTSorting() {
        // not implemented
    }

    void visit( vector< Edge >& edgeVec, int low, int high ) {
        if ( low >= high ) {
            return;
        }
        int j = partition( edgeVec, low, high );
        visit( edgeVec, low, j - 1 );
        visit( edgeVec, j + 1, high );
    }

    double getWeight() const {
        return weight;
    }

    queue< Edge > getEdges() const {
        return mst;
    }

    string toString() const {
        ostringstream oss;
        oss << *this;
        return oss.str();
    }

    friend ostream& operator <<( ostream& out, const KruskalMSTSorting& mst ) {
        out << "\nmst:\n";
        queue< Edge > q = mst.getEdges();
        while ( ! q.empty() ) {
            out << q.front() << ", ";
            q.pop();
        }
        return out;
    }
};

class KruskalMSTPartitioning {
private:

    queue< Edge > mst;
    double weight = 0;

    bool less( const Edge& e1, const Edge& e2 ) const {
        return e1 < e2;
    }

    void exchange( vector< Edge >& a, int i, int j ) {
        Edge temp = a[ i ];
        a[ i ] = a[ j ];
        a[ j ] = temp;
    }

    int partition( vector< Edge >& a, int pivotIndex, int low, int high ) {
        int i = low;
        int j = high + 1;
        Edge pivot = a[ pivotIndex ];

        exchange( a, low, pivotIndex );

        while ( true ) {
            while ( less( a[ ++i ], pivot ) ) if ( i == high ) break;
            while ( less( pivot, a[ --j ] ) ) if ( j == low ) break;

            if ( i >= j ) break;

            exchange( a, i, j );
        }
        exchange( a, low, j );
        return j;
    }

    Edge incrementalQuickSelect( vector< Edge >& a, int k, stack< int >& pivots ) {
        int smallestCorrectPivotIndex = pivots.top();

        if ( k > smallestCorrectPivotIndex ) {
            throw invalid_argument( "Searching for element in the wrong range" );
        }

        if ( k == smallestCorrectPivotIndex ) {
            pivots.pop();
            return a[ k ];
        }

        int pivotIndex = rand() % ( smallestCorrectPivotIndex - k ) + k;
        int correctPivotIndexAfterPartition = partition( a, pivotIndex, k, smallestCorrectPivotIndex - 1 );

        // Invariant: array[0] <= ... <= array[indexToSearch - 1] <= array[indexToSearch, correctPivotIndexAfterPartition - 1]
        // <= array[correctPivotIndexAfterPartition] <= array[correctPivotIndexAfterPartition + 1, pivots.peek() - 1]
        // <= array[pivots.peek(), array.length - 1]
        pivots.push( correctPivotIndexAfterPartition );
        return incrementalQuickSelect( a, k, pivots );
    }

public:

    KruskalMSTPartitioning( const EdgeWeightedGraph& G ) {
        int totalNumberOfEdges = G.getE();
        forward_list< Edge > edges = G.getEdges();
        vector< Edge > edgesVec( edges.begin(), edges.end() );
        WeightedQuickUnionUF uf( G.getV() );
        int kthLightestEdgeToFind = 0;

        stack< int > pivots;
        pivots.push( totalNumberOfEdges );

        while ( mst.size() < G.getV() - 1 ) {
            Edge e = incrementalQuickSelect( edgesVec, kthLightestEdgeToFind, pivots );

            ++kthLightestEdgeToFind;

            int v = e.getEither();
            int w = e.getOther( v );
            if ( uf.connected( v, w ) ) continue;
            uf.doUnion( v, w );
            mst.push( e );
            weight += e.getWeight();
        }
    }

    virtual ~KruskalMSTPartitioning() {
        // not implemented
    }

    string toString() const {
        ostringstream oss;
        oss << *this;
        return oss.str();
    }

    double getWeight() const {
        return weight;
    }

    queue< Edge > getEdges() const {
        return mst;
    }

    friend ostream& operator <<( ostream& out, const KruskalMSTPartitioning& mst ) {
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

    srand( time( NULL ) );
    EdgeWeightedGraph ewGraph( 8 );

    for ( int i = 0; i < 16; ++i ) {
        Edge e( (int)graphArr[ i ][ 0 ], (int)graphArr[ i ][ 1 ], graphArr[ i ][ 2 ] );
        ewGraph.addEdge( e );
    }

    cout << "DEBUG: ewGraph: \n" << ewGraph.toString() << endl;

    KruskalMSTSorting mst( ewGraph );
    cout << "DEBUG: mst: \n" << mst << endl;
    cout << "DEBUG: mst.getWeight(): \n" << mst.getWeight() << endl;

    KruskalMSTPartitioning mst1( ewGraph );
    cout << "DEBUG: mst1: \n" << mst1 << endl;
    cout << "DEBUG: mst1.getWeight(): \n" << mst1.getWeight() << endl;

    return 0;
}
