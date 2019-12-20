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

class SeparateChainingHashST {
private:

    class Node;
    typedef shared_ptr< Node > NodePtr;

    NodePtr newNode( const int key, const double value ) {
        return make_shared< Node >( key, value );
    }

    class Node {
    public:
        int key;
        double value;
        NodePtr next = NULL;

        Node( const int key, const double value ) {
            this->key = key;
            this->value = value;
        }

        virtual ~Node() {
            // not implemented
        }

        friend ostream& operator <<( ostream& out, const Node& h ) {
            out << " | " << h.key << " : " << h.value;
            if ( h.next ) {
                out << " ; next : " << h.next->key;
            } else {
                out << " ; next : null";
            }
            out << " | ";
            return out;
        }

        string toString() {
            ostringstream oss;
            oss << *this;
            return oss.str();
        }
    };

    int hash( const int key ) {
        return std::hash< int >{}( key ) % M;
    }

    int M = 17;
    int N = 0;
    vector< NodePtr > st;

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

    void resize( int cap ) {
        st.resize( cap );
    }

    void put( const int key, const double value ) {
        NodePtr ptr = st[ hash( key ) ];
        if ( ptr ) {
            if ( ptr->key == key ) {
                ptr->value = value;
                return;
            }
            while ( ptr->next ) {
                if ( key == ptr->key ) {
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

    void deleteKey( const int key ) {
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
                return;
            }

            beforePtr = ptr;
            ptr = ptr->next;
        }
    }

    const double get( const int key ) {
        NodePtr ptr = st[ hash( key ) ];
        while ( ptr ) {
            if ( ptr->key == key ) {
                return ptr->value;
            }
            ptr = ptr->next;
        }
        return 0;
    }

    bool contains( const int key ) {
        NodePtr ptr = st[ hash( key ) ];
        while ( ptr ) {
            if ( ptr->key == key ) {
                return true;
            }
        }
        return false;
    }

    int size() {
        return N;
    }

    bool empty() {
        return size() == 0;
    }

    string toString() {
        string rv = "\n";
        for ( int i = 0; i < M; ++i ) {
            NodePtr ptr = st[ i ];
            while ( ptr ) {
                rv += " " + ptr->toString();
                ptr = ptr->next;
            }
        }
        return rv;
    }

    deque< int > getKeys() {
        deque< int > q;
        for ( int i = 0; i < M; ++i ) {
            NodePtr ptr = st[ i ];
            while ( ptr ) {
                q.push_back( ptr->key );
                ptr = ptr->next;
            }
        }
        return q;
    }
};

class SparseVector {
private:
    int M = 17;

public:
    SeparateChainingHashST st;

    SparseVector( int M )
        : M( M )
    {
        st.resize( M );
    }

    SparseVector()
        : SparseVector( 17 )
    {
        // not implemented
    }

    virtual ~SparseVector() {
        // not implemented
    }

    void resize( int cap ) {

    }

    void put( int index, double value ) {
        st.put( index, value );
    }

    double get( int index ) {
        return st.get( index );
    }

    double dot( SparseVector& other ) {
        double dotProduct = 0.0;
        deque< int > q = st.getKeys();
        while ( ! q.empty() ) {
            dotProduct += st.get( q.front() ) * other.get( q.front() );
            q.pop_front();
        }
        return dotProduct;
    }

    const SparseVector& sum( SparseVector& other )  {
        deque< int > thisDeque = st.getKeys();
        deque< int > otherDeque = st.getKeys();

        int maxKey = thisDeque[ 0 ];
        for ( int i = 0; i < thisDeque.size(); ++i ) {
            if ( maxKey < thisDeque[ i ] ) {
                maxKey = thisDeque[ i ];
            }
        }

        for ( int i = 0; i < otherDeque.size(); ++i ) {
            if ( maxKey < otherDeque[ i ] ) {
                maxKey = otherDeque[ i ];
            }
        }

        for ( int i = 0; i < maxKey + 1; ++i ) {
            double sum = st.get( i ) + other.get( i );
            if ( sum != 0 ) {
                st.put( i, sum );
            } else {
                st.deleteKey( i );
            }
        }
        return *this;
    }

    const SparseVector& multiply( SparseVector& other ) {
        deque< int > thisDeque = st.getKeys();
        deque< int > otherDeque = st.getKeys();

        int maxKey = thisDeque[ 0 ];
        for ( int i = 0; i < thisDeque.size(); ++i ) {
            if ( maxKey < thisDeque[ i ] ) {
                maxKey = thisDeque[ i ];
            }
        }

        for ( int i = 0; i < otherDeque.size(); ++i ) {
            if ( maxKey < otherDeque[ i ] ) {
                maxKey = otherDeque[ i ];
            }
        }

        for ( int i = 0; i < maxKey + 1; ++i ) {
            double product = st.get( i ) * other.get( i );
            if ( product != 0 ) {
                st.put( i, product );
            } else {
                st.deleteKey( i );
            }
        }
        return *this;
    }

    bool empty() {
        return size() == 0;
    }

    int size() {
        return st.size();
    }

    string toString() {
        string rv = "\n";




        rv += st.toString();
        return rv;
    }
};

class Sparse2DMatrix {
public:

    vector< SparseVector > rows;
    vector< SparseVector > columns;
    int rowSize = 0;
    int columnSize = 0;

    Sparse2DMatrix( int rowSize, int columnSize )
        : rowSize( rowSize ),
          columnSize( columnSize )
    {
        rows.resize( columnSize );
        columns.resize( rowSize );
        for ( int i = 0; i < columnSize; ++i ) {
            rows[ i ].resize( rowSize );
        }
        for ( int i = 0; i < rowSize; ++i ) {
            rows[ i ].resize( columnSize );
        }
    }

    Sparse2DMatrix( vector< SparseVector > rows, vector< SparseVector > columns, int rowSize, int columnSize )
        : Sparse2DMatrix( rowSize, columnSize )
    {
        this->rows = rows;
        this->columns = columns;
    }

    Sparse2DMatrix()
        : Sparse2DMatrix( 17, 17 )
    {
        // not implemented
    }

    virtual ~Sparse2DMatrix() {
        // not implemented
    }

    void put( int rowIndex, int colIndex, double value ) {
        if ( rowIndex >= rowSize ) return;
        if ( colIndex >= columnSize ) return;
        rows[ rowIndex ].put( colIndex, value );
        columns[ colIndex ].put( rowIndex, value );
    }

    double get( int rowIndex, int colIndex ) {
        if ( rowIndex >= rowSize ) return 0;
        if ( colIndex >= columnSize ) return 0;
        return rows[ rowIndex ].get( colIndex );
    }

    shared_ptr< Sparse2DMatrix > multiply( Sparse2DMatrix& other ) {
        shared_ptr< Sparse2DMatrix > rv = make_shared< Sparse2DMatrix >( other.rowSize, columnSize );
        for ( int i = 0; i < columnSize; ++i ) {
            for ( int j = 0; j < other.rowSize; ++j ) {
                rv->put( i, j, rows[ i ].dot( other.columns[ j ] ) );
            }
        }
        return rv;
    }

    shared_ptr< Sparse2DMatrix > sum( Sparse2DMatrix& other ) {
        shared_ptr< Sparse2DMatrix > rv = make_shared< Sparse2DMatrix >( other.rowSize, columnSize );
        for ( int i = 0; i < columnSize; ++i ) {
            SparseVector sv = rows[ i ].sum( other.rows[ i ] );
            deque< int > dq = sv.st.getKeys();
            for ( int j = 0; j < dq.size(); ++j ) {
                rv->put( i, dq[ j ], sv.get( dq[ j ] ) );
            }
        }
        return rv;
    }

    bool empty() {
        return size() == 0;
    }

    int size() {
        int totalSize = 0;
        for ( int i = 0; i < rows.size(); ++i ) {
            totalSize += rows[ i ].size();
        }
        return totalSize;
    }

    string toString() {
        string rv = "\n";
        for ( int i = 0; i < columnSize; ++i ) {
            rv += rows[ i ].toString();
        }
        return rv;
    }

};

int main( int argc, char ** argv ) {
    // Test Sparse2DMatrix
    int matrix1Values[ 3 ][ 3 ] = {
            { 1, 2, 3 },
            { 4, 5, 6 },
            { 7, 8, 9 },
    };

    int matrix2Values[ 3 ][ 3 ] = {
            { 1, 2, 3 },
            { 4, 5, 6 },
            { 7, 8, 9 },
    };

    Sparse2DMatrix matrix1( 3, 3 );
    for ( int i = 0; i < 3; ++i ) {
        for ( int j = 0; j < 3; ++j ) {
            matrix1.put( i, j, matrix1Values[ i ][ j ] );
        }
    }

    Sparse2DMatrix matrix2( 3, 3 );
    for ( int i = 0; i < 3; ++i ) {
        for ( int j = 0; j < 3; ++j ) {
            matrix2.put( i, j, matrix2Values[ i ][ j ] );
        }
    }

    cout << "DEBUG: matrix1: \n" << endl;
    cout << matrix1.toString() << endl;

    cout << "DEBUG: matrix2: \n" << endl;
    cout << matrix2.toString() << endl;

    shared_ptr< Sparse2DMatrix > additionResult = matrix1.sum( matrix2 );
    cout << "DEBUG: additionResult: \n" << endl;
    cout << additionResult->toString() << endl;

    shared_ptr< Sparse2DMatrix > multiplyResult = matrix1.multiply( matrix2 );
    cout << "DEBUG: multiplyResult: \n" << endl;
    cout << multiplyResult->toString() << endl;


    return 0;
}
