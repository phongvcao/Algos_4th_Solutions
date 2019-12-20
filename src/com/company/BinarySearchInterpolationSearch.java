package com.company;
import edu.princeton.cs.algs4.*;

public class BinarySearchInterpolationSearch< Key extends Comparable< Key >, Value > {

    private Key[] keys;
    private Value[] values;
    private int N = 0;

    public BinarySearchInterpolationSearch( int cap ) {
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

    public boolean contains( Key key ) {
        return get( key ) != null;
    }

    public Value get( Key key ) {
        int i = rank( key );
        if ( i < N && key.compareTo( keys[ i ] ) == 0 ) {
            return values[ i ];
        }
        return null;
    }

    public int rank( Key key ) {
        int low = 0;
        int high = N - 1;
        while ( low <= high ) {
            int mid = low;
            if ( low == high ) {
                mid = low;
            } else {
                mid = ( high - low ) * ( (Integer)key - (Integer)keys[ low ] ) / ( (Integer)keys[ high ] - (Integer)keys[ low ] );

                if ( mid < low ) {
                    mid = low;
                }

                if ( mid > high ) {
                    mid = high;
                }
            }

            StdOut.println( "DEBUG: mid: " + mid );
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

    public void delete( Key key ) {

    }

    public Key min() {
        return keys[ 0 ];
    }

    public Key max() {
        return keys[ N - 1 ];
    }

    public void deleteMin() {
        delete( min() );
    }

    public void deleteMax() {
        delete( max() );
    }

    public int size() {
        return N;
    }

    public boolean isEmpty() {
        return size() == 0;
    }

    public String toString() {
        return "\nkeys : " + java.util.Arrays.toString( keys ) + "\nvalues : " + java.util.Arrays.toString( values );
    }

    public static void main( String[] args ) {
        Integer[] strArr = { 14, 12, 10, 8, 6, 4, 2, 0, 1, 3, 5, 7, 9, 11, 13 };
        Integer[] intArr = { 14, 12, 10, 8, 6, 4, 2, 0, 1, 3, 5, 7, 9, 11, 13 };
        BinarySearchInterpolationSearch< Integer, Integer > st = new BinarySearchInterpolationSearch< Integer, Integer >( strArr.length );
        for ( int i = 0; i < strArr.length; ++i ) {
            st.put( strArr[ i ], intArr[ i ] );
        }
        StdOut.println( "DEBUG: st: " + st.toString() );
        StdOut.println( "DEBUG: st.get( 14 ): " + st.get( 14 ) );
        StdOut.println( "DEBUG: st.get( 0 ): " + st.get( 0 ) );
        StdOut.println( "DEBUG: st.get( 13 ): " + st.get( 13 ) );
    }
}
