package com.company;
import edu.princeton.cs.algs4.*;

public class MyBinarySearchST< Key extends Comparable< Key >, Value > {

    private Key[] keys;
    private Value[] values;
    private int N = 0;

    public MyBinarySearchST( int capacity ) {
        keys = ( Key[] )new Comparable[ capacity ];
        values = ( Value[] )new Object[ capacity ];
    }

    /* private void resize() {

    } */

    public void put( Key key, Value val ) {
        int i = rank( key );

        if ( i < N && keys[ i ].compareTo( key ) == 0 ) {
            values[ i ] = val;
            return;
        }

        for ( int j = N; j > i; --j ) {
            keys[ j ] = keys[ j - 1 ];
            values[ j ] = values[ j - 1 ];
        }

        keys[ i ] = key;
        values[ i ] = val;
        ++N;
    }

    public Value get( Key key ) {
        if ( isEmpty() ) return null;
        int i = rank( key );
        if ( i < N && keys[ i ].compareTo( key ) == 0 ) return values[ i ];
        else return null;
    }

    /* public void delete( Key key ) {

    } */

    public boolean contains( Key key ) {
        return get( key ) != null;
    }

    public boolean isEmpty() {
        return size() == 0;
    }

    public int size() {
        return N;
    }

    public Key min() {
        return keys[ 0 ];
    }

    public Key max() {
        return keys[ N - 1 ];
    }

    /* public Key floor( Key key ) {

    } */

    public Key ceiling( Key key ) {
        int i = rank( key );
        return keys[ i ];
    }

    public int rank( Key key ) {
        // Binary Search
        int low = 0;
        int high = N - 1;

        while ( low <= high ) {
            int mid = low + ( high - low ) / 2;
            if ( less( key, keys[ mid ] ) ) {
                high = mid - 1;
            } else if ( less( keys[ mid ], key ) ) {
                low = mid + 1;
            } else {
                return mid;
            }
        }
        return low;
    }

    private boolean less( Comparable a, Comparable b ) {
        return a.compareTo( b ) == -1;
    }

    public Key select( int k ) {
        return keys[ k ];
    }

    /* public void deleteMin() {

    }

    public void deleteMax() {

    }

    public int size( Key low, Key high ) {

    } */

    public Iterable< Key > keys( Key low, Key high ) {
        Queue< Key > q = new Queue< Key >();
        for ( int i = rank( low ); i < rank( high ); ++i ) {
            q.enqueue( keys[ i ] );
        }

        if ( contains( high ) ) {
            q.enqueue( keys[ rank( high ) ] );
        }
        return q;
    }

    public Iterable< Key > keys() {
        return keys( min(), max() );
    }

    public String toString() {
        return "keys : " + java.util.Arrays.toString( keys ) + "\nvalues : " + java.util.Arrays.toString( values );
    }

    public static void main( String[] args ) {
        Integer[] strArr = { 14, 12, 10, 8, 6, 4, 2, 0, 1, 3, 5, 7, 9, 11, 13 };
        Integer[] intArr = { 14, 12, 10, 8, 6, 4, 2, 0, 1, 3, 5, 7, 9, 11, 13 };
        MyBinarySearchST< Integer, Integer > myBinarySearchST = new MyBinarySearchST< Integer, Integer >( intArr.length );

        for ( int i = 0; i < intArr.length; ++i ) {
            myBinarySearchST.put( strArr[ i ], intArr[ i ] );
        }

        StdOut.println( "DEBUG: myBinarySearchST: \n" + myBinarySearchST.toString() );
        StdOut.println( "DEBUG: myBinarySearchST.rank( 4 ): \n" + myBinarySearchST.rank( 4 ) );
        StdOut.println( "DEBUG: myBinarySearchST.rank( 15 ): \n" + myBinarySearchST.rank( 15 ) );
        StdOut.println( "DEBUG: myBinarySearchST.contains( 4 ): \n" + myBinarySearchST.contains( 4 ) );
        StdOut.println( "DEBUG: myBinarySearchST.contains( 15 ): \n" + myBinarySearchST.contains( 15 ) );
    }
}
