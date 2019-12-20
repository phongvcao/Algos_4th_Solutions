//
// Created by Phong Cao on 2019-03-18.
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
        // not implementd
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
        return ( e1.v == e2.v && e1.w == e2.w );
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
    int count = 0;

public:

    DFSCycle( const EdgeWeightedGraph& G )
        : marked( G.getV(), false ),
          edgeTo( G.getV() )
    {
        for ( int v = 0; v < G.getV(); ++v ) {
            if ( ! marked[ v ] ) {
                dfs( G, v, v );
                ++count;
            }
        }
    }

    virtual ~DFSCycle() {
        // not implemented
    }

    void dfs( const EdgeWeightedGraph& G, int v, int u ) {
        marked[ v ] = true;
        for ( Edge e : G.getAdj( v ) ) {
            int w = e.getOther( v );
            if ( hasCycle() ) {
                return;
            } else if ( ! marked[ w ] ) {
                edgeTo[ w ] = e;
                dfs( G, w, v );
            } else if ( w != u ) {
                // cycle detected
                for ( int x = v; x != w; x = edgeTo[ x ].getOther( x ) ) {
                    if ( edgeTo[ x ] ) {
                        cycle.push( edgeTo[ x ] );
                    }
                }
                cycle.push( e );
            }
        }
    }

    int getCount() const {
        return count;
    }

    queue< Edge > getCycle() const {
        return cycle;
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
        queue< Edge > q = dfsCycle.getCycle();
        out << "\ncycle:\n";
        while ( ! q.empty() ) {
            out << q.front() << ", ";
            q.pop();
        }
        return out;
    }
};

class KruskalMST {
private:

    queue< Edge > mst;
    double weight = 0;

public:

    KruskalMST( const EdgeWeightedGraph& G ) {
        forward_list< Edge > edges = G.getEdges();
        priority_queue< Edge, vector< Edge >, greater< Edge > > minPQ( edges.begin(), edges.end() );
        WeightedQuickUnionUF uf( G.getV() );

        while ( ! minPQ.empty() && mst.size() < G.getV() - 1 ) {
            Edge e = minPQ.top();
            minPQ.pop();
            int v = e.getEither();
            int w = e.getOther( v );
            if ( uf.connected( v, w ) ) continue;
            uf.doUnion( v, w );
            mst.push( e );
            weight += e.getWeight();
        }
    }

    virtual ~KruskalMST() {
        // not implemented
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

    friend ostream& operator <<( ostream& out, const KruskalMST& mst ) {
        out << "\nmst:\n";
        queue< Edge > q = mst.getEdges();
        while ( ! q.empty() ) {
            out << q.front() << ", ";
            q.pop();
        }
        return out;
    }

    static bool check( const EdgeWeightedGraph& G, queue< Edge > mst ) {
        // CHECK WHETHER mst IS A MINIMUM SPANNING TREE

        // First construct ewGraph which is a graph of only the MST
        EdgeWeightedGraph ewGraph( G.getV() );
        while ( ! mst.empty() ) {
            try {
                ewGraph.addEdge( mst.front() );
                mst.pop();
            } catch ( const invalid_argument& e ) {
                cout << e.what() << endl;
                return false;
            }
        }

        // First check whether mst contains all vertices in G
        // Now check whether mst contains any cycle and also if all edges are connected
        // These 3 tasks can be grouped into the cycleFinder ( DFSCycle )
        // If mst doesn't contain all vertices in G, there will be more than 1 component
        // in ewGraph.
        DFSCycle cycleFinder( ewGraph );
        if ( cycleFinder.getCount() > 1 ) {
            return false;
        }

        if ( cycleFinder.hasCycle() ) {
            return false;
        }

        // Remove each edge from ewGraph & run WeightedQuickUnionUF to check how many
        // components it has. If after removing edge e, it has anything different from 2
        // components, then it's not MST.
        // Also, we have to check whether removing edge e makes the 2 components disjoint.
        // If not, then it's not MST.
        forward_list< Edge > edges = ewGraph.getEdges();
        for ( int i = 0; i < ewGraph.getE(); ++i ) {
            int j = 0;
            WeightedQuickUnionUF uf( ewGraph.getV() );
            Edge skippedEdge;
            for ( const Edge& e : edges ) {
                if ( i != j ) {
                    int v = e.getEither();
                    int w = e.getOther( v );
                    uf.doUnion( v, w );
                } else {
                    skippedEdge = e;
                }
                ++j;
            }
            if ( uf.getCount() != 2 ) {
                return false;
            }

            // Now we have to loop through every edge in component 1 & get its
            // adjacent-component-2 edge. Make sure the weights of all these
            // adjacent-component-2 edges are smaller than weight of edge e.
            for ( const Edge& e : edges ) {
                int v = e.getEither();
                int w = e.getOther( v );
                if ( uf.find( v ) != uf.find( w ) ) {
                    if ( e.getWeight() < skippedEdge.getWeight() ) {
                        return false;
                    }
                }
            }
        }

        // If all above conditions are valid, then mst is a Minimum Spanning Tree
        return true;
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

    KruskalMST mst3( ewGraph );
    cout << "DEBUG: KruskalMST: \n" << mst3 << endl;
    cout << "DEBUG: KruskalMST.getWeight(): \n" << mst3.getWeight() << endl;
    cout << "DEBUG: KruskalMST.check( mst3.getEdges() ): \n" << KruskalMST::check( ewGraph, mst3.getEdges() ) << endl;

    queue< Edge > q;
    Edge e( 0, 7, 0.16 );
    cout << "DEBUG: KruskalMST.check( q ): \n" << KruskalMST::check( ewGraph, q ) << endl;

    return 0;
}
