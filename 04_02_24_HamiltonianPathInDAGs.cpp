//
// Created by Phong Cao on 2019-02-26.
//


#include <iostream>
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

//----<iostream>------------//
using std::cout;
using std::cin;
using std::endl;
using std::ostream;
using std::istream;

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

//--------------------------//

class Digraph {
private:

    int V = 0;
    int E = 0;
    vector< forward_list< int > > adj;

public:

    Digraph( int V )
        : V( V ),
          adj( V )
    {
        // not implemented
    }

    virtual ~Digraph() {
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

    void addEdge( int v, int w ) {
        adj[ v ].push_front( w );
        ++E;
    }

    string toString() const {
        string rv = "\n";
        for ( int v = 0; v < V; ++v ) {
            rv += "\n| v : " + to_string( v ) + " : ";
            for ( int w : getAdj( v ) ) {
                rv += to_string( w ) + ", ";
            }
            rv += " | ";
        }
        return rv;
    }

    Digraph reverse() const {
        Digraph R( V );
        for ( int v = 0; v < V; ++v ) {
            for ( int w : getAdj( v ) ) {
                R.addEdge( w, v );
            }
        }
        return R;
    }

    bool hasEdge( int v, int w ) const {
        for ( int x : getAdj( v ) ) {
            if ( x == w ) {
                return true;
            }
        }
        return false;
    }
};

class DirectedCycle {
private:

    vector< bool > marked;
    vector< int > edgeTo;
    vector< bool > onStack;
    stack< int > cycle;

public:

    DirectedCycle( const Digraph& G )
        : marked( G.getV(), false ),
          edgeTo( G.getV(), -1 ),
          onStack( G.getV(), false )
    {
        for ( int v = 0; v < G.getV(); ++v ) {
            if ( ! marked[ v ] ) {
                dfs( G, v );
            }
        }
    }

    void dfs( const Digraph& G, int v ) {
        marked[ v ] = true;
        onStack[ v ] = true;

        for ( int w : G.getAdj( v ) ) {
            if ( hasCycle() ) {
                return;
            } else if ( ! marked[ w ] ) {
                edgeTo[ w ] = v;
                dfs( G, w );
            } else if ( onStack[ w ] ) {
                for ( int x = v; x != w; x = edgeTo[ x ] ) {
                    cycle.push( x );
                }
                cycle.push( w );
                cycle.push( v );
            }
        }

        onStack[ v ] = false;
    }

    bool hasCycle() const {
        return ! cycle.empty();
    }

    stack< int > getCycle() const {
        return cycle;
    }
};

class DepthFirstOrder {
private:

    vector< bool > marked;
    queue< int > pre;
    queue< int > post;
    stack< int > reversePost;

public:

    DepthFirstOrder( const Digraph& G )
        : marked( G.getV(), false )
    {
        for ( int v = 0; v < G.getV(); ++v ) {
            if ( ! marked[ v ] ) {
                dfs( G, v );
            }
        }
    }

    void dfs( const Digraph& G, int v ) {
        pre.push( v );

        marked[ v ] = true;
        for ( int w : G.getAdj( v ) ) {
            if ( ! marked[ w ] ) {
                dfs( G, w );
            }
        }

        post.push( v );
        reversePost.push( v );
    }

    queue< int > getPre() const {
        return pre;
    }

    queue< int > getPost() const {
        return post;
    }

    stack< int > getReversePost() const {
        return reversePost;
    }
};

class TopologicalSort {
private:

    stack< int > order;

public:

    TopologicalSort( const Digraph& G ) {
        DirectedCycle cycleFinder( G );
        if ( ! cycleFinder.hasCycle() ) {
            DepthFirstOrder dfo( G.reverse() );
            order = dfo.getReversePost();
        }
    }

    virtual ~TopologicalSort() {
        // not implemented
    }

    stack< int > getOrder() const {
        return order;
    }

    bool isDAG() const {
        return ! order.empty();
    }
};

// 4.2.24. Hamiltonian path in DAGs. Given a DAG, design a linear-time algorithm to
// determine whether there is a directed path that visits each vertex exactly once.
//
// Answer : Compute a topological sort and check if there is an edge between each
// consecutive pair of vertices in the topological order.

class HamiltonPath {
private:

    bool hamilton = true;

public:

    HamiltonPath( const Digraph& G ) {
        TopologicalSort topo( G );
        if ( topo.isDAG() ) {
            stack< int > order = topo.getOrder();
            int v = order.top();
            order.pop();
            while ( ! order.empty() ) {
                int w = order.top();
                order.pop();
                if ( ! G.hasEdge( w, v ) ) {
                    hamilton = false;
                    break;
                }
                v = w;
            }
        }
    }

    virtual ~HamiltonPath() {
        // not implemented
    }

    bool hasHamilton() const {
        return hamilton;
    }
};

int main( int argc, char ** argv ) {

    int graphArr[ 16 ][ 2 ] = {
            { 0, 5 },
            { 4, 3 },
            { 0, 1 },
            { 9, 12 },
            { 6, 4 },
            { 5, 4 },
            { 0, 2 },
            { 11, 12 },
            { 9, 10 },
            { 0, 6 },
            { 7, 8 },
            { 9, 11 },
            { 5, 3 },
            { 6, 7 },
            { 6, 9 },
            { 8, 9 }
    };

    Digraph dGraph( 13 );

    for ( int i = 0; i < 16; ++i ) {
        dGraph.addEdge( graphArr[ i ][ 0 ], graphArr[ i ][ 1 ] );
    }

    cout << "DEBUG: dGraph: \n" << dGraph.toString() << endl;
    cout << "DEBUG: dGraph.reverse(): \n" << dGraph.reverse().toString() << endl;

    HamiltonPath hPath( dGraph );
    cout << "DEBUG: hPath.hasHamilton(): \n" << hPath.hasHamilton() << endl;

    int graphArr1[ 12 ][ 2 ] = {
            { 0, 1 },
            { 1, 2 },
            { 2, 3 },
            { 3, 4 },
            { 4, 5 },
            { 5, 6 },
            { 6, 7 },
            { 7, 8 },
            { 8, 9 },
            { 9, 10 },
            { 10, 11 },
            { 11, 12 },
    };

    Digraph dGraph1( 13 );

    for ( int i = 0; i < 12; ++i ) {
        dGraph1.addEdge( graphArr1[ i ][ 0 ], graphArr1[ i ][ 1 ] );
    }

    cout << "DEBUG: dGraph1: \n" << dGraph1.toString() << endl;
    cout << "DEBUG: dGraph1.reverse(): \n" << dGraph1.reverse().toString() << endl;

    HamiltonPath hPath1( dGraph1 );
    cout << "DEBUG: hPath1.hasHamilton(): \n" << hPath1.hasHamilton() << endl;

    return 0;
}
