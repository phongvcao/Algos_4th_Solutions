package com.company;
import edu.princeton.cs.algs4.*;

public class BinarySearchSTOrderedInsertions< Key extends Comparable< Key >, Value > {

    private Key[] keys;
    private Value[] values;
    private int N = 0;

    public BinarySearchSTOrderedInsertions( int cap ) {
        keys = ( Key[] )new Comparable[ cap ];
        values = ( Value[] )new Object[ cap ];
    }

    public void put( Key key, Value value ) {
        if ( N > 0 && key.compareTo( max() ) > 0 ) {
            keys[ N ] = key;
            values[ N ] = value;
            ++N;
            return;
        }

        int i = rank( key );
        if ( i < N && key.compareTo( keys[ i ] ) == 0 ) {
            values[ i ] = value;
            return;
        }
        for ( int j = N; j > i; --j ) {
            keys[ j ] = keys[ j - 1 ];
            values[ j ] = values[ j - 1 ];
        }
        keys[ i ] = key;
        values[ i ] = value;
        ++N;
    }

    public Key max() {
        return keys[ N - 1 ];
    }

    public Key min() {
        return keys[ 0 ];
    }

    public boolean isEmpty() {
        return size() == 0;
    }

    public int size() {
        return N;
    }

    public boolean contains( Key key ) {
        return get( key ) != null;
    }

    public String toString() {
        return "\nkeys : " + java.util.Arrays.toString( keys ) + "\nvalues : " + java.util.Arrays.toString( values );
    }

    public int rank( Key key ) {
        int low = 0;
        int high = N - 1;
        while ( low <= high ) {
            int mid = low + ( high - low ) / 2;
            int cmp = key.compareTo( keys[ mid ] );
            if ( cmp < 0 ) {
                high = mid - 1;
            } else if ( cmp > 0 ) {
                low = mid + 1;
            } else {
                return mid;
            }
        }
        return low;
    }

    public Iterable< Key > keys( Key low, Key high ) {
        Queue< Key > q = new Queue< Key >();
        if ( low.compareTo( high ) > 0 ) return q;
        int lowRank = rank( low );
        int highRank = rank( high );
        for ( int i = lowRank; i <= highRank; ++i ) {
            q.enqueue( keys[ i ] );
        }
        return q;
    }

    public Iterable< Key > keys() {
        return keys( min(), max() );
    }

    public Value get( Key key ) {
        int i = rank( key );
        if ( i < N && key.compareTo( keys[ i ] ) == 0 ) {
            return values[ i ];
        }
        return null;
    }

    public void delete( Key key ) {
        int i = rank( key );
        if ( i < N && key.compareTo( keys[ i ] ) == 0 ) {
            for ( int j = N - 1; j >= i; --j ) {
                keys[ j ] = keys[ j + 1 ];
                values[ j ] = values[ j + 1 ];
            }
            keys[ i ] = null;
            values[ i ] = null;
            --N;
        }
    }

    public void deleteMax() {
        delete( max() );
    }

    public void deleteMin() {
        delete( min() );
    }

    public static void main( String[] args ) {
        Integer[] strArr = { 14, 12, 10, 8, 6, 4, 2, 0, 1, 3, 5, 7, 9, 11, 13 };
        Integer[] intArr = { 14, 12, 10, 8, 6, 4, 2, 0, 1, 3, 5, 7, 9, 11, 13 };
        BinarySearchSTOrderedInsertions< Integer, Integer > st = new BinarySearchSTOrderedInsertions< Integer, Integer >( intArr.length );
        for ( int i = 0; i < intArr.length; ++i ) {
            st.put( strArr[ i ], intArr[ i ] );
        }

        StdOut.println( "DEBUG: st: " + st.toString() );
    }
}
