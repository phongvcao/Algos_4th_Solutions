package com.company;
import edu.princeton.cs.algs4.*;

public class BinarySearchSTLetterGrades< Key extends Comparable< Key >, Value > {

    private Key[] keys;
    private Value[] values;
    private int N = 0;

    public BinarySearchSTLetterGrades( int cap ) {
        keys = ( Key[] )new Comparable[ cap ];
        values = ( Value[] )new Object[ cap ];
    }

    public void put( Key key, Value val ) {
        int i = rank( key );

        if ( i < N && keys[ i ].compareTo( key ) == 0 ) {
            keys[ i ] = key;
            values[ i ] = val;
            return;
        } else {
            for ( int j = N; j > i; --j ) {
                keys[ j ] = keys[ j - 1 ];
                values[ j ] = values[ j - 1 ];
            }
            keys[ i ] = key;
            values[ i ] = val;
            ++N;
        }
    }

    public Value get( Key k ) {
        if ( isEmpty() ) return null;
        int i = rank( k );
        if ( i < N && keys[ i ].compareTo( k ) == 0 ) {
            return values[ i ];
        }
        return null;
    }

    public boolean contains( Key k ) {
        return get( k ) != null;
    }

    private void exchange( Comparable[] a, int i, int j ) {
        Comparable temp = a[ i ];
        a[ i ] = a[ j ];
        a[ j ] = temp;
    }

    public int rank( Key k ) {
        int low = 0;
        int high = N - 1;

        while ( low <= high ) {
            int mid = low + ( high - low ) / 2;
            if ( less( k, keys[ mid ] ) ) {
                high = mid - 1;
            } else if ( less( keys[ mid ], k ) ) {
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

    public Key min() {
        return keys[ 0 ];
    }

    public Key max() {
        return keys[ N - 1 ];
    }

    public Iterable< Key > keys( Key low, Key high ) {
        Queue< Key > q = new Queue< Key >();
        if ( low.compareTo( high ) > 0 ) return q;
        for ( int i = rank( low ); i < rank( high ); ++i ) {
            q.enqueue( keys[ i ] );
        }
        if ( contains( high ) ) {
            q.enqueue( keys[ rank( high ) ] );
        }
        return q;
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
        String[] strArr = { "A+", "A", "A-", "B+", "B", "B-", "C+", "C", "C-", "D", "F" };
        Double[] doubleArr = { 4.33, 4.00, 3.67, 3.33, 3.00, 2.67, 2.33, 2.00, 1.67, 1.00, 0.00 };
        BinarySearchSTLetterGrades< String, Double > st = new BinarySearchSTLetterGrades< String, Double >( doubleArr.length );
        for ( int i = 0; i < strArr.length; ++i ) {
            st.put( strArr[ i ], doubleArr[ i ] );
        }

        StdOut.println( "DEBUG: st (BEFORE): " + st.toString() );
    }
}
