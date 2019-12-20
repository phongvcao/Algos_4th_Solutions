package com.company;
import edu.princeton.cs.algs4.*;

public class QuickSortSampleSort {

    public static final int SAMPLE_SIZE = 7;

    public static boolean less( Comparable a, Comparable b ) {
        return a.compareTo( b ) == -1;
    }

    public static void exchange( Comparable[] a, int i, int j ) {
        Comparable temp = a[ i ];
        a[ i ] = a[ j ];
        a[ j ] = temp;
    }

    public static void sampleSort( Comparable[] a ) {
        sampleSort( a, 0, a.length - 1 );
    }

    public static void sampleSort( Comparable[] a, int low, int high ) {
        if ( low >= high ) return;

        int j = partition( a, low, high );
        sampleSort( a, low, j - 1 );
        sampleSort( a, j + 1, high );
    }

    public static int partition( Comparable[] a, int low, int high ) {
        int i = low;
        int j = high + 1;
        if ( high - low + 1 >= SAMPLE_SIZE ) {
            Insertion.sort( a, low, low + SAMPLE_SIZE );
            int medianIdx = low + ( SAMPLE_SIZE - 1 ) / 2;
            exchange( a, medianIdx, low );
        }
        Comparable pivot = a[ low ];

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

        sampleSort( intArr );

        StdOut.println( "DEBUG: intArr (AFTER): " + java.util.Arrays.toString( intArr ) );
    }
}
