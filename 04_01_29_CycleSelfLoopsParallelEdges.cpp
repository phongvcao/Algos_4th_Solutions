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

class Cycle {
private:

    vector< bool > marked;
    bool cycle = false;

public:

    Cycle( const Graph& G ) {
        marked.resize( G.getV() );
        for ( int v = 0; v < G.getV(); ++v ) {
            if ( ! marked[ v ] ) {
                dfs( G, v, v );
            }
        }
    }

    virtual ~Cycle() {
        // not implemented
    }

    void dfs( const Graph& G, int v, int u ) {
        marked[ v ] = true;
        for ( int w : G.getAdj( v ) ) {
            // Skip self-loops
            if ( w == v ) {
                continue;
            }

            if ( ! marked[ w ] ) {
                dfs( G, w, v );
            } else if ( w != u ) {
                // Cycle detected
                cycle = true;
                return;
            }
        }
    }

    bool hasCycle() const {
        return cycle;
    }

};

class SymbolGraph {
private:

    SeparateChainingHashST< string, int > st;
    vector< string > keys;
    shared_ptr< Graph > G;

public:

    SymbolGraph( string filename, string delim ) {
        ifstream inFile( filename );
        string lineFile = "";
        while ( getline( inFile, lineFile ) ) {
            size_t pos = 0;
            while ( ( pos = lineFile.find( delim ) ) != string::npos ) {
                string token = lineFile.substr( 0, pos );
                if ( ! st.contains( token ) ) {
                    st.put( token, st.size() );
                }
                lineFile.erase( 0, pos + delim.length() );
            }
            if ( ! st.contains( lineFile ) ) {
                st.put( lineFile, st.size() );
            }
        }

        keys.resize( st.size() );
        queue< string > q = st.getKeys();
        while ( ! q.empty() ) {
            keys[ *( st.get( q.front() ) ) ] = q.front();
            q.pop();
        }

        G = make_shared< Graph >( st.size() );
        ifstream inFileG( filename );
        string lineFileG = "";
        while ( getline( inFileG, lineFileG ) ) {
            size_t pos = 0;
            int v = -1;
            while ( ( pos = lineFileG.find( delim ) ) != string::npos ) {
                string token = lineFileG.substr( 0, pos );
                if ( v == -1 ) {
                    v = *( st.get( token ) );
                } else {
                    G->addEdge( v, *( st.get( token ) ) );
                }
                lineFileG.erase( 0, pos + delim.length() );
            }
            G->addEdge( v, *( st.get( lineFileG ) ) );
        }
    }

    virtual ~SymbolGraph() {
        // not implemented
    }

    int index( string s ) const {
        return *( st.get( s ) );
    }

    string name( int v ) const {
        return keys[ v ];
    }

    shared_ptr< Graph > getG() const {
        return G;
    }

    bool contains( string s ) const {
        return st.contains( s );
    }

    static void testSymbolGraph() {
        SymbolGraph sg( "../routes.txt", " " );
        Cycle cycle( *( sg.getG() ) );

        cout << "DEBUG: cycle: " << cycle.hasCycle() << endl;
    }
};

int main( int argc, char ** argv ) {
    SymbolGraph::testSymbolGraph();

    return 0;
}
