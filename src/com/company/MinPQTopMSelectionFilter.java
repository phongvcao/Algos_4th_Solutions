package com.company;
import edu.princeton.cs.algs4.*;
import java.lang.Double;
import java.lang.Math;

public class MinPQTopMSelectionFilter {

    private static class Point {
        public Double x = 0.0;
        public Double y = 0.0;
        public Double z = 0.0;
        public Double distance = 0.0;

        public Point( Double x, Double y, Double z ) {
            this.x = x;
            this.y = y;
            this.z = z;
            this.distance = Math.sqrt( Math.pow( this.x, 2 ) + Math.pow( this.y, 2 ) + Math.pow( this.z, 2 ) );
        }

        public String toString() {
            return " | x : " + this.x + " , y : " + this.y + " , z : " + this.z + " , distance : " + this.distance + " | ";
        }

        public int compareTo( Point other ) {
            return this.distance.compareTo( other.distance );
        }
    }

    private int N = 0;
    private Point[] pq;

    public MinPQTopMSelectionFilter( int maxN ) {
        pq = new Point[ maxN + 1 ];
    }

    public boolean less( Point a, Point b ) {
        return a.compareTo( b ) == -1;
    }

    public boolean less( int i, int j ) {
        return pq[ i ].compareTo( pq[ j ] ) == -1;
    }

    public void exchange( int i, int j ) {
        Point temp = pq[ i ];
        pq[ i ] = pq[ j ];
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

    public void insert( Point p ) {
        pq[ ++N ] = p;
        swim( N );
    }

    public Point min() {
        return pq[ 1 ];
    }

    public Point delMin() {
        Point min = min();
        exchange( 1, N-- );
        pq[ N + 1 ] = null;
        sink( 1 );
        return min;
    }

    public void swim( int k ) {
        while ( k > 1 && less( k, k / 2 ) ) {
            exchange( k / 2, k );
            k /= 2;
        }
    }

    public void sink( int k ) {
        while ( 2 * k <= N ) {
            int j = 2 * k;
            if ( j < N && less( j + 1, j ) ) ++j;
            if ( ! less( j, k ) ) break;
            exchange( k, j );
            k = j;
        }
    }

    public String toStringDelMin() {
        String rv = "{ ";

        while ( ! isEmpty() ) {
            rv += delMin() + ", ";
        }

        rv += "}";
        return rv;
    }

    public static void main( String[] args ) {
        int N = 5;
        MinPQTopMSelectionFilter minPQ = new MinPQTopMSelectionFilter( N * N * N );

        for ( int i = 0; i < N; ++i ) {
            for ( int j = 0; j < N; ++j ) {
                for ( int k = 0; k < N; ++k ) {
                    minPQ.insert( new Point( (double)i, (double)j, (double)k ) );
                }
            }
        }

        StdOut.println( "DEBUG: minPQ (BEFORE): " + minPQ.toString() );
        StdOut.println( "DEBUG: minPQ (AFTER): " + minPQ.toStringDelMin() );
    }
}
