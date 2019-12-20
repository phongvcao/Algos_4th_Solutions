//
// Created by Phong Cao on 2019-02-25.
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

    forward_list< int > getAdj( int v ) const {
        return adj[ v ];
    }

    void addEdge( int v, int w ) {
        adj[ v ].push_front( w );
        ++E;
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
};

class ShortestAncestralPath {
private:

    vector< bool > marked;
    vector< int > length;
    vector< int > edgeTo;
    vector< int > vLength;
    vector< int > wLength;
    vector< int > vEdgeTo;
    vector< int > wEdgeTo;
    forward_list< int > ancestralPath;
    int ancestralPathLength = -1;
    int ancestor = -1;
    int sourceV = -1;
    int sourceW = -1;

public:

    ShortestAncestralPath( const Digraph& G, int v, int w )
        : marked( G.getV(), false ),
          length( G.getV(), -1 ),
          edgeTo( G.getV(), -1 ),
          vLength( G.getV(), -1 ),
          wLength( G.getV(), -1 ),
          vEdgeTo( G.getV(), 0 ),
          wEdgeTo( G.getV(), 0 ),
          sourceV( v ),
          sourceW( w )
    {
        // Run bfs() on v
        // bfs() on v should leave behind vLength;
        // bfs() on w would check vLength.
        //   - If -1 => not in the path
        //   - If > 0 => add together wLength[ i ] & vLength[ i ]
        //      - If smaller than currently smallest pathLength, make this the path & make this the x ancestor.
        //      - Otherwise, keep moving forward
        Digraph R = G.reverse();

        length[ v ] = 0;
        bfs( R, v );
        vLength = length;
        vEdgeTo = edgeTo;
        fill( marked.begin(), marked.end(), false );
        fill( length.begin(), length.end(), 0 );

        length[ w ] = 0;
        bfs( R, w, true );
        wLength = length;
        wLength = length;
        wEdgeTo = edgeTo;
    }

    virtual ~ShortestAncestralPath() {
        // not implemented
    }

    void bfs( const Digraph& G, int v, bool doubleCheckVLength = false ) {
        marked[ v ] = true;
        queue< int > q;
        q.push( v );
        while ( ! q.empty() ) {
            int w = q.front();
            q.pop();
            for ( int x : G.getAdj( w ) ) {
                if ( ! marked[ x ] ) {
                    length[ x ] = length[ w ] + 1;
                    marked[ x ] = true;
                    edgeTo[ x ] = w;
                    q.push( x );
                }

                if ( doubleCheckVLength ) {
                    if ( vLength[ x ] > 0 ) {
                        // x has been visited before by dfs( v ). This means x is on shortest path of v
                        // check if combo vLength[ x ] + length[ x ] , ancestralPathLength.
                        if ( ancestralPathLength == -1 || ancestralPathLength > vLength[ x ] + length[ x ] ) {
                            ancestralPathLength = vLength[ x ] + length[ x ];
                            ancestor = x;
                        }
                    }
                }
            }
        }
    }

    int getAncestor() const {
        return ancestor;
    }

    int getAncestralPathLength() const {
        return ancestralPathLength;
    }

    vector< int > getWLength() const {
        return wLength;
    }

    vector< int > getVLength() const {
        return vLength;
    }

    forward_list< int > getVAncestralPath() const {
        forward_list< int > path;
        for ( int v = ancestor; v != sourceV; v = vEdgeTo[ v ] ) {
            path.push_front( v );
        }
        path.push_front( sourceV );
        return path;
    }

    forward_list< int > getWAncestralPath() const {
        forward_list< int > path;
        for ( int v = ancestor; v != sourceW; v = wEdgeTo[ v ] ) {
            path.push_front( v );
        }
        path.push_front( sourceW );
        return path;
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

    ShortestAncestralPath sap( dGraph, 4, 10 );
    cout << "DEBUG: sap.getAncestor(): \n" << sap.getAncestor() << endl;
    cout << "DEBUG: sap.getAncestralPathLength(): \n" << sap.getAncestralPathLength() << endl;

    cout << "DEBUG: vAncestralPath: \n";
    for ( int v : sap.getVAncestralPath() ) {
        cout << v << ", ";
    }
    cout << endl;

    cout << "DEBUG: wAncestralPath: \n";
    for ( int v : sap.getWAncestralPath() ) {
        cout << v << ", ";
    }
    cout << endl;

    return 0;
}
