package com.company;
import edu.princeton.cs.algs4.*;

public class MyMaxPQ< Key extends Comparable< Key > > {

    private Key[] pq;
    private int N = 0;

    public MyMaxPQ( int maxN ) {
        pq = (Key[]) new Comparable[ maxN + 1 ];
    }

    public boolean isEmpty() {
        return N == 0;
    }

    public int size() {
        return N;
    }

    public void insert( Key v ) {
        pq[ ++N ] = v;
        swim( N );
    }

    public Key delMax() {
        Key max = pq[ 1 ];
        exchange( 1, N-- );
        pq[ N + 1 ] = null;
        sink( 1 );
        return max;
    }

    public boolean less( int i, int j ) {
        return pq[ i ].compareTo( pq[ j ] ) == -1;
    }

    public void exchange( int i, int j ) {
        Key temp = pq[ i ];
        pq[ i ] = pq[ j ];
        pq[ j ] = temp;
    }

    public void swim( int k ) {
        while ( k > 1 && less( k / 2, k ) ) {
            exchange( k / 2, k );
            k /= 2;
        }
    }
    public void sink( int k ) {
        while ( 2 * k <= N ) {
            int j = 2 * k;
            if ( j < N && less( j, j + 1 ) ) ++j;
            if ( ! less( k, j ) ) break;
            exchange( k, j );
            k = j;
        }
    }

    public String toString() {
        return java.util.Arrays.toString( pq );
    }

    public String toStringDelMax() {
        String rv = "{ ";

        while ( ! isEmpty() ) {

            StdOut.println( "DEBUG: toStringDelMax(): " + toString() );

            rv += delMax() + ", ";
        }

        rv += "}";
        return rv;
    }

    public static void main( String[] args ) {
        Integer[] intArr = { 14, 12, 10, 8, 6, 4, 2, 0, 1, 3, 5, 7, 9, 11, 13 };
        MyMaxPQ< Integer > maxPQ = new MyMaxPQ< Integer >( intArr.length );
        for ( int i = 0; i < intArr.length; ++i ) {
            maxPQ.insert( intArr[ i ] );
        }

        StdOut.println( "DEBUG: intArr (BEFORE): " + maxPQ.toString() );

        StdOut.println( "DEBUG: intArr (AFTER): " + maxPQ.toStringDelMax() );
    }
}
