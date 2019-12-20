//
// Created by Phong Cao on 2019-02-07.
//

#include <iostream>
#include <sstream>
#include <cmath>
#include <cstdlib>
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
#include <algorithm>
#include <functional>

using std::cout;
using std::cin;
using std::ostream;
using std::istream;
using std::ostringstream;
using std::sqrt;
using std::pow;
using std::rand;
using std::srand;
using std::endl;
using std::hash;
using std::string;
using std::to_string;
using std::vector;
using std::map;              // Ordered Map (Red-Black Tree)
using std::unordered_map;    // HashMap (SeparateChainingHashST)
using std::set;              // Ordered Set (Red-Black Tree)
using std::unordered_set;    // HashSet (SeparateChainingHashST)
using std::pair;
using std::deque;
using std::queue;
using std::stack;
using std::fill;
using std::max;
using std::min;
using std::make_shared;
using std::shared_ptr;

int main( int argc, char ** argv ) {
    string keyArr[] = { "S", "E", "A", "R", "C", "H", "X", "M", "P", "L", "L", "L", "L" };

    map< string, vector< int > > concordance;
    for ( int i = 0; i < sizeof( keyArr ) / sizeof( string ); ++i ) {
        if ( concordance.find( keyArr[ i ] ) != concordance.end() ) {
            concordance[ keyArr[ i ] ].push_back( i );
        } else {
            vector< int > indexVec{ i };
            concordance.insert( pair< string, vector< int > >( keyArr[ i ], indexVec ) );
        }
    }

    // Now translate from concordance to vector< string >
    vector< string > strVec;
    strVec.resize( concordance.size() );
    for ( map< string, vector< int > >::iterator iter = concordance.begin(); iter != concordance.end(); ++iter ) {
        vector< int > indexVec = iter->second;
        for ( int i = 0; i < indexVec.size(); ++i ) {
            if ( indexVec[ i ] >= strVec.size() ) {
                strVec.resize( strVec.size() * 2 );
            }
            strVec[ indexVec[ i ] ] = iter->first;
        }
    }

    for ( int i = 0; strVec[ i ] != "\0" ; ++i ) {
        cout << strVec[ i ] << ", ";
    }

    return 0;
}
