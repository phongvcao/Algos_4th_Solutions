package com.company;
import edu.princeton.cs.algs4.*;
import java.lang.Math;

public class MinPQComputationalNumberTheory {

    private Number[] pq;
    private int N = 0;

    public static class Number {
        public Integer sum = 0;
        public Integer a = 0;
        public Integer b = 0;

        public Number( Integer a, Integer b ) {
            this.a = a;
            this.b = b;
            sum = (int)( Math.pow( a, 3 ) + Math.pow( b, 3 ) );
        }
    }

    public MinPQComputationalNumberTheory( int maxN ) {
        pq = new Number[ maxN + 1 ];
    }

    public Number min() {
        return pq[ 1 ];
    }

    public int size() {
        return N;
    }

    public boolean isEmpty() {
        return size() == 0;
    }

    public Number delMin() {
        Number min = min();
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

    public void insert( Number k ) {
        pq[ ++N ] = k;
        swim( N );
    }

    public String toString( Number a ) {
        return " | sum: " + a.sum + " , a : " + a.a + " , b : " + a.b + " | ";
    }

    public String toString() {
        String rv = "{ ";

        for ( int i = 1; i <= N; ++i ) {
            rv += toString( pq[ i ] );
        }

        rv += "}";
        return rv;
    }

    public String toStringDelMin() {
        String rv = "{ ";
        while ( ! isEmpty() ) {
            // rv += toString( delMin() );
            rv += delMin().sum + ", ";
        }

        rv += "}";
        return rv;
    }

    public boolean less( int i, int j ) {
        return pq[ i ].sum.compareTo( pq [ j ].sum ) == -1;
    }

    public void exchange( int i, int j ) {
        Number temp = pq[ i ];
        pq[ i ] = pq[ j ];
        pq[ j ] = temp;
    }

    public static void main( String[] args ) {
        int N = 15;
        MinPQComputationalNumberTheory minPQ = new MinPQComputationalNumberTheory( N + 1 );
        for ( int i = 0; i < N; ++i ) {
            Number n = new Number( i, 0 );
            minPQ.insert( n );
        }

        while ( ! minPQ.isEmpty() ) {
            Number min = minPQ.delMin();
            StdOut.println( " | sum : " + min.sum + " ; a : " + min.a + " ; b : " + min.b + " | " );

            if ( min.b < N ) {
                minPQ.insert( new Number( min.a, min.b + 1 ) );
            }
        }
    }
}
