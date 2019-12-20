package com.company;
import edu.princeton.cs.algs4.*;

public class QuickSortFast3WayPartitioning1 {

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

        int i = low;
        int j = high + 1;
        int p = low;
        int q = high + 1;
        Comparable pivot = a[ low ];

        while ( true ) {
            if ( i > low && a[ i ].compareTo( pivot ) == 0 ) {
                exchange( a, ++p, i );
            }

            if ( j <= high && a[ j ].compareTo( pivot ) == 0 ) {
                exchange( a, --q, j );
            }

            while ( less( a[ ++i ], pivot ) ) if ( i == high ) break;
            while ( less( pivot, a[ --j ] ) ) if ( j == low ) break;

            if ( i == j && a[ i ].compareTo( pivot ) == 0 ) {
                exchange( a, ++p, i );
            }

            if ( i >= j ) break;

            exchange( a, i, j );
        }

        i = j + 1;
        for ( int k = low; k <= p; ++k ) {
            exchange( a, k, j-- );
        }
        for ( int k = high; k >= q; --k ) {
            exchange( a, k, i++ );
        }

        sort( a, low, j );
        sort( a, i, high );
    }

    public static void main( String[] args ) {
        Integer[] intArr = { 4, 14, 12, 10, 8, 6, 4, 4, 4, 4, 4, 2, 0, 1, 3, 5, 7, 9, 11, 13 };

        StdOut.println( "DEBUG: intArr (BEFORE): " + java.util.Arrays.toString( intArr ) );

        sort( intArr );

        StdOut.println( "DEBUG: intArr (AFTER): " + java.util.Arrays.toString( intArr ) );
    }
}
