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

class Cell {
private:

    int row = 0;
    int col = 0;
    double value = numeric_limits< double >::infinity();

public:

    Cell() {
        // not implemented
    }

    Cell( int row, int col, double value )
        : row( row ),
          col( col ),
          value( value )
    {
        // not implemented
    }

    Cell( const Cell& c )
        : row( c.row ),
          col( c.col ),
          value( c.value )
    {
        // not implemented
    }

    virtual ~Cell() {
        // not implemented
    }

    int getRow() const {
        return row;
    }

    int getCol() const {
        return col;
    }

    double getValue() const {
        return value;
    }

    string toString() const {
        ostringstream oss;
        oss << *this;
        return oss.str();
    }

    friend ostream& operator <<( ostream& out, const Cell& cell ) {
        out << fixed << setprecision( 2 );
        out << " | " << cell.row << " : " << cell.col << " : " << cell.value << " | ";
        return out;
    }
};

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
    vector< Cell > vertices;

public:

    EdgeWeightedDigraph( int V )
        : V( V ),
          adj( V ),
          vertices( V )
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

    void addVertex( int v, Cell p ) {
        vertices[ v ] = p;
    }

    Cell getVertex( int v ) const {
        return vertices[ v ];
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
        for ( int v = 0; v < G.getV(); ++v ) {
            out << "\n| v : " << v << " : ";
            for ( const DirectedEdge& e : G.getAdj( v ) ) {
                out << e << ", ";
            }
            out << " | ";
        }

        out << "\nvertices:\n";
        for ( const Cell& p : G.vertices ) {
            out << p << ", " << endl;
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

    void change( int k, Key key ) {
        if ( ! contains( k ) ) throw runtime_error( "Invalid index for priority queue" );
        keys[ k ] = key;
        swim( qp[ k ] );
        sink( qp[ k ] );
    }

    int delMin() {
        int min = pq[ 1 ];
        exchange( 1, N-- );
        sink( 1 );
        pq[ N + 1 ] = -1;
        qp[ min ] = -1;
        return min;
    }

    void deleteKey( int k, Key key ) {
        if ( ! contains( k ) ) throw runtime_error( "Invalid index for priority queue" );
        int index = qp[ k ];
        exchange( index, N-- );
        swim( index );
        sink( index );
        pq[ N + 1 ] = -1;
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

class DijkstraSP {
private:

    vector< double > distTo;
    vector< DirectedEdge > edgeTo;
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
        : distTo( G.getV(), numeric_limits< double >::infinity() ),
          edgeTo( G.getV() ),
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

    bool hasPathTo( int v ) const {
        return distTo[ v ] != numeric_limits< double >::infinity();
    }

    stack< DirectedEdge > getPathTo( int v ) const {
        stack< DirectedEdge > path;
        if ( ! hasPathTo( v ) ) return path;
        for ( DirectedEdge e = edgeTo[ v ]; e; e = edgeTo[ e.getFrom() ] ) {
            path.push( e );
        }
        return path;
    }

    double getDistTo( int v ) const {
        return distTo[ v ];
    }

    string toString() const {
        ostringstream oss;
        oss << *this;
        return oss.str();
    }

    friend ostream& operator <<( ostream& out, const DijkstraSP& sp ) {
        out << "\nsp:\n";
        for ( int v = 0; v < sp.edgeTo.size(); ++v ) {
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
        for ( int v = 0; v < sp.edgeTo.size(); ++v ) {
            out << v << " : " << sp.edgeTo[ v ] << endl;
        }
        return out;
    }

};

class ShortestPathInAGrid {

public:

    ShortestPathInAGrid( const vector< vector< int > >& matrixVec, bool onlyRightDown = false ) {
        EdgeWeightedDigraph G( ( int )pow( matrixVec.size(), 2 ) );

        // Loop through all rows
        for ( int i = 0; i < matrixVec.size(); ++i ) {
            // Loop through all columns
            for ( int j = 0; j < matrixVec.size(); ++j ) {
                // Add vertex
                Cell p( i, j, matrixVec[ i ][ j ] );
                int v = matrixVec.size() * i + j;
                G.addVertex( v, p );

                if ( j == 0 ) {
                    // If j is first ele in the row, only make right edge
                    DirectedEdge e1( v, v + 1, matrixVec[ i ][ j ] + matrixVec[ i ][ j + 1 ] );
                    // DirectedEdge e( v + 1, v, matrixVec[ i ][ j ] + matrixVec[ i ][ j + 1 ] );
                    G.addEdge( e1 );
                } else if ( j == matrixVec.size() - 1 ) {
                    // If j is last ele in the row, only make left edge
                    // This is only applicable if onlyRightDown == false
                    if ( ! onlyRightDown ) {
                        DirectedEdge e2( v, v - 1, matrixVec[ i ][ j ] + matrixVec[ i ][ j - 1 ] );
                        // DirectedEdge e( v - 1, v, matrixVec[ i ][ j ] + matrixVec[ i ][ j - 1 ] );
                        G.addEdge( e2 );
                    }
                } else {
                    // If j is not first ele in the row, make edges both left & right
                    DirectedEdge e1( v, v + 1, matrixVec[ i ][ j ] + matrixVec[ i ][ j + 1 ] );
                    // DirectedEdge e( v + 1, v, matrixVec[ i ][ j ] + matrixVec[ i ][ j + 1 ] );
                    G.addEdge( e1 );

                    if ( ! onlyRightDown ) {
                        DirectedEdge e2( v, v - 1, matrixVec[ i ][ j ] + matrixVec[ i ][ j - 1 ] );
                        // DirectedEdge e( v - 1, v, matrixVec[ i ][ j ] + matrixVec[ i ][ j - 1 ] );

                        G.addEdge( e2 );
                    }
                }

                if ( i == 0 ) {
                    // If i is first ele in the column, only make down edge
                    DirectedEdge e1( v, v + matrixVec.size(), matrixVec[ i ][ j ] + matrixVec[ i + 1 ][ j ] );
                    // DirectedEdge e( v + matrixVec.size(), v, matrixVec[ i ][ j ] + matrixVec[ i + 1 ][ j ] );

                    G.addEdge( e1 );
                } else if ( i == matrixVec.size() - 1 ) {
                    if ( ! onlyRightDown ) {
                        // If i is last ele in the column, only make up edge
                        DirectedEdge e2( v, v - matrixVec.size(), matrixVec[ i ][ j ] + matrixVec[ i - 1 ][ j ] );
                        // DirectedEdge e( v - matrixVec.size(), v, matrixVec[ i ][ j ] + matrixVec[ i + 1 ][ j ] );

                        G.addEdge( e2 );
                    }
                } else {
                    // If i is not first ele in the column, make up & down edge
                    DirectedEdge e1( v, v + matrixVec.size(), matrixVec[ i ][ j ] + matrixVec[ i + 1 ][ j ] );
                    G.addEdge( e1 );

                    if ( ! onlyRightDown ) {
                        DirectedEdge e2( v, v - matrixVec.size(), matrixVec[ i ][ j ] + matrixVec[ i - 1 ][ j ] );
                        G.addEdge( e2 );
                    }
                }
            }
        }

        // cout << "DEBUG : G : \n" << G << endl;


        DijkstraSP sp( G, 0 );
        stack< DirectedEdge > s = sp.getPathTo( G.getV() - 1 );
        double dist = sp.getDistTo( G.getV() - 1 );
        cout << "DEBUG: Shortest Path to last vertex : dist : " << dist << endl;
        while ( ! s.empty() ) {
            cout << s.top() << ", ";
            s.pop();
        }
        cout << endl;
        cout << sp << endl;
    }

    virtual ~ShortestPathInAGrid() {
        // not implemented
    }

};

int main( int argc, char ** argv ) {
    vector< vector< int > > matrixVec1 = {
            {  0,  1,  2,  3,  4 },
            {  5,  6,  7,  8,  9 },
            { 10, 11, 12, 13, 14 },
            { 15, 16, 17, 18, 19 },
            { 20, 21, 22, 23, 24 },
    };

    cout << "Shortest Path in Grid : All Directions :" << endl;
    ShortestPathInAGrid sp1( matrixVec1 );

    vector< vector< int > > matrixVec2 = {
            { 24, 23, 22, 21, 20 },
            { 19, 18, 17, 16, 15 },
            { 14, 13, 12, 11, 10 },
            {  9,  8,  7,  6,  5 },
            {  4,  3,  2,  1,  0 },
    };

    cout << "Shortest Path in Grid : Right & Down Only :" << endl;
    ShortestPathInAGrid sp2( matrixVec2, true );

    return 0;
}
