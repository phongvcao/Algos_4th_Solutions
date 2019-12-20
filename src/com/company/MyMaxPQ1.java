package com.company;
import edu.princeton.cs.algs4.*;

public class MyMaxPQ1< Key extends Comparable< Key > > {

    private Key[] pq;
    private int N = 0;

    public MyMaxPQ1( int maxN ) {
        pq = ( Key[] ) new Comparable[ maxN + 1 ];
    }

    public boolean less( int i, int j ) {
        return pq[ i ].compareTo( pq[ j ] ) == -1;
    }

    public void exchange( int i, int j ) {
        Key temp = pq[ i ];
        pq[ i ] = pq [ j ];
        pq[ j ] = temp;
    }

    public String toString() {
        return java.util.Arrays.toString( pq );
    }

    public int size() {
        return N;
    }

    public boolean isEmpty() {
        return size() == 0;
    }

    public String toStringDelMax() {
        String rv = "{ ";
        while ( ! isEmpty() ) {
            rv += delMax() + ", ";
        }

        rv += " }";
        return rv;
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

    public void insert( Key k ) {
        pq[ ++N ] = k;
        swim( N );
    }

    public Key delMax() {
        Key max = pq[ 1 ];
        exchange( 1, N-- );
        pq[ N + 1 ] = null;
        sink( 1 );
        return max;
    }

    public static void main( String[] args ) {
        Integer[] intArr = { 14, 12, 10, 8, 6, 4, 2, 0, 1, 3, 5, 7, 9, 11, 13 };
        MyMaxPQ1< Integer > maxPQ = new MyMaxPQ1< Integer >( intArr.length );

        for ( int i = 0; i < intArr.length; ++i ) {
            maxPQ.insert( intArr[ i ] );
        }

        StdOut.println( "DEBUG: maxPQ (BEFORE): " + maxPQ.toString() );
        // [null, 14, 12, 13, 8, 6, 9, 11, 0, 1, 3, 5, 4, 7, 2, 10]

        StdOut.println( "DEBUG: maxPQ (AFTER): " + maxPQ.toStringDelMax() );
    }
}
