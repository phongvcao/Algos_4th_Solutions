package com.company;
import edu.princeton.cs.algs4.*;

public class QuickSortFast3WayPartitioning {

    public static boolean less( Comparable a, Comparable b ) {
        return a.compareTo( b ) == -1;
    }

    public static void exchange( Comparable[] a, int i, int j ) {
        Comparable temp = a[ i ];
        a[ i ] = a [ j ];
        a[ j ] = temp;
    }

    public static void sort( Comparable[] a ) {
        sort( a, 0, a.length - 1 );
    }

    public static void sort( Comparable[] a, int low, int high ) {
        if ( low >= high ) return;

        // int j = partition( a, low, high );
        int j = partitionFast3Ways( a, low, high );
        sort( a, low, j - 1 );
        sort( a, j + 1, high );
    }

    public static int partition( Comparable[] a, int low, int high ) {
        int i = low;
        int lt = low;
        int gt = high;
        Comparable pivot = a[ low ];

        while ( i <= high ) {
            if ( a[ i ].compareTo( pivot ) < 0 ) {
                exchange( a, lt++, i++ );
            } else if ( a[ i ].compareTo( pivot ) > 0 ) {
                exchange( a, i++, gt-- );
            } else {
                ++i;
            }
        }

        return lt;
    }

    public static boolean equals( Comparable a, Comparable b ) {
        return a.compareTo( b ) == 0;
    }

    public static int partitionFast3Ways( Comparable[] a, int low, int high ) {
        int i = low + 1;
        int p = low + 1;
        int q = high;
        int j = high;
        Comparable pivot = a[ low ];

        while ( i <= j ) {
            int cmp = a[ i ].compareTo( pivot );
            if ( cmp > 0 ) {
                exchange( a, i, j-- );
            } else if ( cmp < 0 ) {
                ++i;
            } else {
                exchange( a, i, p++ );
            }
        }

        while ( ( j >= p ) && ( a[ j ].compareTo( pivot ) < 0 ) ) {
            exchange( a, j - p, j );
            --j;
        }

        StdOut.println( "DEBUG: pivot: " + pivot );
        StdOut.println( "DEBUG: PARTITIONED: " + java.util.Arrays.toString( a ) );

        StdOut.println( "DEBUG: j: " + j );
        StdOut.println( "DEBUG: p: " + p );
        StdOut.println( "DEBUG: i: " + i );

        // exchange( a, low, j );
        return j;
    }

    public static void main( String[] args ) {
        Integer[] intArr = { 4, 14, 12, 10, 8, 6, 4, 4, 4, 4, 4, 2, 0, 1, 3, 5, 7, 9, 11, 13 };

        StdOut.println( "DEBUG: intArr (BEFORE): " + java.util.Arrays.toString( intArr ) );

        sort( intArr );

        StdOut.println( "DEBUG: intArr (AFTER): " + java.util.Arrays.toString( intArr ) );

        /* Integer[] intArr = { 4, 14, 12, 10, 8, 6, 4, 4, 4, 4, 4, 2, 0, 1, 3, 5, 7, 9, 11, 13 };

        StdOut.println( "DEBUG: intArr (BEFORE): " + java.util.Arrays.toString( intArr ) );

        int j = partitionFast3Ways( intArr, 0, intArr.length - 1 );

        StdOut.println( "DEBUG: intArr (AFTER): " + java.util.Arrays.toString( intArr ) + " ; j: " + j ); */
    }
}
