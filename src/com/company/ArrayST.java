package com.company;
import edu.princeton.cs.algs4.*;

public class ArrayST< Key extends Comparable< Key >, Value > {

    private Key[] keys;
    private Value[] values;
    private int N = 0;

    public ArrayST( int cap ) {
        keys = ( Key[] )new Comparable[ cap ];
        values = ( Value[] )new Object[ cap ];
    }

    public int size() {
        return N;
    }

    public boolean isEmpty() {
        return size() == 0;
    }

    public void put( Key key, Value value ) {
        keys[ N ] = key;
        values[ N ] = value;
        ++N;
    }

    public Value get( Key key ) {
        for ( int i = 0; i < N; ++i ) {
            if ( keys[ i ].compareTo( key ) == 0 ) {
                return values[ i ];
            }
        }
        return null;
    }

    public Key min() {
        Key minKey = null;
        for ( int i = 0; i < N; ++i ) {
            if ( ( minKey == null ) || ( less( keys[ i ], minKey ) ) ) {
                minKey = keys[ i ];
            }
        }
        return minKey;
    }

    private boolean less( Comparable a, Comparable b ) {
        return a.compareTo( b ) == -1;
    }

    public Key max() {
        Key maxKey = null;
        for ( int i = 0; i < N; ++i ) {
            if ( ( maxKey == null ) || ( less( maxKey, keys[ i ] ) ) ) {
                maxKey = keys[ i ];
            }
        }
        return maxKey;
    }

    public boolean contains( Key key ) {
        return get( key ) != null;
    }

    public Iterable< Key > keys( Key low, Key high ) {
        Queue< Key > q = new Queue< Key >();
        if ( low.compareTo( high ) > 0 ) return q;
        for ( int i = 0; i < N; ++i ) {
            if ( ( keys[ i ].compareTo( low ) >= 0 ) && ( keys[ i ].compareTo( high ) <= 0 ) ) {
                q.enqueue( keys[ i ] );
            }
        }
        return q;
    }

    public int rank( Key key ) {
        int rankCount = 0;
        for ( int i = 0; i < keys.length; ++i ) {
            if ( keys[ i ].compareTo( key ) < 0 ) {
                ++rankCount;
            }
        }
        return rankCount;
    }

    public String toString() {
        return "\nkeys : " + java.util.Arrays.toString( keys ) + "\nvalues : " + java.util.Arrays.toString( values );
    }

    public static void main( String[] args ) {
        String[] strArr = { "A+", "A", "A-", "B+", "B", "B-", "C+", "C", "C-", "D", "F" };
        Double[] doubleArr = { 4.33, 4.00, 3.67, 3.33, 3.00, 2.67, 2.33, 2.00, 1.67, 1.00, 0.00 };
        ArrayST< String, Double > st = new ArrayST< String, Double >( doubleArr.length );
        for ( int i = 0; i < strArr.length; ++i ) {
            st.put( strArr[ i ], doubleArr[ i ] );
        }

        StdOut.println( "DEBUG: st (BEFORE): " + st.toString() );
    }
}
