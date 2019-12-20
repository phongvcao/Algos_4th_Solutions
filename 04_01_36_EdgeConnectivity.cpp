//
// Created by Phong Cao on 2019-02-17.
//

#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <string>
#include <memory>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <deque>
#include <queue>
#include <stack>
#include <list>
#include <forward_list>
#include <algorithm>
#include <iterator>
#include <functional>

using std::cout;
using std::cin;
using std::ostream;
using std::istream;
using std::ostringstream;
using std::istringstream;
using std::ofstream;
using std::ifstream;
using std::getline;
using std::sqrt;
using std::pow;
using std::rand;
using std::srand;
using std::time;
using std::endl;
using std::hash;
using std::string;
using std::to_string;
using std::stoi;
using std::stol;
using std::vector;           // Unordered Array
using std::map;              // Ordered Map (Red-Black Tree)
using std::unordered_map;    // HashMap (SeparateChainingHashST)
using std::set;              // Ordered Set (Red-Black Tree)
using std::unordered_set;    // HashSet (SeparateChainingHashST)
using std::pair;
using std::list;             // Doubly-Linked List with size() ( O( 1 ) )
using std::forward_list;     // Singly-Linked List without size() function ( so O( N ) if we need to get size() )
using std::deque;            // Vector of fixed-size Vectors: 1 fixed-size vector for each end of the deque
using std::queue;            // Non-Iterable & Use std::deque as underlying data structure
using std::stack;            // Non-Iterable & Use std::deque as underlying data structure
using std::next;             // Return an advanced iter without changing original iter
using std::fill;
using std::max;
using std::min;
using std::find;
using std::make_shared;
using std::shared_ptr;

template< typename Key, typename Value >
class SeparateChainingHashST {
private:

    class Node;
    typedef shared_ptr< Node > NodePtr;
    NodePtr newNode( Key key, Value value ) {
        return make_shared< Node >( key, value );
    }

    class Node {
    public:
        Key key;
        Value value;
        NodePtr next = NULL;

        Node( Key key, Value value ) {
            this->key = key;
            this->value = value;
        }

        virtual ~Node() {
            // not implemented
        }

        friend ostream& operator <<( ostream& out, const Node& h ) {
            out << " | key : " << h.key << " ; value : " << h.value;
            if ( h.next ) {
                out << " ; next : " << h.next->key;
            } else {
                out << " ; next : null";
            }
            out << " | ";
            return out;
        }

        string toString() const {
            ostringstream oss;
            oss << *this;
            return oss.str();
        }
    };

    int hash( const Key& key ) const {
        return std::hash< Key >{}( key ) % M;
    }

    int M = 17;
    int N = 0;
    vector< NodePtr > st;

public:

    SeparateChainingHashST( int M )
            : M( M )
    {
        st.resize( M );
    }

    SeparateChainingHashST()
            : SeparateChainingHashST( 17 )
    {
        // not implemented
    }

    virtual ~SeparateChainingHashST() {
        // not implemented
    }

    void put( Key key, Value value ) {
        NodePtr ptr = st[ hash( key ) ];
        if ( ptr ) {
            if ( ptr->key == key ) {
                ptr->value = value;
                return;
            }

            while ( ptr->next ) {
                if ( ptr->key == key ) {
                    ptr->value = value;
                    return;
                }

                ptr = ptr->next;
            }
            ptr->next = newNode( key, value );
        } else {
            st[ hash( key ) ] = newNode( key, value );
        }
        ++N;
    }

    void deleteKey( const Key& key ) {
        if ( ! contains( key ) ) return;
        NodePtr ptr = st[ hash( key ) ];
        NodePtr beforePtr = NULL;
        while ( ptr ) {
            if ( key == ptr->key ) {
                if ( beforePtr ) {
                    beforePtr->next = ptr->next;
                } else {
                    st[ hash( key ) ] = NULL;
                }
                --N;
            }
            beforePtr = ptr;
            ptr = ptr->next;
        }
    }

    string toString() const {
        string rv = "\n";
        for ( int i = 0; i < M; ++i ) {
            NodePtr ptr = st[ i ];
            while ( ptr ) {
                rv += "\n| i : " + to_string( i ) + ptr->toString();
                ptr = ptr->next;
            }
        }
        return rv;
    }

    const Value* get( const Key& key ) const {
        NodePtr ptr = st[ hash( key ) ];
        while ( ptr ) {
            if ( ptr->key == key ) {
                return &( ptr->value );
            }
            ptr = ptr->next;
        }
        return NULL;
    }

    bool contains( const Key& key ) const {
        return get( key ) != NULL;
    }

    int size() const {
        return N;
    }

    queue< Key > getKeys() {
        queue< Key > q;
        for ( int i = 0; i < M; ++i ) {
            NodePtr ptr = st[ i ];
            while ( ptr ) {
//                cout << "DEBUG: PUSHING KEY: " << ptr->key << endl;
                q.push( ptr->key );
                ptr = ptr->next;
            }
        }
        return q;
    }
};

class Graph {
private:

    int V = 0;
    int E = 0;
    vector< forward_list< int > > adj;

public:

    Graph( int V )
            : V( V )
    {
        adj.resize( V );
    }

    virtual ~Graph() {
        // not implemented
    }

    int getV() const {
        return V;
    }

    int getE() const {
        return E;
    }

    string toString() const {
        string rv = "\nV : " + to_string( V ) + " ; E : " + to_string( E ) + " ; adj : \n";
        for ( int v = 0; v < V; ++v ) {
            rv += "\n| v : " + to_string( v ) + " : ";
            for ( int w : adj[ v ] ) {
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
        adj[ w ].push_front( v );
        ++E;
    }

    static int degree( const Graph& G, int v ) {
        int deg = 0;
        for ( int w : G.getAdj( v ) ) {
            ++deg;
        }
        return deg;
    }

    static int maxDeg( const Graph& G ) {
        int maxDeg = 0;
        for ( int v = 0; v < G.getV(); ++v ) {
            int deg = degree( G, v );
            if ( maxDeg < deg ) {
                maxDeg = deg;
            }
        }
        return maxDeg;
    }

    static int avgDeg( const Graph& G ) {
        return 2 * G.getE() / G.getV();
    }

    static int numSelfLoops( const Graph& G ) {
        int count = 0;
        for ( int v = 0; v < G.getV(); ++v ) {
            for ( int w : G.getAdj( v ) ) {
                if ( v == w ) {
                    ++count;
                }
            }
        }
        return count / 2;
    }
};

class Bridge {
private:

    vector< int > low;
    vector< int > pre;
    int count = 0;
    int bridges = 0;

public:

    Bridge( const Graph& G ) {
        low.resize( G.getV() );
        pre.resize( G.getV() );
        fill( low.begin(), low.end(), -1 );
        fill( pre.begin(), pre.end(), -1 );
        for ( int v = 0; v < G.getV(); ++v ) {
            if ( pre[ v ] == -1 ) {
                dfs( G, v, v );
            }
        }
    }

    virtual ~Bridge() {
        // not implemented
    }

    void dfs( const Graph& G, int v, int u ) {
        pre[ v ] = count++;
        low[ v ] = pre[ v ];
        for ( int w : G.getAdj( v ) ) {
            if ( pre[ w ] == -1 ) {
                dfs( G, w, v );

                // Update the lowest preorder vertex that can visit v from either v -> w direction or w -> v direction
                low[ v ] = std::min( low[ v ], low[ w ] );

                if ( low[ w ] == pre[ w ] ) {
                    // There is no way to reach w from edges other than v
                    ++bridges;
                }
            } else if ( w != u ) {
                // We can reach v from already-visited vertex w
                low[ v ] = std::min( low[ v ], pre[ w ] );
            }
        }
    }

    string toString() const {
        string rv = "\n";
        return rv;
    }

    int getBridges() const {
        return bridges;
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
            { 7, 9 },
            { 8, 9 }
    };

    Graph graph( 13 );

    for ( int i = 0; i < 16; ++i ) {
        graph.addEdge( graphArr[ i ][ 0 ], graphArr[ i ][ 1 ] );
    }

    cout << "DEBUG: graph: \n" << graph.toString() << endl;

    Bridge bridge( graph );
    cout << "DEBUG: bridge: \n" << bridge.toString() << endl;
    cout << "DEBUG: bridge.getBridges(): \n" << bridge.getBridges() << endl;

    return 0;
}
