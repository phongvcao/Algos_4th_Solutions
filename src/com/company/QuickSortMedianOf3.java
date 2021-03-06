package com.company;
import edu.princeton.cs.algs4.*;

public class QuickSortMedianOf3 {

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

    public static int partition( Comparable[] a, int low, int high ) {
        int i = low;
        int j = high + 1;

        int middle = ( low + high ) / 2;

        if ( less( a[ middle ], a[ low ] ) ) {
            exchange( a, low, middle );
        }

        if ( less( a[ high ], a[ low ] ) ) {
            exchange( a, high, low );
        }

        if ( less( a[ high ], a[ middle ] ) ) {
            exchange( a, high, middle );
        }

        exchange( a, middle, low );
        Comparable pivot = a[ low ];

        while ( true ) {
            while ( less( a[ ++i ], pivot ) );
            while ( less( pivot, a[ --j ] ) );

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
    }
}
