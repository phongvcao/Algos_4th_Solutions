package com.company;
import edu.princeton.cs.algs4.*;

public class RecursiveSelect {

    public static Comparable select( Comparable[] a, int k ) {
        StdRandom.shuffle( a );
        int low = 0;
        int high = a.length - 1;
        while ( high > low ) {
            int j = partition( a, low, high );
            if ( j == k ) {
                return a[ k ];
            } else if ( j > k ) {
                high = j - 1;
            } else if ( j < k ) {
                low = j + 1;
            }
        }

        return a[ k ];
    }

    public static Comparable selectRecursively( Comparable[] a, int k ) {
        StdRandom.shuffle( a );
        return selectRecursively( a, k, 0, a.length - 1 );
    }

    public static Comparable selectRecursively( Comparable[] a, int k, int low, int high ) {
        if ( low >= high ) return a[ k ];

        int j = partition( a, low, high );
        if ( j == k ) {
            return a[ k ];
        } else if ( j > k ) {
            return selectRecursively( a, k, low, j - 1 );
        } else if ( j < k ) {
            return selectRecursively( a, k, j + 1, high );
        }

        return a[ k ];
    }

    public static int partition( Comparable[] a, int low, int high ) {
        int i = low;
        int j = high + 1;
        Comparable pivot = a[ low ];

        while ( true ) {
            while ( less( a[ ++i ], pivot ) ) if ( i == high ) break;
            while ( less( pivot, a[ --j ] ) ) if ( j == low ) break;

            if ( i >= j ) {
                break;
            }

            exchange( a, i, j );
        }
        exchange( a, low, j );
        return j;
    }

    public static void quickSort( Comparable[] a ) {
        quickSort( a, 0, a.length - 1 );
    }

    public static void quickSort( Comparable[] a, int low, int high ) {
        if ( low >= high ) return;

        int j = partition( a, low, high );
        quickSort( a, low, j - 1 );
        quickSort( a, j + 1, high );
    }

    public static boolean less( Comparable a, Comparable b ) {
        return a.compareTo( b ) == -1;
    }

    public static void exchange( Comparable[] a, int i, int j ) {
        Comparable temp = a[ i ];
        a[ i ] = a[ j ];
        a[ j ] = temp;
    }

    public static void main( String[] args ) {
        Integer[] intArr = { 14, 12, 10, 8, 6, 4, 2, 0, 1, 3, 5, 7, 9, 11, 13 };

        StdOut.println( "DEBUG: intArr (BEFORE): " + java.util.Arrays.toString( intArr ) );

        // quickSort( intArr );

        // StdOut.println( "DEBUG: intArr (AFTER): " + java.util.Arrays.toString( intArr ) );

        // StdOut.println( "DEBUG: intArr (AFTER select( 0 ): " + select( intArr, intArr.length / 2 ) );

        StdOut.println( "DEBUG: intArr (AFTER select( 0 ): " + selectRecursively( intArr, intArr.length / 2 ) );
    }
}
