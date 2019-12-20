//
// Created by Phong Cao on 2019-02-24.
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

class LCAOfDAG {
private:

    vector< bool > marked;
    vector< int > inDegrees;
    vector< int > heights;

    vector< bool > vParents;
    vector< bool > wParents;

    int lca = 0;
    int lcaHeight = 0;
    int v = 0;
    int w = 0;

public:

    LCAOfDAG( const Digraph& G, int v, int w )
        : marked( G.getV(), false ),
          inDegrees( G.getV(), 0 ),
          heights( G.getV(), 0 ),
          vParents( G.getV(), false ),
          wParents( G.getV(), false),
          v( v ),
          w( w )
    {
        // Find all roots ( inDegrees == 0 )
        // Loop through the roots
        //   - Do dfs( root )
        //   - If either v & w are not marked, this cannot be a root leading to LCA
        //   - If both v & w are marked, get the ancestors with greatest heights
        //   - As we move up from the recursive dfs(), wee checked whether

        // Get inDegrees
        for ( int x = 0; x < G.getV(); ++x ) {
            for ( int y : G.getAdj( x ) ) {
                ++inDegrees[ y ];
            }
        }

        // Loop through zero-indegree roots
        for ( int x = 0; x < inDegrees.size(); ++x ) {
            if ( inDegrees[ x ] == 0 ) {
                fill( marked.begin(), marked.end(), false );
                fill( vParents.begin(), vParents.end(), false );
                fill( wParents.begin(), wParents.end(), false );
                dfs( G, x );
            }
        }

    }

    virtual ~LCAOfDAG() {
        // not implemented
    }

    void dfs( const Digraph& G, int x ) {
        marked[ x ] = true;
        // Found v
        if ( x == v ) {
            vParents[ x ] = true;
        }

        // Found w
        if ( x == w ) {
            wParents[ x ] = true;
        }

        for ( int y : G.getAdj( x ) ) {
            // If y was not visited yet, visit it
            if ( ! marked[ y ] ) {
                if ( heights[ y ] < heights[ x ] + 1 ) {
                    heights[ y ] = heights[ x ] + 1;
                }

                dfs( G, y );

                // if y is parent of v, so does x
                if ( vParents[ y ] ) {
                    vParents[ x ] = true;
                }

                // if y is parent of w, so does x
                if ( wParents[ y ] ) {
                    wParents[ x ] = true;
                }

                if ( vParents[ x ] && wParents[ x ] && x != w && x != v ) {
                    if ( heights[ x ] > lcaHeight ) {
                        cout << "DEBUG: Switching lca : " << lca << "; lcaHeight : " << lcaHeight;
                        cout << " to: x : " << x << "; heights[ x ] : " << heights[ x ] << endl;
                        lca = x;
                        lcaHeight = heights[ x ];
                    }
                }
            }
        }
    }

    int getLCA() const {
        return lca;
    }

    int getLCAHeight() const {
        return lcaHeight;
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

    LCAOfDAG lcaOfDAG( dGraph, 11, 12 );
    cout << "DEBUG: lcaOfDAG.getLCA(): \n" << lcaOfDAG.getLCA() << endl;
    cout << "DEBUG: lcaOfDAG.getLCAHeight(): \n" << lcaOfDAG.getLCAHeight() << endl;

    return 0;
}
