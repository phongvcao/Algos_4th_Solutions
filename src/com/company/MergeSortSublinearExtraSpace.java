package com.company;
import edu.princeton.cs.algs4.*;

public class MergeSortSublinearExtraSpace {

    public static int N = 15;
    public static int M = 5;

    public static boolean less( Comparable a, Comparable b ) {
        return a.compareTo( b ) == -1;
    }

    public static void exchange( Comparable[] a, int i, int j ) {
        Comparable temp = a[ i ];
        a[ i ] = a[ j ];
        a[ j ] = temp;
    }

    public static void selectionSort( Comparable[] a, int low, int high ) {
        for ( int i = low; i < high; ++i ) {
            int minIdx = i;
            int j = i + 1;
            for ( j = i + 1; j <= high; ++j ) {
                if ( less( a[ j ], a[ minIdx ] ) ) {
                    minIdx = j;
                }
            }
            exchange( a, minIdx, i );
        }
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

    public static void sortSublinearExtraSpace( Comparable[] a, int low, int high ) {
        for ( int i = 0; i < N / M; ++i ) {
            selectionSort( a, low + i * M, low + ( i + 1 ) * M - 1 );
        }

        Comparable[] aux = new Comparable[ a.length ];
        int i = low;
        int j = M - 1;
        int k = 2 * M - 1;

        while ( k <= high ) {
            merge( a, aux, i, j, k );
            j = k;
            k += M;
        }
    }

    public static void main( String[] args ) {
        Integer[] intArr = { 14, 12, 10, 8, 6, 4, 2, 0, 1, 3, 5, 7, 9, 11, 13 };

        // sort( intArr );
        // selectionSort( intArr, 0, intArr.length - 1 );
        sortSublinearExtraSpace( intArr, 0, intArr.length - 1 );

        StdOut.println( "DEBUG: " + java.util.Arrays.toString( intArr ) );
    }
}
