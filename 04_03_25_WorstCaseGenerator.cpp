//
// Created by Phong Cao on 2019-03-13.
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

    friend ostream& operator <<( ostream& out, const Edge& e ) {
        out << fixed << setprecision( 2 );
        out << " | " << e.v << " : " << e.w << " : " << e.weight << " | ";
        return out;
    }

    string toString() const {
        ostringstream oss;
        oss << *this;
        return oss.str();
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

    EdgeWeightedGraph( const EdgeWeightedGraph& G )
        : V( G.getV() )
    {
        forward_list< Edge > edges = G.getEdges();
        for ( Edge e : edges ) {
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

    void addEdge( Edge e ) {
        int v = e.getEither();
        int w = e.getOther( v );
        adj[ v ].push_front( e );
        adj[ w ].push_front( e );
        ++E;
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

    string toString() const {
        ostringstream oss;
        oss << *this;
        return oss.str();
    }

};

template< typename Key >
class IndexMinPQ {
private:

    vector< int > pq;
    vector< int > qp;
    vector< Key > keys;
    int N = 0;

    bool greater( int i, int j ) const {
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
        while ( k > 1 && greater( k / 2, k ) ) {
            exchange( k / 2, k );
            k /= 2;
        }
    }

    void sink( int k ) {
        while ( 2 * k <= N ) {
            int j = 2 * k;
            if ( j < N && greater( j, j + 1 ) ) ++j;
            if ( ! greater( k, j ) ) break;
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

    Key getMin() const {
        return keys[ pq[ 1 ] ];
    }

    int getMinIndex() const {
        return pq[ 1 ];
    }

    void change( int k, Key key ) {
        if ( ! contains( k ) ) throw invalid_argument( "Invalid index for priority queue" );
        keys[ k ] = key;
        swim( qp[ k ] );
        sink( qp[ k ] );
    }

    void deleteKey( int k ) {
        if ( ! contains( k ) ) throw invalid_argument( "Invalid index for priority queue" );
        int index = qp[ k ];
        exchange( index, N-- );
        swim( index );
        sink( index );
        pq[ index ] = -1;
        qp[ k ] = -1;
    }

    string toString() const {
        ostringstream oss;
        oss << *this;
        return oss.str();
    }

    friend ostream& operator <<( ostream& out, const IndexMinPQ< Key >& indexMinPQ ) {
        out << "\npq:\n";
        for ( int i = 0; i < indexMinPQ.pq.size(); ++i ) {
            out << i << " : " << indexMinPQ.pq[ i ] << endl;
        }
        
        out << "\nqp:\n";
        for ( int i = 0; i < indexMinPQ.qp.size(); ++i ) {
            out << i << " : " << indexMinPQ.qp[ i ] << endl;
        }

        out << "\nkeys:\n";
        for ( int i = 0; i < indexMinPQ.keys.size(); ++i ) {
            out << i << " : " << indexMinPQ.keys[ i ] << endl;
        }
        return out;
    }
};

class LazyPrimMST {
private:

    vector< bool > marked;
    queue< Edge > mst;
    priority_queue< Edge, vector< Edge >, greater< Edge > > minPQ;

public:

    LazyPrimMST( const EdgeWeightedGraph& G )
        : marked( G.getV(), false )
    {
        for ( int v = 0; v < G.getV(); ++v ) {
            if ( ! marked[ v ] ) {
                visit( G, v );

                while ( ! minPQ.empty() ) {
                    Edge e = minPQ.top();
                    minPQ.pop();
                    int x = e.getEither();
                    int y = e.getOther( x );
                    if ( marked[ x ] && marked[ y ] ) continue;
                    mst.push( e );
                    if ( ! marked[ x ] ) visit( G, x );
                    if ( ! marked[ y ] ) visit( G, y );
                }
            }
        }
    }

    virtual ~LazyPrimMST() {
        // not implemented
    }

    void visit( const EdgeWeightedGraph& G, int v ) {
        marked[ v ] = true;
        for ( Edge e : G.getAdj( v ) ) {
            minPQ.push( e );
        }
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

    queue< Edge > getEdges() const {
        return mst;
    }

    string toString() const {
        ostringstream oss;
        oss << *this;
        return oss.str();
    }

    friend ostream& operator <<( ostream& out, const LazyPrimMST& mst ) {
        out << "\nmst:\n";
        queue< Edge > q = mst.getEdges();
        while ( ! q.empty() ) {
            out << q.front() << ", ";
            q.pop();
        }
        return out;
    }

};

class PrimMST {
private:

    vector< bool > marked;
    vector< Edge > edgeTo;
    vector< double > distTo;
    IndexMinPQ< double > indexMinPQ;

public:

    PrimMST( const EdgeWeightedGraph& G )
        : marked( G.getV(), false ),
          edgeTo( G.getV() ),
          distTo( G.getV(), numeric_limits< double >::infinity() ),
          indexMinPQ( G.getV() )
    {
        for ( int v = 0; v < G.getV(); ++v ) {
            if ( ! marked[ v ] ) {
                distTo[ v ] = 0;
                indexMinPQ.insert( v, 0 );

                while ( ! indexMinPQ.empty() ) {
                    visit( G, indexMinPQ.delMin() );
                }
            }
        }
    }

    virtual ~PrimMST() {
        // not implemented
    }

    void visit( const EdgeWeightedGraph& G, int v ) {
        marked[ v ] = true;
        for ( Edge e : G.getAdj( v ) ) {
            int w = e.getOther( v );
            if ( marked[ w ] ) continue;
            if ( e.getWeight() < distTo[ w ] ) {
                distTo[ w ] = e.getWeight();
                edgeTo[ w ] = e;
                if ( indexMinPQ.contains( w ) ) {
                    indexMinPQ.change( w, distTo[ w ] );
                } else {
                    indexMinPQ.insert( w, distTo[ w ] );
                }
            }
        }
    }
    
    queue< Edge > getEdges() const {
        queue< Edge > q;
        for ( int v = 0; v < edgeTo.size(); ++v ) {
            if ( edgeTo[ v ] ) {
                q.push( edgeTo[ v ] );
            }
        }
        return q;
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

    string toString() const {
        ostringstream oss;
        oss << *this;
        return oss.str();
    }

    friend ostream& operator <<( ostream& out, const PrimMST& mst ) {
        out << "\nmst:\n";
        queue< Edge > q = mst.getEdges();
        while ( ! q.empty() ) {
            out << q.front() << ", ";
            q.pop();
        }
        return out;
    }

};

class WorstCaseGenerator {
public:

    WorstCaseGenerator() {
        // not implemented
    }

    virtual ~WorstCaseGenerator() {
        // not implemented
    }

    static EdgeWeightedGraph generateWorstCaseLazyPrimMST( int V ) {
        // Worst Case of LazyPrimMST is a complete graph
        EdgeWeightedGraph ewGraph( V );
        for ( int v = 0; v < V; ++v ) {
            for ( int w = v + 1; w < V; ++w ) {
                // No self-loops
                Edge e( v, w, (double)rand() / (double)RAND_MAX );
                ewGraph.addEdge( e );
            }
        }
        return ewGraph;
    }

    static EdgeWeightedGraph generateWorstCasePrimMST( int V ) {
        // Worst Case of PrimMST is a graph that is:
        // - First, a complete graph
        // - Second, the weight from the nearest vertices to the MST is larger than the weight from the furthest MST
        //   to the MST. So for each v and w that are not in the MSt, v-w weight is less than distTo[ w ] which cause
        //   indexMinPQ to insert v-w again and again E times.
        EdgeWeightedGraph ewGraph( V );
        double maxWeight = (double)rand() / (double)RAND_MAX;
        double step = 0.01;
        for ( int v = 0; v < V; ++v ) {
            step += 0.01;
            for ( int w = v + 1; w < V; ++w ) {
                // No self-loops
                double weight = maxWeight - step;
                Edge e( v, w, weight );
                ewGraph.addEdge( e );
            }
        }
        return ewGraph;
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

    LazyPrimMST mst( ewGraph );
    cout << "DEBUG: LazyPrimMST: \n" << mst << endl;
    cout << "DEBUG: LazyPrimMST.getWeight(): \n" << mst.getWeight() << endl;

    PrimMST mst1( ewGraph );
    cout << "DEBUG: PrimMST: \n" << mst1 << endl;
    cout << "DEBUG: PrimMST.getWeight(): \n" << mst1.getWeight() << endl;

    srand( time( NULL ) );
    cout << "DEBUG: Worst-Case LazyPrimMST: \n" << WorstCaseGenerator::generateWorstCaseLazyPrimMST( ewGraph.getV() ) << endl;
    cout << "DEBUG: Worst-Case PrimMST: \n" << WorstCaseGenerator::generateWorstCasePrimMST( ewGraph.getV() ) << endl;

    return 0;
}
