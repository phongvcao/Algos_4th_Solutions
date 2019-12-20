package com.company;
import edu.princeton.cs.algs4.*;

public class PriorityQueueStable< Key extends Comparable< Key > > {

    private static class Element implements Comparable< Element > {

        public Integer index = -1;
        public Comparable value = null;

        public Element( Comparable value, Integer index ) {
            this.value = value;
            this.index = index;
        }

        public int compareTo( Element other ) {
            int cmp = this.value.compareTo( other.value );

            if ( cmp != 0 ) return cmp;

            return this.index.compareTo( other.index );
        }

        public String toString() {
            return this.value + " " + this.index;
        }
    }

    private Key[] pq;
    private int N = 0;

    public PriorityQueueStable( int maxN ) {
        pq = ( Key[] )new Comparable[ maxN + 1 ];
    }

    private void sink( int k ) {
        while ( 2 * k <= N ) {
            int j = 2 * k;
            if ( j < N && less( j, j + 1 ) ) ++j;
            if ( ! less( k, j ) ) break;
            exchange( k, j );
            k = j;
        }
    }

    private void swim( int k ) {
        while ( k > 1 && less( k / 2, k ) ) {
            exchange( k / 2, k );
            k /= 2;
        }
    }

    public boolean isEmpty() {
        return size() == 0;
    }

    public int size() {
        return N;
    }

    public void insert( Key k ) {
        pq[ ++N ] = k;
        swim( N );
    }

    public Key max() {
        return pq[ 1 ];
    }

    public Key delMax() {
        Key max = pq[ 1 ];
        exchange( 1, N-- );
        pq[ N + 1 ] = null;
        sink( 1 );
        return max;
    }

    private boolean less( int i, int j ) {
        return pq[ i ].compareTo( pq[ j ] ) == -1;
    }

    private void exchange( int i, int j ) {
        Key temp = pq[ i ];
        pq[ i ] = pq[ j ];
        pq[ j ] = temp;
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
        Integer[] intArr = { 14, 12, 10, 8, 6, 4, 2, 2, 2, 2, 2, 2, 2, 0, 1, 3, 5, 7, 9, 11, 13 };
        PriorityQueueStable< Element > maxPQ = new PriorityQueueStable< Element >( intArr.length );

        for ( int i = 0; i < intArr.length; ++i ) {
            maxPQ.insert( new Element( intArr[ i ], i ) );
        }

        StdOut.println( "DEBUG: maxPQ (BEFORE): " + maxPQ );
        StdOut.println( "DEBUG: maxPQ (AFTER): " + maxPQ.toStringDelMax() );
    }
}
