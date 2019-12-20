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
#include <cctype>

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

//--------------------------//

class Digraph {
private:

    int V = 0;
    int E = 0;
    vector< forward_list< int > > adj;
    vector< string > values;

public:

    Digraph( int V )
        : V( V ),
          adj( V ),
          values( V )
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

    string toString() const {
        string rv = "\n";
        for ( int v = 0; v < getV(); ++v ) {
            rv += "\n| v : " + to_string( v ) + " : ";
            for ( int w : getAdj( v ) ) {
                rv += to_string( w ) + ", ";
            }
            rv += " | ";
        }
        return rv;
    }

    void addEdge( int v, int w ) {
        adj[ v ].push_front( w );
        ++E;
    }

    void addValue( int v, string value ) {
        values[ v ] = value;
    }

    string getValue( int v ) const {
        return values[ v ];
    }

    vector< string > getValues() const {
        return values;
    }

    Digraph reverse() const {
        Digraph R( V );
        for ( int v = 0; v < getV(); ++v ) {
            for ( int w : getAdj( v ) ) {
                R.addEdge( w, v );
            }
        }
        return R;
    }
};

class ArithmeticExpression {
private:

    vector< bool > marked;
    vector< string > results;

    string evaluate( string leftValue, string rightValue, string oper ) {
        if ( oper[ 0 ] == '+' ) {
            return to_string( stoi( leftValue ) + stoi( rightValue ) );
        } else if ( oper[ 0 ] == '-' ) {
            return to_string( stoi( leftValue ) - stoi( rightValue ) );
        } else if ( oper[ 0 ] == '/' ) {
            return to_string( stoi( leftValue ) / stoi( rightValue ) );
        } else if ( oper[ 0 ] == '*' ) {
            return to_string( stoi( leftValue ) * stoi( rightValue ) );
        }
        return "0";
    }

public:

    ArithmeticExpression( const Digraph& G )
        : marked( G.getV(), false ),
          results( G.getV(), "" )
    {
        for ( int v = 0; v < G.getV(); ++v ) {
            if ( ! marked[ v ] ) {
                dfs( G, v );
            }
        }
    }

    virtual ~ArithmeticExpression() {
        // not implemented
    }

    void dfs( const Digraph& G, int v ) {
        marked[ v ] = true;

        for ( int w : G.getAdj( v ) ) {
            if ( ! marked[ w ] ) {
                dfs( G, w );
            }

            if ( isdigit( G.getValue( w )[ 0 ] ) ) {
                results[ w ] = G.getValue( w );
            }

            if ( ! isdigit( G.getValue( v )[ 0 ] ) ) {
                if ( results[ v ].empty() ) {
                    results[ v ] = results[ w ];
                } else {
                    results[ v ] = evaluate( results[ v ], results[ w ], G.getValue( v ) );
                }
            }
        }
    }

    int getResult() const {
        return stoi( results[ 0 ] );
    }
};

int main( int argc, char ** argv ) {
    // 3 * 6 + 2 * 3 + 5 * 6
    //               { "0", "1", "2", "3", "4", "5", "6", "7" }
    string strArr1[] = { "+", "*", "3", "6", "*", "2", "*", "5" };
    int graphArr1[ 9 ][ 2 ] = {
            { 0, 1 },
            { 0, 4 },
            { 0, 6 },
            { 1, 2 },
            { 1, 3 },
            { 4, 5 },
            { 4, 2 },
            { 6, 7 },
            { 6, 3 }
    };
    Digraph dGraph1( 9 );
    for ( int i = 0; i < sizeof( strArr1 ) / sizeof( string ); ++i ) {
        dGraph1.addValue( i, strArr1[ i ] );
    }

    for ( int i = 0; i < 9; ++i ) {
        dGraph1.addEdge( graphArr1[ i ][ 0 ], graphArr1[ i ][ 1 ] );
    }

    ArithmeticExpression ae( dGraph1 );
    cout << "DEBUG: result: " << ae.getResult() << endl;

    return 0;
}
