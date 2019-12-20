package com.company;
import edu.princeton.cs.algs4.*;

public class MaxPQArrayConstructor< Key extends Comparable< Key > > {

    private Key[] pq;
    private int N = 0;

    public MaxPQArrayConstructor( int maxN ) {
        pq = ( Key[] )new Comparable[ maxN + 1 ];
    }

    public MaxPQArrayConstructor( Comparable[] a ) {
        pq = ( Key[] )new Comparable[ a.length + 1 ];
        System.arraycopy( a, 0, pq, 1, a.length );
        N = pq.length - 1;
        /* for ( int i = 1; i <= N / 2; ++i ) {
            swim( i );
        } */
        for ( int i = N / 2; i >= 1; --i ) {
            sink( i );
        }
    }

    public int size() {
        return N;
    }

    public boolean isEmpty() {
        return size() == 0;
    }

    public Key max() {
        return pq[ 1 ];
    }

    public void exchange( int i, int j ) {
        Key temp = pq[ i ];
        pq[ i ] = pq[ j ];
        pq[ j ] = temp;
    }

    public boolean less( int i, int j ) {
        return pq[ i ].compareTo( pq[ j ] ) == -1;
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

    public void swim( int k ) {
        while ( k > 1 && less( k / 2, k ) ) {
            exchange( k / 2, k );
            k /= 2;
        }
    }

    public Key delMax() {
        Key max = pq[ 1 ];
        exchange( 1, N-- );
        pq[ N + 1 ] = null;
        sink( 1 );
        return max;
    }

    public void insert( Key k ) {
        pq[ ++N ] = k;
        swim( N );
    }

    public String toString() {
        return java.util.Arrays.toString( pq );
    }

    public String toStringDelMax() {
        String rv = "{ ";

        while ( ! isEmpty() ) {
            rv += delMax() + ", ";
        }

        rv += "}";
        return rv;
    }

    public static void main( String[] args ) {
        Integer[] intArr = { 14, 12, 10, 8, 6, 4, 2, 0, 1, 3, 5, 7, 9, 11, 13 };
        MaxPQArrayConstructor< Integer > maxPQ = new MaxPQArrayConstructor< Integer >( intArr );
        /* for ( int i = 0; i < intArr.length; ++i ) {
            maxPQ.insert( intArr[ i ] );
        } */

        StdOut.println( "DEBUG: maxPQ (BEFORE): " + maxPQ.toString() );
        StdOut.println( "DEBUG: maxPQ (AFTER): " + maxPQ.toStringDelMax() );

    }
}
