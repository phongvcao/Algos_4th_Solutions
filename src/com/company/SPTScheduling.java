package com.company;
import edu.princeton.cs.algs4.*;

public class SPTScheduling {

    private static class Job implements Comparable< Job > {
        public int index = -1;
        public int time = -1;

        public Job( int index, int time ) {
            this.index = index;
            this.time = time;
        }

        public int compareTo( Job other ) {
            if ( this.time < other.time ) {
                return -1;
            } else if ( this.time > other.time ) {
                return 1;
            } else {
                return 0;
            }
        }

        public String toString() {
            return " | " + this.index + " : " + this.time + " | ";
        }
    }

    private Job[] pq;
    private int N = 0;

    public SPTScheduling( int minN ) {
        pq = new Job[ minN + 1 ];
    }

    public boolean isEmpty() {
        return size() == 0;
    }

    public int size() {
        return N;
    }

    private void exchange( int i, int j ) {
        Job temp = pq[ i ];
        pq[ i ] = pq[ j ];
        pq[ j ] = temp;
    }

    private boolean less( int i, int j ) {
        return pq[ i ].compareTo( pq[ j ] ) == -1;
    }

    private void sink( int k ) {
        while ( 2 * k <= N ) {
            int j = 2 * k;
            if ( j < N && less( j + 1, j ) ) ++j;
            if ( ! less( j, k ) ) break;
            exchange( k, j );
            k = j;
        }
    }

    private void swim( int k ) {
        while ( k > 1 && less( k, k / 2 ) ) {
            exchange( k / 2, k );
            k /= 2;
        }
    }

    public Job delMin() {
        Job min = pq[ 1 ];
        exchange( 1, N-- );
        pq[ N + 1 ] = null;
        sink( 1 );
        return min;
    }

    public Job min() {
        return pq[ 1 ];
    }

    public void insert( Job job ) {
        pq[ ++N ] = job;
        swim( N );
    }

    public String toString() {
        return java.util.Arrays.toString( pq );
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
        Integer[] intArr = { 14, 12, 10, 8, 6, 4, 2, 0, 1, 3, 5, 7, 9, 11, 13 };
        SPTScheduling spt = new SPTScheduling( intArr.length );

        for ( int i = 0; i < intArr.length; ++i ) {
            spt.insert( new Job( intArr[ i ], intArr[ i ] ) );
        }

        StdOut.println( "DEBUG: spt (BEFORE): " + spt.toString() );
        StdOut.println( "DEBUG: spt (AFTER): " + spt.toStringDelMin() );
    }
}
