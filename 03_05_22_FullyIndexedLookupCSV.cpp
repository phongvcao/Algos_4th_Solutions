//
// Created by Phong Cao on 2019-02-08.
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
using std::stoi;
using std::stol;
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

// Implement SeparateChainingHashST for FullLookupCSV
template< typename Key, typename Value >
class SeparateChainingHashST {
private:

    class Node;
    typedef shared_ptr< Node > NodePtr;

    NodePtr newNode( const Key& key, const Value& value ) {
        return make_shared< Node >( key, value );
    }

    class Node {
    public:
        const Key* key = NULL;
        Value value;
        NodePtr next = NULL;

        Node( const Key& key, const Value value ) {
            this->key = &key;
            this->value = value;
        }

        virtual ~Node() {
            // not implemented
        }

        friend ostream& operator <<( ostream& out, const Node& h ) {
            out << " | " << *( h.key ) << " : " << *( h.value );
            if ( h.next ) {
                out << " ; next : " << *( h.next->key );
            } else {
                out << " ; next : null";
            }
            out << " | \n";
            return out;
        }

        string toString() {
            ostringstream oss;
            oss << *this;
            return oss.str();
        }
    };

    int M = 17;
    int N = 0;
    vector< NodePtr > st;

    int hash( const Key& key ) {
        return std::hash< Key >{}( key ) % M;
    }

public:

    SeparateChainingHashST( int M )
        : M( M )
    {
        st.resize( M );
        for ( int i = 0; i < M; ++i ) {
            st[ i ] = NULL;
        }
    }

    SeparateChainingHashST()
        : SeparateChainingHashST( 17 )
    {
        // not implemented
    }

    virtual ~SeparateChainingHashST() {
        // not implemented
    }

    void put( const Key& key, const Value& value ) {
        NodePtr ptr = st[ hash( key ) ];
        if ( ptr ) {
            while ( ptr->next ) {
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
        NodePtr beforePtr = ptr;
        while ( ptr ) {
            if ( key == *( ptr->key ) ) {
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

    bool contains( const Key& key ) {
        return get( key ) != NULL;
    }

    const Value* get( const Key& key ) {
        NodePtr ptr = st [ hash( key ) ];
        while ( ptr ) {
            if ( key == *( ptr->key ) ) {
                return &( ptr->value );
            }
            ptr = ptr->next;
        }
        return NULL;
    }

    int size() {
        return N;
    }

    bool empty() {
        return size() == 0;
    }
    
    queue< Key > getKeys() {
        queue< Key > q;
        for ( int i = 0; i < M; ++i ) {
            NodePtr ptr = st[ i ];
            while ( ptr ) {
                q.push( *( ptr->key ) );
                ptr = ptr->next;
            }
        }
        return q;
    }

    string toString() {
        string rv = "\n";
        for ( int i = 0; i < M; ++i ) {
            NodePtr ptr = st[ i ];
            while ( ptr ) {
                if ( ptr ) {
                    rv += "\ni : " + to_string( i ) + " " + ptr->toString();
                }
                ptr = ptr->next;
            }
        }
        return rv;
    }
};

// So we'll build 1 x SeparateChainingHashST for each field.
// For example, if we use first field as keyField, build SeparateChainingHashST for field 0 of the input
// For example, if we use second field as keyField, build SeparateChainingHashST for field 1 of the input
// When query-ing, users specify which field they want to use as key, and they're querying for which attribute index,
// and then the query string for keyField type that they chose.
//
// e.g. 0 1 wayne => Use the 1st field in input as keyField of SeparateChainingHashST, querying into the 2nd column of
//                   the CSV, for this value of 'wayne'. 'wayne' should be 1 of the values of the initial keyField at
//                   beginning of the query.
//
//     < queryFieldIndex > < queryForWhatValue > < queryValue >

string query( vector< SeparateChainingHashST< string, vector< string > > >& hashSTVec,
              int keyField, int valueField, const string query ) {
    if ( keyField >= hashSTVec.size() ) return query;

    SeparateChainingHashST< string, vector< string > >* hashST = &hashSTVec[ keyField ];
    if ( valueField >= hashST->size() ) return query;

    const vector< string >* valueVec = hashST->get( query );
    return valueVec->at( valueField );
}

int main( int argc, char ** argv ) {
    string firstField[] = { "S", "E", "A", "R", "C", "H", "X", "M", "P", "L" };
    string secondField[] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
    string thirdField[] = { "E", "A", "S", "Y", "Q", "U", "T", "I", "O", "N" };

    vector< SeparateChainingHashST< string, vector< string > > > fullLookupCSV;
    fullLookupCSV.resize( 3 );
    for ( int i = 0; i < sizeof( firstField ) / sizeof( string ); ++i ) {
        vector< string > secondThirdField;
        vector< string > firstThirdField;
        vector< string > firstSecondField;

        secondThirdField.push_back( firstField[ i ] );
        secondThirdField.push_back( secondField[ i ] );
        secondThirdField.push_back( thirdField[ i ] );

        firstThirdField.push_back( firstField[ i ] );
        firstThirdField.push_back( secondField[ i ] );
        firstThirdField.push_back( thirdField[ i ] );

        firstSecondField.push_back( firstField[ i ] );
        firstSecondField.push_back( secondField[ i ] );
        firstSecondField.push_back( thirdField[ i ] );

        fullLookupCSV[ 0 ].put( firstField[ i ], secondThirdField );
        fullLookupCSV[ 1 ].put( secondField[ i ], firstThirdField );
        fullLookupCSV[ 2 ].put( thirdField[ i ], firstSecondField );
    }

    cout << "DEBUG: FullCSV: \n" << endl;
    for ( int i = 0; i < fullLookupCSV.size(); ++i ) {
        queue< string > q = fullLookupCSV[ i ].getKeys();
        while ( ! q.empty() ) {
            cout << to_string( i ) << ", " << q.front() << ", { ";
            vector< string > valueField = *( fullLookupCSV[ i ].get( q.front() ) );
            for ( int j = 0; j < valueField.size(); ++j ) {
                cout << valueField[ j ] << ", ";
            }
            cout << "}\n";
            q.pop();
        }
        cout << endl;
    }

    string myQuery[ 6 ][ 3 ] = {
            { "0", "2", "E" }, // expected: A
            { "0", "1", "E" }, // expected: 1
            { "1", "0", "0" }, // expected: S
            { "1", "2", "4" }, // expected: Q
            { "2", "0", "A" }, // expected: E
            { "2", "1", "A" }, // expected: 1
    };

    for ( int i = 0; i < 6; ++i ) {
        cout << query( fullLookupCSV, stoi( myQuery[ i ][ 0 ] ), stoi( myQuery[ i ][ 1 ] ), myQuery[ i ][ 2 ] ) << endl;
    }

    return 0;
}
