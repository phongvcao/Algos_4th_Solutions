package com.company;
import edu.princeton.cs.algs4.*;

import java.util.Collections;
import java.util.HashMap;
import java.util.Random;
import java.util.ArrayList;

public class QuickSortMedianOf5 {

    public static boolean less( Comparable a, Comparable b ) {
        return a.compareTo( b ) == -1;
    }

    public static void exchange( Comparable[] a, int i, int j ) {
        Comparable temp = a[ i ];
        a[ i ] = a[ j ];
        a[ j ] = temp;
    }

    public static void sort( Comparable[] a ) {
        sort( a, 0, a.length - 1 );
    }

    public static void sort( Comparable[] a, int low, int high ) {
        if ( low >= high ) return;

        int j = partition( a, low, high );
        sort( a, low, j - 1 );
        sort( a, j + 1, high );
    }

    public static void exchange( ArrayList< Comparable > a, int i, int j ) {
        Comparable temp = a.get( i );
        a.add( i, a.get( j ) );
        a.add( j, temp );
    }

    public static int getPivot( Comparable[] a, int low, int high ) {
        if ( high - low < 4 ) return low;
        Integer[] randomIndexes = new Integer[ 5 ];
        for ( int i = 0; i < 5; ++i ) {
            randomIndexes[ i ] = low + i;
        }
        // Collections.shuffle( randomIndexes );

        /* HashMap< Comparable, Integer > randomElementMap = new HashMap< Comparable, Integer >();
        randomElementMap.put( a[ randomIndexes.get( 0 ) ], randomIndexes.get( 0 ) );
        randomElementMap.put( a[ randomIndexes.get( 1 ) ], randomIndexes.get( 1 ) );
        randomElementMap.put( a[ randomIndexes.get( 2 ) ], randomIndexes.get( 2 ) );
        randomElementMap.put( a[ randomIndexes.get( 3 ) ], randomIndexes.get( 3 ) );
        randomElementMap.put( a[ randomIndexes.get( 4 ) ], randomIndexes.get( 4 ) ); */

        // Find median
        // Comparison 1
        if ( less( a[ randomIndexes[ 1 ] ], a[ randomIndexes[ 0 ] ] ) ) {
            exchange( randomIndexes, 1, 0 );
        }

        // Comparison 2
        if ( less( a[ randomIndexes[ 3 ] ], a[ randomIndexes[ 2 ] ] ) ) {
            exchange( randomIndexes, 3, 2 );
        }

        // Comparison 3
        if ( less( a[ randomIndexes[ 3 ] ], a[ randomIndexes[ 1 ] ] ) ) {
            exchange( randomIndexes, 3, 1 );
            exchange( randomIndexes, 0, 2 );
        }

        // Comparison 4
        if ( less( a[ randomIndexes[ 4 ] ], a[ randomIndexes[ 2 ] ] ) ) {
            exchange( randomIndexes, 4, 2 );
        }

        // Comparison 5
        if ( less( a[ randomIndexes[ 4 ] ], a[ randomIndexes[ 1 ] ] ) ) {
            exchange( randomIndexes, 4, 1 );
            exchange( randomIndexes, 2, 0 );
        }

        // Comparison 6
        if ( less( a[ randomIndexes[ 1 ] ], a[ randomIndexes[ 2 ] ] ) ) {
            return randomIndexes[ 2 ];
        } else {
            return randomIndexes[ 1 ];
        }
    }

    public static int partition( Comparable[] a, int low, int high ) {
        int i = low;
        int j = high + 1;
        int pivotIndex = getPivot( a, low, high );
        Comparable pivot = a[ pivotIndex ];
        exchange( a, pivotIndex, low );

        while ( true ) {
            while ( less( a[ ++i ], pivot ) ) if ( i == high ) break;
            while ( less( pivot, a[ --j ] ) ) if ( j == low ) break;

            if ( i >= j ) break;

            exchange( a, i, j );
        }
        exchange( a, low, j );
        return j;
    }

    public static void main( String[] args ) {
        Integer[] intArr = { 14, 12, 10, 8, 6, 4, 2, 0, 1, 3, 5, 7, 9, 11, 13 };

        StdOut.println( "DEBUG: intArr (BEFORE): " + java.util.Arrays.toString( intArr ) );

        sort( intArr );

        StdOut.println( "DEBUG: intArr (AFTER): " + java.util.Arrays.toString( intArr ) );

        /* // DEBUG
        Integer[] intArr = { 22, 14, 12, 10, 80 };

        StdOut.println( "DEBUG: pivot: " + getPivot( intArr, 0, intArr.length - 1 ) );
        // END OF DEBUG */
    }
}
