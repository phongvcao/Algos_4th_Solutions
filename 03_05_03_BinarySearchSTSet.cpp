//
// Created by Phong Cao on 2019-02-04.
//

#include <iostream>
#include <sstream>
#include <cmath>
#include <cstdlib>
#include <string>
#include <memory>
#include <vector>
#include <map>
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
using std::map;
using std::queue;
using std::stack;
using std::fill;
using std::max;
using std::min;
using std::make_shared;
using std::shared_ptr;

template< typename Key >
class BinarySearchSTSet {
private:

    int M = 17;
    int N = 0;
    vector< const Key* > st;

    int rank( const Key& key ) {
        int low = 0;
        int high = N;
        while ( low < high ) {
            int mid = ( low + high ) / 2;
            if ( key < *st[ mid ] ) {
                high = mid - 1;
            } else if ( key > *st[ mid ] ) {
                low = mid + 1;
            } else {
                return mid;
            }
        }
        return low;
    }

    void resize( int cap ) {
        vector< const Key* > temp;
        temp.resize( cap );
        for ( int i = 0; i < N; ++i ) {
            temp[ i ] = st[ i ];
        }
        this->st = temp;
        this->M = temp.capacity();
    }

public:

    BinarySearchSTSet( int M )
        : M( M )
    {
        st.resize( M );
        for ( int i = 0; i < M; ++i ) {
            st[ i ] = NULL;
        }
    }

    BinarySearchSTSet()
        : BinarySearchSTSet( 97 )
    {
        // not implemented
    }

    virtual ~BinarySearchSTSet() {
        // not implemented
    }

    void add( const Key& key ) {
        int keyRank = rank( key );
        if ( st[ keyRank ] != NULL ) {
            if ( *st[ keyRank ] == key ) {
                return;
            }

            for ( int i = N; i > keyRank; --i ) {
                st[ i ] = st[ i - 1 ];
            }
        }
        st[ keyRank ] = &key;
        ++N;
    }

    void deleteKey( const Key& key ) {
        if ( ! contains( key ) ) return;
        int keyRank = rank( key );
        for ( int i = keyRank; i < N; ++i ) {
            st[ i ] = st[ i + 1 ];
        }
        st[ N - 1 ] = NULL;
        --N;
    }

    bool contains( const Key& key ) {
        return key == *st[ rank( key ) ];
    }

    bool empty() {
        return size() == 0;
    }

    int size() {
        return N;
    }

    string toString() {
        ostringstream oss;
        for ( int i = 0; i < N; ++i ) {
            oss << " " << *st[ i ];
        }
        oss << endl;
        return oss.str();
    }
};

int main( int argc, char ** argv ) {
    string keyArr[] = { "S", "E", "A", "R", "C", "H", "X", "M", "P", "L" };
    string valueArr[] = { "S", "E", "A", "R", "C", "H", "X", "M", "P", "L" };
    BinarySearchSTSet< string > set( 17 );

    for ( int i = 0; i < sizeof( keyArr ) / sizeof( string ); ++i ) {
        set.add( keyArr[ i ] );
    }

    cout << "DEBUG: set: " << set.toString() << endl;
    cout << "DEBUG: set.contains( L ): " << set.contains( "L" ) << endl;
    cout << "DEBUG: set.contains( D ): " << set.contains( "D" ) << endl;

    set.deleteKey( "E" );
    cout << "DEBUG: set (AFTER deleteKey( E )): " << set.toString() << endl;

    set.deleteKey( "D" );
    cout << "DEBUG: set (AFTER deleteKey( D )): " << set.toString() << endl;

    return 0;
}
