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

class DirectedCycle {
private:

    vector< bool > marked;
    vector< int > edgeTo;
    vector< bool > onStack;
    stack< int > cycle;
    int s = 0;

public:

    DirectedCycle( const Digraph& G, int s )
        : marked( G.getV(), false ),
          edgeTo( G.getV(), -1 ),
          onStack( G.getV(), false ),
          s( s )
    {
        dfs( G, s );
    }

    virtual ~DirectedCycle() {
        // not implemented
    }

    void dfs( const Digraph& G, int v ) {
        marked[ v ] = true;
        onStack[ v ] = true;

        for ( int w : G.getAdj( v ) ) {
            if ( hasCycle() ) {
                return;
            }
            else if ( ! marked[ w ] ) {
                edgeTo[ w ] = v;
                dfs( G, w );
            } else if ( onStack[ w ] && w == s ) {
                // cycle detected
                for ( int x = v; x != w; x = edgeTo[ x ] ) {
                    cycle.push( x );
                }
                cycle.push( w );
                cycle.push( v );
            }
        }

        onStack[ v ] = false;
    }

    stack< int > getCycle() const {
        return cycle;
    }

    bool hasCycle() const {
        return ! cycle.empty();
    }

    bool isMarked( int v ) const {
        return marked[ v ];
    }

    vector< bool > getMarked() const {
        return marked;
    }
};

class Cycle {
public:
    vector< int > cycle;

    Cycle( vector< int > cycle )
        : cycle( cycle )
    {
        // not implemented
    }

    virtual ~Cycle() {
        // not implemented
    }

    friend bool operator ==( const Cycle& c1, const Cycle& c2 ) {
        vector< int > c1Vec = c1.cycle;
        vector< int > c2Vec = c2.cycle;
        if ( c1Vec.size() != c2Vec.size() ) {
            return false;
        }
        c1Vec.pop_back();
        c2Vec.pop_back();
        sort( c1Vec.begin(), c1Vec.end() );
        sort( c2Vec.begin(), c2Vec.end() );
        for ( int i = 0; i < c1Vec.size(); ++i ) {
            if ( c1Vec[ i ] != c2Vec[ i ] ) {
                return false;
            }
        }
        return true;
    }
};

namespace std {
    template<>
    struct hash< Cycle > {
        size_t operator ()( const Cycle& v1 ) const {
            vector< int > v1Cycle = v1.cycle;
            v1Cycle.pop_back();
            sort( v1Cycle.begin(), v1Cycle.end() );

            int hash = 17;

            for ( int i = 0; i != v1Cycle.size(); ++i ) {
                hash = 31 * hash + std::hash< int >{}( v1Cycle[ i ] );
            }
            return hash;
        }
    };
}

class SCC {
private:

    unordered_set< Cycle > scc;

public:

    SCC( const Digraph& G ) {
        for ( int v = 0; v < G.getV(); ++v ) {
            vector< bool > marked( G.getV(), false );
            vector< int > edgeTo( G.getV(), -1 );
            vector< bool > onStack( G.getV(), false );
            dfs( G, v, v, marked, edgeTo, onStack );
        }
    }

    void dfs( const Digraph& G, int v, int s, vector< bool > marked, vector< int > edgeTo, vector< bool > onStack ) {
        marked[ v ] = true;
        onStack[ v ] = true;

        for ( int w : G.getAdj( v ) ) {
            if ( ! marked[ w ] ) {
                edgeTo[ w ] = v;
                dfs( G, w, s, marked, edgeTo, onStack );
            } else if ( onStack[ w ] && w == s ) {
                // cycle detected
                vector< int > cycle;
                for ( int x = v; x != w; x = edgeTo[ x ] ) {
                    cycle.push_back( x );
                }
                cycle.push_back( w );
                cycle.push_back( v );
                Cycle cycleObj( cycle );

                scc.insert( cycleObj );
            }
        }

        onStack[ v ] = false;
    }

    virtual ~SCC() {
        // not implemented
    }

//    bool contains( vector< int > cycle ) {
//        for ( int i = 0; i < scc.size(); ++i ) {
//            bool found = true;
//            if ( cycle.size() != scc[ i ].size() ) {
//                continue;
//            }
//
//            vector< int > sccVec = scc[ i ];
//            cycle.pop_back();
//            sccVec.pop_back();
//            sort( cycle.begin(), cycle.end() );
//            sort( sccVec.begin(), sccVec.end() );
//            for ( int j = 0; j < cycle.size(); ++j ) {
//                if ( cycle[ j ] != sccVec[ j ] ) {
//                    found = false;
//                    break;
//                }
//            }
//
//            if ( ! found ) {
//                continue;
//            } else {
//                cout << "DEBUG: FOUND: " << endl;
//                for ( int j = 0; j < cycle.size(); ++j ) {
//                    cout << cycle[ j ] << ", ";
//                }
//                cout << endl;
//
//                return found;
//            }
//        }
//        cout << "DEBUG: NOT FOUND: " << endl;
//        for ( int j = 0; j < cycle.size(); ++j ) {
//            cout << cycle[ j ] << ", ";
//        }
//        cout << endl;
//        return false;
//    }

    unordered_set< Cycle > getSCC() const {
        return scc;
    }
};

int main( int argc, char ** argv ) {

    int graphArr[ 16 ][ 2 ] = {
            { 0, 1 },
            { 1, 2 },
            { 2, 0 },
            { 1, 3 },
            { 3, 4 },
            { 4, 5 },
            { 5, 6 },
            { 6, 2 },
            { 3, 7 },
            { 7, 8 },
            { 8, 9 },
            { 9, 6 },
            { 3, 10 },
            { 10, 11 },
            { 11, 12 },
            { 12, 6 }
    };

    Digraph dGraph( 13 );

    for ( int i = 0; i < 16; ++i ) {
        dGraph.addEdge( graphArr[ i ][ 0 ], graphArr[ i ][ 1 ] );
    }

    cout << "DEBUG: dGraph: \n" << dGraph.toString() << endl;
    cout << "DEBUG: dGraph.reverse(): \n" << dGraph.reverse().toString() << endl;

    DirectedCycle dCycle( dGraph, 7 );
    cout << "DEBUG: dCycle.hasCycle(): \n" << dCycle.hasCycle() << endl;
    cout << "DEBUG: dCycle.getCycle(): \n";
    stack< int > s = dCycle.getCycle();
    while ( ! s.empty() ) {
        cout << s.top() << ", ";
        s.pop();
    }
    cout << endl;
    cout << endl;

    SCC scc( dGraph );
    unordered_set< Cycle > sccVec = scc.getSCC();
    cout << "DEBUG: scc.getSCC(): \n";
    for ( auto iter = sccVec.begin(); iter != sccVec.end(); ++iter ) {
        for ( int i = 0; i < iter->cycle.size(); ++i ) {
            cout << iter->cycle[ i ] << ", ";
        }
        cout << endl;
    }
    cout << endl;

    return 0;
}
