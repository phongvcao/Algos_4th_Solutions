//
// Created by Phong Cao on 2019-03-11.
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

    int getOther( int vertex ) const {
        if ( v == vertex ) {
            return w;
        } else if ( w == vertex ) {
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
        return isSame( e1, e2 );
    }

    friend bool operator !=( const Edge& e1, const Edge& e2 ) {
        return ! ( e1 == e2 );
    }

    friend bool isSame( const Edge& e1, const Edge& e2 ) {
        return ( e1.v == e2.v && e1.w == e2.w ) || ( e1.v == e2.w && e1.w == e2.v );
    }

    friend bool isNotSame( const Edge& e1, const Edge& e2 ) {
        return ! isSame( e1, e2 );
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
        size_t operator ()( const Edge& e ) const {
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

    string toString() const {
        ostringstream oss;
        oss << *this;
        return oss.str();
    }

    friend ostream& operator <<( ostream& out, const EdgeWeightedGraph& G ) {
        out << "\n | V : " << G.getV() << " ; E : " << G.getE() << " ; adj : \n";
        for ( int v = 0; v < G.getV(); ++v ) {
            out << "\n| v : " << v << " : ";
            for ( const Edge& e : G.getAdj( v ) ) {;
                out << e << ", ";
            }
            out << " | ";
        }
        return out;
    }

};

template< typename Key >
class SeparateChainingHashST {
private:

    class Node;
    typedef shared_ptr< Node > NodePtr;
    NodePtr newNode( Key key ) {
        return make_shared< Node >( key );
    }

    class Node {
    public:
        const Key* key = NULL;
        NodePtr next = NULL;

        Node( const Key& key )
            : key( &key )
        {
            // not implemented
        }

        virtual ~Node() {
            // not implemented
        }

        friend ostream& operator <<( ostream& out, const Node& h ) {
            out << " | key : " << *( h.key );
            if ( h.next ) {
                out << " ; next : " << *( h.next.key );
            } else {
                out << " ; next : null";
            }
            out << " | ";
        }

        string toString() const {
            ostringstream oss;
            oss << *this;
            return oss.str();
        }
    };

    int hash( const Key& key ) {
        return std::hash< Key >{}( key ) % M;
    }

    vector< NodePtr > st;
    int N = 0;
    int M = 0;

public:

    SeparateChainingHashST( int cap )
        : M( cap ),
          st( cap )
    {
        // not implemented
    }

    virtual ~SeparateChainingHashST() {
        // not implemented
    }

    void put( const Key& key ) {
        NodePtr ptr = st[ hash( key ) ];
        if ( ptr ) {
            if ( *( ptr->key ) == key ) {
                return;
            }

            while ( ptr->next ) {
                if ( *( ptr->key ) == key ) {
                    return;
                }
                ptr = ptr->next;
            }
            ptr->next = newNode( key );
        } else {
            st[ hash( key ) ] = newNode( key );
        }
        ++N;
    }

    void deleteKey( const Key& key ) {
        if ( ! contains( key ) ) return;
        NodePtr ptr = st[ hash( key ) ];
        NodePtr beforePtr = NULL;

        while ( ptr ) {
            if ( *( ptr->key ) == key ) {
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

    bool contains( const Key& key ) const {
        NodePtr ptr = st[ hash( key ) ];
        while ( ptr ) {
            if ( *( ptr->key ) == key ) {
                return true;
            }
            ptr = ptr->next;
        }
        return false;
    }

    int size() const {
        return N;
    }

    bool empty() const {
        return size() == 0;
    }

    int capacity() const {
        return M;
    }

    queue< Key > getKeys() const {
        queue< Edge > q;
        for ( int i = 0; i < st.size(); ++i ) {
            NodePtr ptr = st[ i ];
            while ( ptr ) {
                q.push( *( ptr->key ) );
                ptr = ptr->next;
            }
        }
        return q;
    }

    string toString() const {
        ostringstream oss;
        oss << *this;
        return oss.str();
    }

    friend ostream& operator <<( ostream& out, const SeparateChainingHashST< Key >& hashST ) {
        for ( int i = 0; i < hashST.st.size(); ++i ) {
            NodePtr ptr = hashST.st[ i ];
            if ( ptr ) {
                out << "\n | i : " << i << " : ";
            }
            while ( ptr ) {
                out << *( ptr->key ) << ", ";
                ptr = ptr->next;
            }
            out << " | ";
        }
        return out;
    }
};

class DFSCycle {
private:

    vector< bool > marked;
    vector< Edge > edgeTo;
    queue< Edge > cycle;
    Edge maxEdge;

public:

    DFSCycle( const EdgeWeightedGraph& G )
        : marked( G.getV(), false ),
          edgeTo( G.getV() )
    {
        for ( int v = 0; v < G.getV(); ++v ) {
            if ( ! marked[ v ] ) {
                dfs( G, v, v );
            }
        }
    }

    DFSCycle( unordered_set< Edge > mst, int V )
        : marked( V, false ),
          edgeTo( V )
    {
        EdgeWeightedGraph G( V );
        for ( const Edge& e : mst ) {
            Edge newEdge( e );
            G.addEdge( newEdge );
        }

        for ( int v = 0; v < G.getV(); ++v ) {
            if ( ! marked[ v ] ) {
                dfs( G, v, v );
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
                for ( int x = v; x != w; x = edgeTo[ x ].getOther( x ) ) {
                    if ( edgeTo[ x ] ) {
                        cycle.push( edgeTo[ x ] );
                    }

                    if ( ! maxEdge || maxEdge < edgeTo[ x ] ) {
                        maxEdge = edgeTo[ x ];
                    }
                }
                if ( maxEdge < e ) {
                    maxEdge = e;
                }
                cycle.push( e );
            }
        }
    }

    Edge getMaxEdge() const {
        return maxEdge;
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

    friend ostream& operator <<( ostream& out, const DFSCycle& cycle ) {
        out << "\ncycle:\n";
        queue< Edge > q = cycle.getCycle();
        while ( ! q.empty() ) {
            out << q.front() << ", ";
            q.pop();
        }
        return out;
    }
};

class VyssotskyMST {
private:

    vector< bool > marked;
    vector< Edge > edgeTo;
    unordered_set< Edge > mst;

public:

    VyssotskyMST( const EdgeWeightedGraph& G )
        : marked( G.getV(), false ),
          edgeTo( G.getV() )
    {
        forward_list< Edge > all = G.getEdges();
        for ( Edge e : all ) {
            // Add edge to mst first
            mst.insert( e );

            int v = e.getEither();
            int w = e.getOther( v );
            if ( marked[ v ] && marked[ w ] ) {
                // cycle detected
                // cout << "DEBUG: BEFORE ERASING: mst: " << toString() << endl;
                DFSCycle dfsCycle( mst, G.getV() );
                Edge maxEdge = dfsCycle.getMaxEdge();
                mst.erase( maxEdge );
                // cout << "DEBUG: ERASING: maxEdge: " << maxEdge << endl;
            }

            marked[ v ] = true;
            marked[ w ] = true;
            // cout << "DEBUG: mst: " << toString() << endl;
        }
    }

    virtual ~VyssotskyMST() {
        // not implemented
    }

    double getWeight() const {
        double weight = 0;
        for ( const Edge& e : mst ) {
            weight += e.getWeight();
        }
        return weight;
    }

    queue< Edge > getEdges() const {
        queue< Edge > q;
        for ( unordered_set< Edge >::iterator iter = mst.begin(); iter != mst.end(); ++iter ) {
            q.push( *iter );
        }
        return q;
    }

    string toString() const {
        ostringstream oss;
        oss << *this;
        return oss.str();
    }

    friend ostream& operator<<( ostream& out, const VyssotskyMST& mst ) {
        out << "\nmst:\n";
        for ( const Edge& e : mst.mst ) {
            out << e << ", ";
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

    VyssotskyMST mst( ewGraph );
    cout << "DEBUG: mst: \n" << mst << endl;
    cout << "DEBUG: mst.getWeight(): \n" << mst.getWeight() << endl;

    return 0;
}
