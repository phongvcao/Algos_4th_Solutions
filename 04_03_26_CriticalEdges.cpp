//
// Created by Phong Cao on 2019-03-14.
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
    bool inMST = false;

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

    int isInMST() const {
        return inMST;
    }

    void setInMST( bool inMST ) {
        this->inMST = inMST;
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

    friend bool isSame( const Edge& e1, const Edge& e2 ) {
        return ( ( e1.v == e2.v && e1.w == e2.w ) || ( e1.v == e2.w && e1.w == e2.v ) );
    }

    friend bool isNotSame( const Edge& e1, const Edge& e2 ) {
        return ! isSame( e1, e2 );
    }

    friend bool operator ==( const Edge& e1, const Edge& e2 ) {
        return isSame( e1, e2 );
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
    template <>
    struct hash< Edge > {
        size_t operator()( const Edge& e ) const {
            int hash = 17;
            int v = e.getEither();
            int w = e.getOther( v );
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

    EdgeWeightedGraph( int V, queue< Edge > q )
        : V( V ),
          adj( V )
    {
        while ( ! q.empty() ) {
            addEdge( q.front() );
            q.pop();
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

    void deleteEdge( const Edge& edge ) {
        int v = edge.getEither();
        int w = edge.getOther( v );

        forward_list< Edge > newAdjV;
        for ( Edge e : getAdj( v ) ) {
            if ( isNotSame( e, edge ) ) {
                newAdjV.push_front( e );
            }
        }

        forward_list< Edge > newAdjW;
        for ( Edge e : getAdj( w ) ) {
            if ( isNotSame( e, edge ) ) {
                newAdjW.push_front( e );
            }
        }

        adj[ v ] = newAdjV;
        adj[ w ] = newAdjW;
        --E;
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

class DFSCycle {
private:

    vector< bool > marked;
    vector< Edge > edgeTo;
    queue< Edge > cycle;
    vector< Edge > equalWeightEdgesInCycle;

public:

    DFSCycle( const EdgeWeightedGraph& G, const unordered_set< Edge >& equalWeightEdges )
        : marked( G.getV(), false ),
          edgeTo( G.getV() )
    {
        for ( int v = 0; v < G.getV(); ++v ) {
            if ( ! marked[ v ] ) {
                dfs( G, v, v, equalWeightEdges );
            }
        }
    }

    virtual ~DFSCycle() {
        // not implemented
    }

    void dfs( const EdgeWeightedGraph& G, int v, int u, const unordered_set< Edge >& equalWeightEdges ) {
        marked[ v ] = true;
        for ( Edge e : G.getAdj( v ) ) {
            int w = e.getOther( v );
            if ( hasCycle() ) {
                return;
            } else if ( ! marked[ w ] ) {
                edgeTo[ w ] = e;
                dfs( G, w, v, equalWeightEdges );
            } else if ( w != u ) {
                // cycle detected
                for ( int x = v; x != w; x = edgeTo[ x ].getOther( x ) ) {
                    if ( edgeTo[ x ] ) {
                        cycle.push( edgeTo[ x ] );
                        if ( equalWeightEdges.find( edgeTo[ x ] ) != equalWeightEdges.end() ) {
                            equalWeightEdgesInCycle.push_back( edgeTo[ x ] );
                        }
                    }
                }
                cycle.push( e );
                if ( equalWeightEdges.find( e ) != equalWeightEdges.end() ) {
                    equalWeightEdgesInCycle.push_back( e );
                }
            }
        }
    }

    queue< Edge > getEdges() const {
        return cycle;
    }

    vector< Edge > getEqualWeightEdgesInCycle() {
        return equalWeightEdgesInCycle;
    }


    bool hasCycle() const {
        return ! cycle.empty();
    }

    string toString() const {
        ostringstream oss;
        oss << *this;
        return oss.str();
    }

    friend ostream& operator <<( ostream& out, const DFSCycle& dfsCycle ) {
        out << "\ndfsCycle:\n";
        queue< Edge > q = dfsCycle.getEdges();
        while ( ! q.empty() ) {
            out << q.front() << ", ";
            q.pop();
        }
        return out;
    }
};

//
// Reference: https://stackoverflow.com/a/15722252
//            https://stackoverflow.com/questions/15720155/find-all-critical-edges-of-an-mst
//
class KruskalMST {
private:

    queue< Edge > mst;
    unordered_set< Edge > criticalEdges;
    unordered_set< Edge > nonCriticalEdges;

public:

    KruskalMST( const EdgeWeightedGraph& G ) {
        forward_list< Edge > edges = G.getEdges();
        priority_queue< Edge, vector< Edge >, greater< Edge > > minPQ( edges.begin(), edges.end() );
        WeightedQuickUnionUF uf( G.getV() );

        while ( ! minPQ.empty() && mst.size() < G.getV() - 1 ) {
            unordered_set< Edge > equalWeightEdges;
            equalWeightEdges.insert( minPQ.top() );
            minPQ.pop();
            while ( ! minPQ.empty() && equalWeightEdges.begin() != equalWeightEdges.end() && equalWeightEdges.begin()->getWeight() == minPQ.top().getWeight() ) {
                Edge edge = minPQ.top();
                equalWeightEdges.insert( minPQ.top() );
                minPQ.pop();
            }

            // NOTE: This EdgeWeightedGraph should contain components instead of vertices to increase performance to
            // E log( E )?
            EdgeWeightedGraph ewGraph( G.getV(), mst );
            for ( Edge e : equalWeightEdges ) {
                ewGraph.addEdge( e );
            }

            bool hasCycle = true;
            do {
                DFSCycle cycleFinder( ewGraph, equalWeightEdges );
                hasCycle = cycleFinder.hasCycle();
                if ( ! hasCycle ) {
                    for ( Edge e : equalWeightEdges ) {
                        criticalEdges.insert( e );
                    }
                    break;
                } else {
                    // Check with DFSCycle here
                    vector< Edge > equalWeightEdgesInCycle = cycleFinder.getEqualWeightEdgesInCycle();
                    for ( Edge e : equalWeightEdgesInCycle ) {
                        nonCriticalEdges.insert( e );
                        ewGraph.deleteEdge( e );
                    }
                }
            } while ( hasCycle );

            for ( Edge e : equalWeightEdges ) {
                int v = e.getEither();
                int w = e.getOther( v );
                if ( uf.connected( v, w ) ) continue;
                uf.doUnion( v, w );
                mst.push( e );
            }
        }
    }

    virtual ~KruskalMST() {
        // not implemented
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

    friend ostream& operator <<( ostream& out, const KruskalMST& mst ) {
        out << "\nmst:\n";
        queue< Edge > q = mst.getEdges();
        while ( ! q.empty() ) {
            out << q.front() << ", ";
            q.pop();
        }

        out << "\ncriticalEdges:\n";
        q = mst.getEdges();
        while ( ! q.empty() ) {
            if ( mst.nonCriticalEdges.find( q.front() ) == mst.nonCriticalEdges.end() ) {
                out << q.front() << ", ";
            }
            q.pop();
        }

        out << "\nnonCriticalEdges:\n";
        q = mst.getEdges();
        while ( ! q.empty() ) {
            if ( mst.nonCriticalEdges.find( q.front() ) != mst.nonCriticalEdges.end() ) {
                out << q.front() << ", ";
            }
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
            { 2, 3, 0.19 },
            { 1, 7, 0.19 },
            { 0, 2, 0.19 },
            { 1, 2, 0.36 },
            { 1, 3, 0.19 },
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

    KruskalMST mst2( ewGraph );
    cout << "DEBUG: KruskalMST: \n" << mst2 << endl;
    cout << "DEBUG: KruskalMST.getWeight(): \n" << mst2.getWeight() << endl;

    return 0;
}
