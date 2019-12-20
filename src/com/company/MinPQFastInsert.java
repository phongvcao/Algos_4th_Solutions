package com.company;
import edu.princeton.cs.algs4.*;
import java.lang.Math;

public class MinPQFastInsert< Key extends Comparable< Key > > {

    private Key[] pq;
    private int N = 0;

    public MinPQFastInsert( int minN ) {
        pq = ( Key[] )new Comparable[ minN + 1 ];

        /* // DEBUG
        // Integer[] intArr = { null, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
        Integer[] intArr = { null, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 4 };
        for ( int i = 0; i < intArr.length; ++i ) {
            pq[ i ] = ( Key )intArr[ i ];
        }
        swimLogLogN( 15 );
        // END OF DEBUG */
    }

    public boolean less( int i, int j ) {
        return pq[ i ].compareTo( pq[ j ] ) == -1;
    }

    public void exchange( int i, int j ) {
        Key temp = pq[ i ];
        pq[ i ] = pq[ j ];
        pq[ j ] = temp;
    }

    public void insert( Key k ) {
        pq[ ++N ] = k;
        swimLogLogN( N );
    }

    public String toString( int[] indexArr ) {
        String rv = "{ ";
        for ( int i = 0; i < indexArr.length; ++i ) {
            rv += pq[ indexArr[ i ] ] + ", ";
        }
        rv += "}";
        return rv;
    }

    public void swimLogLogN( int k ) {
        int[] pathToRoot = new int[ (int)( Math.log( k ) / Math.log( 2 ) ) ];
        int pathToRootSize = pathToRoot.length;
        int kIndex = k;
        while ( kIndex > 1 ) {
            kIndex /= 2;
            pathToRoot[ --pathToRootSize ] = kIndex;
        }

        StdOut.println( "======================================" );
        StdOut.println( "DEBUG: Inserting: " + pq[ k ] );
        StdOut.println( "DEBUG: pathToRoot: " + java.util.Arrays.toString( pathToRoot ) );
        StdOut.println( "DEBUG: pathToRoot ( PQ ): " + toString( pathToRoot ) );

        int low = 0;
        int high = pathToRoot.length - 1;
        int mid = -1;
        while ( low < high ) {
            mid = ( low + high ) / 2;
            StdOut.println( "DEBUG: Looking at low : " + low + " ; high : " + high + " ; k : " + k + " ; mid : " + mid );
            StdOut.println( "DEBUG: pq: " + java.util.Arrays.toString( pq ) );
            if ( less( pathToRoot[ mid ], k ) ) {
                low = mid + 1;
            } else {
                high = mid;
            }
        }

        if ( mid > -1 ) {
            if ( less( pathToRoot[ mid ], k ) ) {
                mid += 1;
            }

            if ( ! less( k, pathToRoot[ mid ] ) ) {
                return;
            }

            Key temp = pq[ k ];
            pq[ k ] = pq[ pathToRoot[ pathToRoot.length - 1 ] ];
            for ( int i = pathToRoot.length - 1; i > mid; --i ) {
                StdOut.println( "Assigning pq[ pathToRoot[ i - 1 ] ] : " + pq[ pathToRoot[ i - 1 ] ] + " to pq[ pathToRoot[ i ] ] : " + pq[ pathToRoot[ i ] ] );
                pq[ pathToRoot[ i ] ] = pq[ pathToRoot[ i - 1 ] ];
            }
            StdOut.println( "DEBUG: found ( mid ): " + mid );
            StdOut.println( "DEBUG: found: " + pathToRoot[ mid ] );
            StdOut.println( "DEBUG: found ( PQ ): " + pq[ pathToRoot[ mid ] ] );
            pq[ pathToRoot[ mid ] ] = temp;
            StdOut.println( "DEBUG: pq: " + java.util.Arrays.toString( pq ) );
        }
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

    public String toString() {
        return java.util.Arrays.toString( pq );
    }

    public int size() {
        return N;
    }

    public boolean isEmpty() {
        return size() == 0;
    }

    public String toStringDelMin() {
        String rv = "{";

        while ( ! isEmpty() ) {
            rv += delMin() + ", ";
        }

        rv += "}";
        return rv;
    }

    public Key min() {
        return pq[ 1 ];
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
        MinPQFastInsert< Integer > minPQ = new MinPQFastInsert< Integer >( intArr.length );
        for ( int i = 0; i < intArr.length; ++i ) {
            minPQ.insert( intArr[ i ] );
        }

        StdOut.println( "DEBUG: minPQ (BEFORE): " + minPQ.toString() );
        StdOut.println( "DEBUG: minPQ (AFTER): " + minPQ.toStringDelMin() );

        /* // DEBUG
        MinPQFastInsert< Integer > minPQ = new MinPQFastInsert< Integer >( 16 );
        // END OF DEBUG */
    }
}
