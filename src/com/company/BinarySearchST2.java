package com.company;
import edu.princeton.cs.algs4.*;

public class BinarySearchST2< Key extends Comparable< Key >, Value > {

    private Key[] keys;
    private Value[] values;
    private int N = 0;

    public BinarySearchST2( int cap ) {
        keys = ( Key[] )new Comparable[ cap ];
        values = ( Value[] )new Object[ cap ];
    }

    public void put( Key key, Value value ) {
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

    public Key ceiling( Key key ) {
        int i = rank( key );
        if ( i == N ) return null;
        return keys[ i ];
    }

    public Key floor( Key key ) {
        int i = rank( key );
        if ( i == N ) return null;
        if ( i < N && key.compareTo( keys[ i ] ) == 0 ) return keys[ i ];
        return keys[ i - 1 ];
    }

    public int size() {
        return N;
    }

    public boolean contains( Key key ) {
        return get( key ) != null;
    }

    public boolean isEmpty() {
        return size() == 0;
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

    public Value get( Key key ) {
        int i = rank( key );
        if ( i < N && key.compareTo( keys[ i ] ) == 0 ) {
            return values[ i ];
        }
        return null;
    }

    public String toString() {
        return "\nkeys : " + java.util.Arrays.toString( keys ) + "\nvalues : " + java.util.Arrays.toString( values );
    }

    public Key min() {
        return keys[ 0 ];
    }

    public Key max() {
        return keys[ N - 1 ];
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

    public void delete( Key key ) {
        int i = rank( key );
        if ( i < N && key.compareTo( keys[ i ] ) == 0 ) {
            // Key found
            for ( int j = i; j < N - 1; ++j ) {
                keys[ j ] = keys[ j + 1 ];
                values[ j ] = values[ j + 1 ];
            }
            keys[ N - 1 ] = null;
            values[ N - 1 ] = null;
            --N;
        }
    }

    public void deleteMin() {
        delete( min() );
    }

    public void deleteMax() {
        delete( max() );
    }

    public static void main( String[] args ) {

    }
}
