//
// Created by Phong Cao on 2019-04-02.
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
    vector< bool > onStack;
    vector< DirectedEdge > edgeTo;
    stack< DirectedEdge > cycle;
    double cycleWeight = numeric_limits< double >::infinity();

    void dfs( const EdgeWeightedDigraph& G, int v ) {
        marked[ v ] = true;
        onStack[ v ] = true;

        for ( DirectedEdge e : G.getAdj( v ) ) {
            int w = e.getTo();
            if ( hasCycle() ) {
                // do nothing
            } else if ( ! marked[ w ] ) {
                edgeTo[ w ] = e;
                dfs( G, w );
            } else if ( onStack[ w ] ) {
                // cycle detected
                double tempCycleWeight = 0;
                stack< DirectedEdge > tempCycle;
                for ( int x = v; x != w; x = edgeTo[ x ].getFrom() ) {
                    if ( edgeTo[ x ] ) {
                        tempCycle.push( edgeTo[ x ] );
                        tempCycleWeight += edgeTo[ x ].getWeight();
                    }
                }
                tempCycle.push( e );
                tempCycleWeight += e.getWeight();
                if ( tempCycleWeight < cycleWeight ) {
                    cycle = tempCycle;
                    cycleWeight = tempCycleWeight;
                }
            }
        }

        onStack[ v ] = false;
    }

public:

    DirectedCycle( const EdgeWeightedDigraph& G )
        : marked( G.getV(), false ),
          onStack( G.getV(), false ),
          edgeTo( G.getV() )
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

    double getCycleWeight() const {
        return cycleWeight;
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

class TarjanSCC {
private:

    vector< bool > marked;
    vector< int > id;
    vector< int > low;
    int pre = 0;
    int count = 0;
    stack< int > dfsStack;
    map< int, vector< int > > multiVertexComps;

    void dfs( const EdgeWeightedDigraph& G, int v ) {
        marked[ v ] = true;
        low[ v ] = pre++;
        dfsStack.push( v );
        int min = low[ v ];

        for ( const DirectedEdge& e : G.getAdj( v ) ) {
            int w = e.getTo();
            if ( ! marked[ w ] ) {
                dfs( G, w );
            }

            if ( min > low[ w ] ) {
                min = low[ w ];
            }
        }

        if ( min < low[ v ] ) {
            low[ v ] = min;
            return;
        }

        int w;
        vector< int > comp;
        int minVertex = G.getV();

        do {
            w = dfsStack.top();
            dfsStack.pop();
            if ( minVertex > w ) {
                minVertex = w;
            }
            comp.push_back( w );
            id[ w ] = count;
            low[ w ] = G.getV();
        } while ( w != v );

        if ( comp.size() > 1 ) {
            multiVertexComps.insert( { minVertex, comp } );
        }

        ++count;
    }

public:

    TarjanSCC( const EdgeWeightedDigraph& G )
        : marked( G.getV(), false ),
          id( G.getV() ),
          low( G.getV() )
    {
        for ( int v = 0; v < G.getV(); ++v ) {
            if ( ! marked[ v ] ) {
                dfs( G, v );
            }
        }
    }

    virtual ~TarjanSCC() {
        // not implemented
    }

    int getId( int v ) const {
        return id[ v ];
    }

    int getCount() const {
        return count;
    }

    bool stronglyConnected( int v, int w ) const {
        return getId( v ) == getId( w );
    }

    map< int, vector< int > > getMultiVertexComponents() const {
        return multiVertexComps;
    }

    string toString() const {
        ostringstream oss;
        oss << *this;
        return oss.str();
    }

    friend ostream& operator <<( ostream& out, const TarjanSCC& scc ) {
        out << "\nscc:\n";
        out << "\n\nid:\n";
        for ( int v = 0; v < scc.id.size(); ++v ) {
            out << v << " : " << scc.id[ v ] << endl;
        }

        out << "\n\nlow:\n";
        for ( int v = 0; v < scc.low.size(); ++v ) {
            out << v << " : " << scc.low[ v ] << endl;
        }
        
        out << "\n\nmultiVertexComps:\n";
        for ( map< int, vector< int > >::const_iterator iter = scc.multiVertexComps.begin();
              iter != scc.multiVertexComps.end(); ++iter ) {
            out << iter->first << " : ";
            for ( int v : iter->second ) {
                out << v << ", ";
            }
            out << endl;
        }
        return out;
    }

};

struct {
    bool operator ()( const DirectedEdge& e1, const DirectedEdge& e2 ) {
        if ( e1.getFrom() < e2.getFrom() ) {
            return true;
        } else if ( e1.getFrom() > e2.getFrom() ) {
            return false;
        } else {
            if ( e1.getTo() < e2.getTo() ) {
                return true;
            } else if ( e1.getTo() > e2.getTo() ) {
                return false;
            } else {
                return false;
            }
        }
        return false;
    }
} compareDirectedEdges;

class JohnsonFindAllCycles {
private:

    vector< bool > marked;
    vector< DirectedEdge > edgeTo;
    unordered_map< int, unordered_set< int > > invMarkedMap;
    vector< forward_list< DirectedEdge > > allCycles;
    bool cycleFound = false;

    void dfs( const EdgeWeightedDigraph& G, int v, int s ) {
        marked[ v ] = true;
        for ( DirectedEdge e : G.getAdj( v ) ) {
            int w = e.getTo();
            if ( ! marked[ w ] ) {
                edgeTo[ w ] = e;
                dfs( G, w, s );
            } else if ( w == s ) {
                // cycle detected
                forward_list< DirectedEdge > cycle;
                cycle.push_front( e );
                for ( int x = v; x != w; x = edgeTo[ x ].getFrom() ) {
                    if ( edgeTo[ x ] ) {
                        cycle.push_front( edgeTo[ x ] );
                    }
                }
                allCycles.push_back( cycle );
                cycleFound = true;
            }
        }

        if ( cycleFound ) {
            unmark( v );
        } else {
            for ( const DirectedEdge& e : G.getAdj( v ) ) {
                int w = e.getTo();
                if ( invMarkedMap.find( w ) == invMarkedMap.end() ) {
                    invMarkedMap.insert( { w, unordered_set< int >() } );
                }
                invMarkedMap[ w ].insert( v );
            }
        }
    }

    void unmark( int v ) {
        marked[ v ] = false;
        if ( invMarkedMap.find( v ) == invMarkedMap.end() ) return;
        for ( int w : invMarkedMap[ v ] ) {
            if ( marked[ w ] ) {
                unmark( w );
            }
        }
        invMarkedMap.erase( v );
    }

public:

    JohnsonFindAllCycles( const EdgeWeightedDigraph& G )
        : marked( G.getV(), false ),
          edgeTo( G.getV() )
    {
        int s = 0;
        while ( s < G.getV() ) {
            EdgeWeightedDigraph subGraph( G.getV() );
            for ( int v = s; v < G.getV(); ++v ) {
                for ( DirectedEdge e : G.getAdj( v ) ) {
                    int w = e.getTo();
                    if ( w < s ) continue;
                    subGraph.addEdge( e );
                }
            }

            TarjanSCC scc( subGraph );
            map< int, vector< int > > multiVertexComps = scc.getMultiVertexComponents();
            if ( multiVertexComps.empty() ) break;
            map< int, vector< int > >::iterator iter = multiVertexComps.begin();

            EdgeWeightedDigraph sccGraph( G.getV() );
            for ( int v : iter->second ) {
                for ( DirectedEdge e : subGraph.getAdj( v ) ) {
                    int w = e.getTo();
                    if ( scc.stronglyConnected( v, w ) ) {
                        sccGraph.addEdge( e );
                    }
                }
            }

            cycleFound = false;
            dfs( sccGraph, iter->first, iter->first );
            s = iter->first + 1;
        }
    }

    virtual ~JohnsonFindAllCycles() {
        // not implementdd
    }

    bool hasCycle() const {
        return ! allCycles.empty();
    }

    vector< forward_list< DirectedEdge > > getAllCycles() const {
        return allCycles;
    }

    string toString() const {
        ostringstream oss;
        oss << *this;
        return oss.str();
    }

    friend ostream& operator <<( ostream& out, const JohnsonFindAllCycles& jCycles ) {
        out << "\ncycle : count : " << jCycles.allCycles.size() << endl;
        for ( const forward_list< DirectedEdge >& cycle : jCycles.allCycles ) {
            for ( const DirectedEdge& e : cycle ) {
                out << e << ", ";
            }
            out << endl;
        }
        return out;
    }

    static void test() {

        int graphArr[ 15 ][ 2 ] = {
                { 1, 2 },
                { 1, 8 },
                { 1, 5 },
                { 2, 9 },
                { 2, 7 },
                { 2, 3 },
                { 3, 1 },
                { 3, 2 },
                { 3, 6 },
                { 3, 4 },
                { 6, 4 },
                { 4, 5 },
                { 5, 2 },
                { 8, 9 },
                { 9, 8 },
        };

        EdgeWeightedDigraph dGraph( 10 );

        for ( int i = 0; i < 15; ++i ) {
            DirectedEdge e( graphArr[ i ][ 0 ], graphArr[ i ][ 1 ], 0 );
            dGraph.addEdge( e );
        }

        cout << "DEBUG: dGraph: \n" << dGraph.toString() << endl;

        TarjanSCC scc( dGraph );
        cout << "DEBUG: scc: \n" << scc << endl;

        JohnsonFindAllCycles jCycleFinder( dGraph );
        cout << "DEBUG: jCycleFinder: \n" << jCycleFinder.toString() << endl;
    }

};

// We need to find the most negative cycles among all the cycles in the graph
class Arbitrage {
public:

    Arbitrage( const vector< pair< string, vector< double > > >& graphVec ) {
        int V = graphVec.size();
        vector< string > nameVec( V );
        EdgeWeightedDigraph G( V );

        for ( int i = 0; i < graphVec.size(); ++i ) {
            nameVec[ i ] = graphVec[ i ].first;
            for ( int j = 0; j < graphVec[ i ].second.size(); ++j ) {
                DirectedEdge e( i, j, -1 * log( graphVec[ i ].second[ j ] ) );
                G.addEdge( e );
            }
        }

        JohnsonFindAllCycles jCycleFinder( G );
        vector< forward_list< DirectedEdge > > allCycles = jCycleFinder.getAllCycles();
        double minWeight = numeric_limits< double >::infinity();
        int minCycleIdx = -1;
        for ( int i = 0; i < allCycles.size(); ++i ) {
            double weight = 0;
            for ( const DirectedEdge& e : allCycles[ i ] ) {
                weight += e.getWeight();
            }
            if ( weight < minWeight ) {
                minWeight = weight;
                minCycleIdx = i;
            }
        }

        cout << "DEBUG : Best Arbitrage Opportunity: " << endl;
        double stake = 1000;
        for ( const DirectedEdge e : allCycles[ minCycleIdx ] ) {
            printf( "%10.5f %s = ", stake, nameVec[ e.getFrom() ].c_str() );
            stake *= exp( -1 * e.getWeight() );
            printf( "%10.5f %s\n", stake, nameVec[ e.getTo() ].c_str() );
        }
    }

    virtual ~Arbitrage() {
        // not implemented
    }

};

int main( int argc, char ** argv ) {

    vector< pair< string, vector< double > > > graphVec {
            { "USD", { 1     , 0.741 , 0.657 , 1.061 , 1.005 }, },
            { "EUR", { 1.349 , 1     , 0.888 , 1.433 , 1.366 }, },
            { "GBP", { 1.521 , 1.126 , 1     , 1.614 , 1.538 }, },
            { "CHF", { 0.942 , 0.698 , 0.619 , 1     , 0.953 }, },
            { "CAD", { 0.995 , 0.732 , 0.650 , 1.049 , 1     }, },
    };

    Arbitrage arbitrage( graphVec );

    return 0;
}
