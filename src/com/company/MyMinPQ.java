package com.company;
import edu.princeton.cs.algs4.*;

public class MyMinPQ< Key extends Comparable< Key > > {

    private int N = 0;
    private Key[] pq;

    public MyMinPQ( int maxN ) {
        pq = ( Key[] )new Comparable[ maxN + 1 ];
    }

    public boolean less( int i, int j ) {
        return pq[ i ].compareTo( pq[ j ] ) == -1;
    }

    public void exchange( int i, int j ) {
        Key temp = pq[ i ];
        pq[ i ] = pq[ j ];
        pq[ j ] = temp;
    }

    public int size() {
        return N;
    }

    public boolean isEmpty() {
        return N == 0;
    }

    public String toString() {
        return java.util.Arrays.toString( pq );
    }

    public String toStringDelMax() {
        String rv = "{ ";

        while ( ! isEmpty() ) {
            rv += delMin() + ", ";
        }

        rv += "}";
        return rv;
    }

    public void swim( int k ) {
        while ( k > 1 && less( k, k / 2 ) ) {
            exchange( k / 2, k );
            k /= 2;
        }
    }

    public void insert( Key k ) {
        pq[ ++N ] = k;
        swim( N );
    }

    public void sink( int k ) {
        while ( 2 * k <= N ) {
            int j = 2 * k;
            if ( j < N && less( j + 1, j ) ) ++j;
            if ( ! less( j, k ) ) break;
            exchange( j, k );
            k = j;
        }
    }

    public Key delMin() {
        Key min = pq[ 1 ];
        exchange( 1, N-- );
        pq[ N + 1 ] = null;
        sink( 1 );
        return min;
    }

    public static void main( String[] args ) {
        Integer[] intArr = { 14, 12, 10, 8, 6, 4, 2, 0, 1, 3, 5, 7, 9, 11, 13 };
        MyMinPQ< Integer > minPQ = new MyMinPQ< Integer >( intArr.length );
        for ( int i = 0; i < intArr.length; ++i ) {
            minPQ.insert( intArr[ i ] );
        }

        StdOut.println( "DEBUG: minPQ (BEFORE): " + minPQ.toString() );
        StdOut.println( "DEBUG: minPQ (AFTER): " + minPQ.toStringDelMax() );
    }
}
