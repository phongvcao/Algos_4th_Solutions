package com.company;
import edu.princeton.cs.algs4.*;

public class MaxMinPQMedianFinding< Key extends Comparable< Key > > {

    private Key[] maxPQ; // Smaller numbers
    private Key[] minPQ; // Larger numbers
    private int maxN = 0;
    private int minN = 0;

    public MaxMinPQMedianFinding( int N ) {
        maxPQ = ( Key[] )new Comparable[ N + 1 ];
        minPQ = ( Key[] )new Comparable[ N + 1 ];
    }

    public int size() {
        return maxN + minN;
    }

    public boolean isEmpty() {
        return size() == 0;
    }

    public boolean less( Key a, Key b ) {
        return a.compareTo( b ) == -1;
    }

    public String toString() {
        return "maxPQ : " + java.util.Arrays.toString( maxPQ ) + " ; minPQ : " + java.util.Arrays.toString( minPQ );
    }

    public void exchange( int i, int j, boolean isMaxPQ ) {
        if ( isMaxPQ ) {
            Key temp = maxPQ[ i ];
            maxPQ[ i ] = maxPQ[ j ];
            maxPQ[ j ] = temp;
        } else {
            Key temp = minPQ[ i ];
            minPQ[ i ] = minPQ[ j ];
            minPQ[ j ] = temp;
        }
    }

    public void swim( int k, boolean isMaxPQ ) {
        if ( isMaxPQ ) {
            while ( k > 1 && less( maxPQ[ k / 2 ], maxPQ[ k ] ) ) {
                exchange( k / 2, k, true );
                k /= 2;
            }
        } else {
            while ( k > 1 && less( minPQ[ k ], minPQ[ k / 2 ] ) ) {
                exchange( k / 2, k, false );
                k /= 2;
            }
        }
    }

    public void sink( int k, boolean isMaxPQ ) {
        if ( isMaxPQ ) {
            while ( 2 * k <= maxN ) {
                int j = 2 * k;
                if ( j < maxN && less( maxPQ[ j ], maxPQ[ j + 1 ] ) ) ++j;
                if ( ! less( maxPQ[ k ], maxPQ[ j ] ) ) break;
                exchange( j, k, true );
                k = j;
            }
        } else {
            while ( 2 * k <= minN ) {
                int j = 2 * k;
                if ( j < minN && less( minPQ[ j + 1 ], minPQ[ j ] ) ) ++j;
                if ( ! less( minPQ[ j ], minPQ[ k ] ) ) break;
                exchange( j, k, false );
                k = j;
            }
        }
    }

    public void insert( Key k ) {
        // insert() should take logarithmic time
        // First, pop off everything from maxPQ & insert into minPQ
        // Then, insert k into minPQ
        // Then, insert minN / 2 + 1 of minPQ to maxPQ
        // If they're equal, do nothing

        // Insert into minPQ
        minPQ[ ++minN ] = k;
        swim( minN, false );

        // Now compare minPQ[ 1 ] & maxPQ[ 1 ].
        // If minPQ[ 1 ] < maxPQ[ 1 ], exchange the 2 & sink( 1 ) for maxPQ
        while ( ( minPQ[ 1 ] != null ) && ( maxPQ[ 1 ] != null ) && ( less( minPQ[ 1 ], maxPQ[ 1 ] ) ) ) {
            Key temp = minPQ[ 1 ];
            minPQ[ 1 ] = maxPQ[ 1 ];
            maxPQ[ 1 ] = temp;
            sink( 1, true );
        }

        // Maybe pop off minPQ & insert into maxPQ
        if ( minN > maxN ) {
            // Pop off minPQ
            Key min = minPQ[ 1 ];
            exchange( 1, minN--, false );
            minPQ[ minN + 1 ] = null;
            sink( 1, false );

            // Insert into maxPQ
            maxPQ[ ++maxN ] = min;
            swim( maxN, true );
        }
    }

    public Key delMedian() {
        // Simply delMax() & then see if minN > maxN
        // If minN > maxN, pop off minN & insert into maxN

        // Pop off maxPQ
        Key max = maxPQ[ 1 ];
        exchange( 1, maxN--, true );
        maxPQ[ maxN + 1 ] = null;
        sink( 1, true );

        // Pop off minN & insert into maxN
        if ( minN > maxN ) {
            // Pop off minPQ
            Key min = minPQ[ 1 ];
            exchange( 1, minN--, false );
            minPQ[ minN + 1 ] = null;
            sink( 1, false );

            // Insert into maxPQ
            maxPQ[ ++maxN ] = min;
            swim( maxN, true );
        }

        return max;
    }

    public Key median() {
        if ( maxN == minN ) {
            return ( Key )(Integer)( ( (Integer)maxPQ[ 1 ] + (Integer)minPQ[ 1 ] ) / 2 );
        } else {
            return maxPQ[ 1 ];
        }
    }

    public static void main( String[] args ) {
        Integer[] intArr = { 14, 12, 10, 8, 6, 4, 2, 0, 1, 3, 5, 7, 9, 11, 13 };
        MaxMinPQMedianFinding maxMinPQ = new MaxMinPQMedianFinding( intArr.length );
        for ( int i = 0; i < intArr.length; ++i ) {
            maxMinPQ.insert( intArr[ i ] );
        }

        StdOut.println( "DEBUG: median(): " + maxMinPQ.median() );

        while ( ! maxMinPQ.isEmpty() ) {
            StdOut.println( "DEBUG: maxMinPQ: " + maxMinPQ.toString() );
            StdOut.println( "DEBUG: delMedian(): " + maxMinPQ.delMedian() );
        }
    }
}
