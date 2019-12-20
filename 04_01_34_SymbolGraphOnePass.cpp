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

    Value* get( const Key& key ) const {
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
    SeparateChainingHashST< int, forward_list< int > > adj;

public:

    Graph() {
        // not implemented
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

    forward_list< int > getAdj( int v ) const {
        forward_list< int > path;
        forward_list< int >* rv = adj.get( v );
        if ( rv != NULL ) {
            return *rv;
        } else {
            return path;
        }
    }

    string toString() const {
        string rv = "\nV : " + to_string( V ) + " ; E : " + to_string( E ) + " ; adj : \n";
        for ( int v = 0; v < V; ++v ) {
            rv += "\n| v : " + to_string( v ) + " : ";
            for ( int w : getAdj( v ) ) {
                rv += to_string( w ) + ", ";
            }
            rv += " | ";
        }
        return rv;
    }

    void addEdge( int v, int w ) {
        if ( ! adj.contains( v ) ) {
            forward_list< int > list;
            list.assign( { w } );
            adj.put( v, list );
            ++V;
        } else {
            adj.get( v )->push_front( w );
        }

        if ( ! adj.contains( w ) ) {
            forward_list< int > list;
            list.assign( { v } );
            adj.put( w, list );
            ++V;
        } else {
            adj.get( w )->push_front( v );
        }
        ++E;
    }

    static int degree( const Graph& G, int v ) {
        int deg = 0;
        for ( int w : G.getAdj( v ) ) {
            ++deg;
        }
        return deg;
    }

    static int maxDegree( const Graph& G ) {
        int maxDeg = 0;
        for ( int v = 0; v < G.getV(); ++v ) {
            int deg = degree( G, v );
            if ( maxDeg < deg ) {
                maxDeg = deg;
            }
        }
        return maxDeg;
    }

    static int avgDegree( const Graph& G ) {
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

class SymbolGraph {
private:

    SeparateChainingHashST< string, int > st;
    vector< string > keys;
    shared_ptr< Graph > G;

public:

    SymbolGraph( string filename, string delim ) {
        G = make_shared< Graph >();
        ifstream inFile( filename );
        string lineFile = "";
        while ( getline( inFile, lineFile ) ) {
            size_t pos = 0;
            int v = -1;
            while ( ( pos = lineFile.find( delim ) ) != string::npos ) {
                string token = lineFile.substr( 0, pos );
                if ( ! st.contains( token ) ) {
                    st.put( token, st.size() );
                }
                if ( v == -1 ) {
                    v = *( st.get( token ) );
                } else {
                    G->addEdge( v, *( st.get( token ) ) );
                }
                lineFile.erase( 0, pos + delim.length() );
            }

            if ( ! st.contains( lineFile ) ) {
                st.put( lineFile, st.size() );
            }
            G->addEdge( v, *( st.get( lineFile ) ) );
        }

        keys.resize( st.size() );
        queue< string > q = st.getKeys();
        while ( ! q.empty() ) {
            keys[ *( st.get( q.front() ) ) ] = q.front();
            q.pop();
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

};

class BFP {
private:

    vector< bool > marked;
    vector< int > edgeTo;
    int s = 0;

public:

    BFP( const Graph& G, int s )
            : s( s )
    {
        marked.resize( G.getV() );
        edgeTo.resize( G.getV() );
        bfs( G, s );
    }

    virtual ~BFP() {
        // not implemented
    }

    void bfs( const Graph& G, int v ) {
        marked[ v ] = true;
        queue< int > q;
        q.push( v );
        while ( ! q.empty() ) {
            int w = q.front();
            q.pop();
            for ( int x : G.getAdj( w ) ) {
                if ( ! marked[ x ] ) {
                    marked[ x ] = true;
                    edgeTo[ x ] = w;
                    q.push( x );
                }
            }
        }
    }

    string toString() const {
        string rv = "\n";
        for ( int v = 0; v < edgeTo.size(); ++v ) {
            rv += "\n| v : " + to_string( v ) + " : ";
            for ( int w : pathTo( v ) ) {
                rv += to_string( w ) + ", ";
            }
            rv += " | ";
        }
        return rv;
    }

    forward_list< int > pathTo( int v ) const {
        forward_list< int > path;
        if ( ! hasPathTo( v ) ) return path;
        for ( int w = v; w != s; w = edgeTo[ w ] ) {
            path.push_front( w );
        }
        path.push_front( s );
        return path;
    }

    bool hasPathTo( int v ) const {
        return marked[ v ];
    }

};

int main( int argc, char ** argv ) {

    SymbolGraph sg( "../routes.txt", " " );
    shared_ptr< Graph > G = sg.getG();

    string source = "JFK";
    if ( ! sg.contains( source ) ) {
        cout << "DEBUG: " << source << " not in database." << endl;
        return -1;
    }

    cout << "DEBUG: graph G: \n" << G->toString() << endl;

    int s = sg.index( source );
    BFP bfp( *G, s );

    cout << "DEBUG: bfp: \n" << bfp.toString() << endl;

    string dest = "LAS";
    cout << endl;
    cout << dest << endl;
    int t = sg.index( dest );
    if ( bfp.hasPathTo( t ) ) {
        for ( int v : bfp.pathTo( t ) ) {
            cout << "    " << sg.name( v ) << endl;
        }
    }

    return 0;
}
