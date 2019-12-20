//
// Created by Phong Cao on 2019-04-01.
//

// uncomment to disable assert()
// #define NDEBUG
#include <cassert>
#include <iostream>
#include <cstdio>
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

//----<cstdio>--------------//
using std::printf;
using std::fprintf;
using std::sprintf;
using std::snprintf;

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
using std::log;             // log( <arg> )
using std::exp;             // e ^ <arg>
using std::abs;

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
using std::prev;            // Return an decremented iter without changin original iter
using std::distance;        // Calculate distance between 2 iterators

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
using std::runtime_error;
using std::invalid_argument;
using std::out_of_range;

//----<limits>--------------//
using std::numeric_limits;

//----<numeric>-------------//
using std::iota;
using std::gcd;
using std::lcm;

//--------------------------//

class DirectedEdge {
private:

    int v = 0;
    int w = 0;
    double weight = numeric_limits< double >::infinity();

public:

    DirectedEdge() {
        // not implemented
    }

    DirectedEdge( int v, int w, double weight )
        : v( v ),
          w( w ),
          weight( weight )
    {
        // not implemented
    }

    DirectedEdge( const DirectedEdge& e )
        : v( e.v ),
          w( e.w ),
          weight( e.weight )
    {
        // not implemented
    }

    virtual ~DirectedEdge() {
        // not implemented
    }

    int getFrom() const {
        return v;
    }

    int getTo() const {
        return w;
    }

    double getWeight() const {
        return weight;
    }

    operator bool() const {
        return weight != numeric_limits< double >::infinity();
    }

    string toString() const {
        ostringstream oss;
        oss << *this;
        return oss.str();
    }

    friend ostream& operator <<( ostream& out, const DirectedEdge& e ) {
        out << fixed << setprecision( 2 );
        out << " | " << e.v << " : " << e.w << " : " << e.weight << " | ";
        return out;
    }
};

class EdgeWeightedDigraph {
private:

    int V = 0;
    int E = 0;
    vector< forward_list< DirectedEdge > > adj;

public:

    EdgeWeightedDigraph( int V )
        : V( V ),
          adj( V )
    {
        // not implemented
    }

    virtual ~EdgeWeightedDigraph() {
        // not implemented
    }

    int getV() const {
        return V;
    }

    int getE() const {
        return E;
    }

    forward_list< DirectedEdge > getAdj( int v ) const {
        return adj[ v ];
    }

    forward_list< DirectedEdge > getEdges() const {
        forward_list< DirectedEdge > all;
        for ( int v = 0; v < getV(); ++v ) {
            for ( DirectedEdge e : getAdj( v ) ) {
                all.push_front( e );
            }
        }
        return all;
    }

    void addEdge( DirectedEdge e ) {
        adj[ e.getFrom() ].push_front( e );
        ++E;
    }

    string toString() const {
        ostringstream oss;
        oss << *this;
        return oss.str();
    }

    friend ostream& operator <<( ostream& out, const EdgeWeightedDigraph& G ) {
        out << "\n| V : " << G.getV() << " ; E : " << G.getE() << " ; adj : \n";
        for ( int v = 0; v < G.getV(); ++v ) {
            out << "\n| v : " << v << " : ";
            for ( const DirectedEdge& e : G.getAdj( v ) ) {
                out << e << ", ";
            }
            out << " | ";
        }
        return out;
    }

};

class DirectedCycle {
private:

    vector< bool > marked;
    vector< DirectedEdge > edgeTo;
    vector< bool > onStack;
    stack< DirectedEdge > cycle;

    void dfs( const EdgeWeightedDigraph& G, int v ) {
        marked[ v ] = true;
        onStack[ v ] = true;

        for ( DirectedEdge e : G.getAdj( v ) ) {
            int w = e.getTo();
            if ( hasCycle() ) {
                return;
            } else if ( ! marked[ w ] ) {
                edgeTo[ w ] = e;
                dfs( G, w );
            } else if ( onStack[ w ] ) {
                // cycle detected
                for ( int x = v; x != w; x = edgeTo[ x ].getFrom() ) {
                    if ( edgeTo[ x ] ) {
                        cycle.push( edgeTo[ x ] );
                    }
                }
                cycle.push( e );
            }
        }

        onStack[ v ] = false;
    }

public:

    DirectedCycle( const EdgeWeightedDigraph& G )
        : marked( G.getV(), false ),
          edgeTo( G.getV() ),
          onStack( G.getV(), false )
    {
        for ( int v = 0; v < G.getV(); ++v ) {
            if ( ! marked[ v ] ) {
                dfs( G, v );
            }
        }
    }

    virtual ~DirectedCycle() {
        // not implemented
    }

    stack< DirectedEdge > getCycle() const {
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

    friend ostream& operator <<( ostream& out, const DirectedCycle& dCycle ) {
        out << "\ncycle:\n";
        stack< DirectedEdge > s = dCycle.getCycle();
        while ( ! s.empty() ) {
            out << s.top() << ", ";
            s.pop();
        }
        return out;
    }

};

class DepthFirstOrder {
private:

    vector< bool > marked;
    queue< int > pre;
    queue< int > post;
    stack< int > reversePost;

    void dfs( const EdgeWeightedDigraph& G, int v ) {
        marked[ v ] = true;
        pre.push( v );

        for ( const DirectedEdge& e : G.getAdj( v ) ) {
            int w = e.getTo();
            if ( ! marked[ w ] ) {
                dfs( G, w );
            }
        }

        post.push( v );
        reversePost.push( v );
    }

public:

    DepthFirstOrder( const EdgeWeightedDigraph& G )
        : marked( G.getV(), false )
    {
        for ( int v = 0; v < G.getV(); ++v ) {
            if ( ! marked[ v ] ) {
                dfs( G, v );
            }
        }
    }

    virtual ~DepthFirstOrder() {
        // not implemented
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

    string toString() const {
        ostringstream oss;
        oss << *this;
        return oss.str();
    }

    friend ostream& operator <<( ostream& out, const DepthFirstOrder& dfo ) {
        out << "\npre:\n";
        queue< int > q = dfo.getPre();
        while ( ! q.empty() ) {
            out << q.front() << ", ";
            q.pop();
        }

        out << "\npost:\n";
        q = dfo.getPost();
        while ( ! q.empty() ) {
            out << q.front() << ", ";
            q.pop();
        }

        out << "\nreversePost:\n";
        stack< int > s = dfo.getReversePost();
        while ( ! s.empty() ) {
            out << s.top() << ", ";
            s.pop();
        }
        return out;
    }

};

class Topological {
private:

    stack< int > order;

public:

    Topological( const EdgeWeightedDigraph& G ) {
        DirectedCycle cycleFinder( G );
        if ( ! cycleFinder.hasCycle() ) {
            DepthFirstOrder dfo( G );
            order = dfo.getReversePost();
        }
    }

    virtual ~Topological() {
        // not implemented
    }

    stack< int > getOrder() const {
        return order;
    }

    bool isDAG() const {
        return ! order.empty();
    }

    string toString() const {
        ostringstream oss;
        oss << *this;
        return oss.str();
    }

    friend ostream& operator <<( ostream& out, const Topological& topo ) {
        out << "\ntopo:\n";
        stack< int > s = topo.getOrder();
        while ( ! s.empty() ) {
            out << s.top() << ", ";
            s.pop();
        }
        return out;
    }

};

class AcyclicLP {
private:

    vector< double > distTo;
    vector< vector< DirectedEdge > > edgeTo;

    void relax( const EdgeWeightedDigraph& G, int v ) {
        for ( DirectedEdge e : G.getAdj( v ) ) {
            int w = e.getTo();
            if ( distTo[ w ] < distTo[ v ] + e.getWeight() ) {
                distTo[ w ] = distTo[ v ] + e.getWeight();
                if ( ! edgeTo[ w ].empty() ) {
                    edgeTo[ w ].clear();
                }
                edgeTo[ w ].push_back( e );
            } else if ( distTo[ w ] - distTo[ v ] - e.getWeight() < numeric_limits< double >::epsilon() ) {
                edgeTo[ w ].push_back( e );
            }
        }
    }

public:

    AcyclicLP( const EdgeWeightedDigraph& G, int s )
        : distTo( G.getV(), -1 * numeric_limits< double >::infinity() ),
          edgeTo( G.getV() )
    {
        distTo[ s ] = 0;
        edgeTo[ s ].resize( 1 );
        Topological topo( G );
        stack< int > order = topo.getOrder();
        while ( ! order.empty() ) {
            relax( G, order.top() );
            order.pop();
        }
    }

    virtual ~AcyclicLP() {
        // not implemented
    }

    bool hasPathTo( int v ) const {
        return distTo[ v ] != -1 * numeric_limits< double >::infinity();
    }

    stack< DirectedEdge > getPathTo( int v ) const {
        stack< DirectedEdge > path;
        if ( ! hasPathTo( v ) ) return path;
        DirectedEdge e = edgeTo[ v ][ 0 ];
        while ( e ) {
            path.push( e );
            e = edgeTo[ e.getFrom() ][ 0 ];
        }
        return path;
    }

    vector< stack< DirectedEdge > > getAllPathsTo( int v ) const {
        vector< stack< DirectedEdge > > allPaths;
        if ( ! hasPathTo( v ) ) return allPaths;

        queue< stack< DirectedEdge > > pathsQueue;
        for ( int w = 0; w < edgeTo[ v ].size(); ++w ) {
            stack< DirectedEdge > s;
            s.push( edgeTo[ v ][ w ] );
            pathsQueue.push( s );
        }

        while ( ! pathsQueue.empty() ) {
            stack< DirectedEdge > s = pathsQueue.front();
            pathsQueue.pop();

            DirectedEdge topEdge = s.top();

            if ( ! edgeTo[ topEdge.getFrom() ][ 0 ] ) {
                allPaths.push_back( s );
            } else {
                for ( int w = 0; w < edgeTo[ topEdge.getFrom() ].size(); ++w ) {
                    stack< DirectedEdge > sCopy = s;
                    sCopy.push( edgeTo[ topEdge.getFrom() ][ w ] );
                    pathsQueue.push( sCopy );
                }
                // pathsQueue.push( s );
            }
        }

        return allPaths;
    }

    double getDistTo( int v ) const {
        return distTo[ v ];
    }

    string toString() const {
        ostringstream oss;
        oss << *this;
        return oss.str();
    }

    friend ostream& operator <<( ostream& out, const AcyclicLP& lp ) {
        out << "\nlp:\n";
        for ( int v = 0; v < lp.edgeTo.size(); ++v ) {
            out << "\n| v : " << v << " : ";
            // stack< DirectedEdge > s = lp.getPathTo( v );
            vector< stack< DirectedEdge > > pathVec = lp.getAllPathsTo( v );
            int pathVecSize = pathVec.size();
            for ( int i = 0; i < pathVec.size(); ++i ) {
                stack< DirectedEdge > s = pathVec[ i ];
                while ( ! s.empty() ) {
                    if ( s.top().getWeight() > 0 ) {
                        out << s.top().getFrom() << ", ";
                    }
                    s.pop();
                }
                out << " | \n";
            }
        }

        out << "\n\ndistTo:\n";
        for ( int v = 0; v < lp.distTo.size(); ++v ) {
            out << v << " : " << lp.distTo[ v ] << endl;
        }

        out << "\n\nedgeTo:\n";
        for ( int v = 0; v < lp.edgeTo.size(); ++v ) {
            out << v << " : ";
            for ( int w = 0; w < lp.edgeTo[ v ].size(); ++w ) {
                out << lp.edgeTo[ v ][ w ] << ", ";
            }
            out << endl;
        }

        return out;
    }

};

class CPM {
public:

    CPM( const vector< pair< double, vector< int > > >& graphVec ) {
        int N = graphVec.size();
        EdgeWeightedDigraph G( 2 * N + 2 );
        int s = 2 * N;
        int t = 2 * N + 1;

        for ( int i = 0; i < N; ++i ) {
            DirectedEdge currentJobEdge( i, i + N, graphVec[ i ].first );
            G.addEdge( currentJobEdge );

            DirectedEdge sourceToCurrentJobEdge( s, i, 0 );
            G.addEdge( sourceToCurrentJobEdge );

            DirectedEdge currentJobToSinkEdge( i + N, t, 0 );
            G.addEdge( currentJobToSinkEdge );

            for ( int j = 0; j < graphVec[ i ].second.size(); ++j ) {
                DirectedEdge currentJobToNextJobEdge( i + N, graphVec[ i ].second[ j ], 0 );
                G.addEdge( currentJobToNextJobEdge );
            }
        }

        AcyclicLP lp( G, s );
        // cout << lp << endl;

        cout << fixed << setprecision( 2 );
        cout << "DEBUG: START TIME : " << endl;
        for ( int v = 0; v < N; ++v ) {
            cout << v << " : " << lp.getDistTo( v ) << endl;
        }
        cout << endl;
        cout << "DEBUG: FINISH TIME : " << lp.getDistTo( t ) << endl;
        cout << "DEBUG: CRITICAL PATHS: " << endl;

        vector< stack< DirectedEdge > > pathVec = lp.getAllPathsTo( t );
        int pathVecSize = pathVec.size();
        for ( int i = 0; i < pathVec.size(); ++i ) {
            stack< DirectedEdge > s = pathVec[ i ];
            while ( ! s.empty() ) {
                if ( s.top().getWeight() > 0 ) {
                    cout << s.top().getFrom() << ", ";
                }
                s.pop();
            }
            cout << "\n";
        }
    }

    virtual ~CPM() {
        // not implemented
    }

};

int main( int argc, char ** argv ) {

    vector< pair< double, vector< int > > > graphVec {
            { 41.0, { 1, 7, 9 } },
            { 51.0, { 2 } },
            { 50.0, {   } },
            { 32.0, { 2 } },
            { 38.0, {   } },
            { 45.0, {   } },
            { 21.0, { 3, 8 } },
            { 29.0, { 3, 8, 6 } },
            { 32.0, { 2 } },
            { 29.0, { 4, 6 } },
    };

    CPM cpm( graphVec );

    return 0;
}
