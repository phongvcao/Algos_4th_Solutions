package com.company;
import edu.princeton.cs.algs4.*;

public class MergeSortNatural {

    public static boolean less( Comparable a, Comparable b ) {
        return a.compareTo( b ) == -1;
    }

    public static void sort( Comparable[] a ) {
        Comparable[] aux = new Comparable[ a.length ];
        sort( a, aux, 0, a.length - 1 );
    }

    public static void sort( Comparable[] a, Comparable[] aux, int low, int high ) {
        if ( low >= high ) return;
        int mid = ( low + high ) / 2;

        sort( a, aux, low, mid );
        sort( a, aux, mid + 1, high );
        merge( a, aux, low, mid, high );
    }

    public static void sortNatural( Comparable[] a ) {
        Comparable[] aux = new Comparable[ a.length ];
        sortNatural( a, aux, 0, a.length - 1 );
    }

    public static void sortNatural( Comparable[] a, Comparable[] aux, int low, int high ) {
        int start = low;
        int i = start;

        while ( ( i < high ) && ( a[ i ].compareTo( a[ i + 1 ] ) <= 0 ) ) {
            ++i;
        }

        if ( i >= high ) {
            return;
        }

        int next = i + 1;
        int j = next;

        while ( ( j < high ) && ( a[ j ].compareTo( a[ j + 1 ] ) <= 0 ) ) {
            ++j;
        }

        merge( a, aux, start, i, j );
        sortNatural( a, aux, low, high );
    }

    public static void merge( Comparable[] a, Comparable[] aux, int low, int mid, int high ) {
        int i = low;
        int j = mid + 1;

        for ( int k = low; k <= high; ++k ) {
            aux[ k ] = a[ k ];
        }

        for ( int k = low; k <= high; ++k ) {
            if ( i > mid ) {
                a[ k ] = aux[ j++ ];
            } else if ( j > high ) {
                a[ k ] = aux[ i++ ];
            } else if ( less( aux[ j ], aux[ i ] ) ) {
                a[ k ] = aux[ j++ ];
            } else {
                a[ k ] = aux[ i++ ];
            }
        }
    }

    public static void main( String[] args ) {
        Integer[] intArr = { 14, 12, 10, 8, 6, 4, 2, 0, 1, 3, 5, 7, 9 };

        // sort( intArr );
        sortNatural( intArr );

        StdOut.println( "DEBUG: " + java.util.Arrays.toString( intArr ) );
    }
}
