package com.company;
import edu.princeton.cs.algs4.*;

public class MergeSortCountInversions1 {

    public static int exchangeCount = 0;

    public static boolean less( Comparable a, Comparable b ) {
        return a.compareTo( b ) == -1;
    }

    public static void exchange( Comparable[] a, int i, int j ) {
        Comparable temp = a[ i ];
        a[ i ] = a[ j ];
        a[ j ] = temp;
    }

    public static void insertionSort( Comparable[] a ) {
        for ( int i = 1; i < a.length; ++i ) {
            for ( int j = i; j > 0 && less( a[ j ], a[ j - 1 ] ); --j ) {
                exchange( a, j, j - 1 );
                ++exchangeCount;
            }
        }
    }

    public static boolean isSorted( Comparable[] a ) {
        for ( int i = 1; i < a.length; ++i ) {
            if ( less( a[ i ], a[ i - 1 ] ) ) {
                return false;
            }
        }
        return true;
    }

    public static int sort( Comparable[] a ) {
        Comparable[] aux = new Comparable[ a.length ];
        return sort( a, aux, 0, a.length - 1 );
    }

    public static int sort( Comparable[] a, Comparable[] aux, int low, int high ) {
        if ( low >= high ) return 0;
        int mid = ( low + high ) / 2;

        int xchangeCount = sort( a, aux, low, mid );
        xchangeCount += sort( a, aux, mid + 1, high );
        xchangeCount += merge( a, aux, low, mid, high );
        return xchangeCount;
    }

    public static int merge( Comparable[] a, Comparable[] aux, int low, int mid, int high ) {
        int i = low;
        int j = mid + 1;
        int xchangeCount = 0;

        // Copy from a to aux
        for ( int k = low; k <= high; ++k ) {
            aux[ k ] = a[ k ];
        }

        // Now do the merge
        for ( int k = low; k <= high; ++k ) {
            if ( i > mid ) {
                a[ k ] = aux[ j++ ];
            } else if ( j > high ) {
                a[ k ] = aux[ i++ ];
            } else if ( less( aux[ i ], aux[ j ] ) ) {
                a[ k ] = aux[ i++ ];
            } else {
                a[ k ] = aux[ j++ ];

                if ( high - j >= 0 ) {
                    xchangeCount += mid - low;
                }
            }
        }
        return xchangeCount;
    }

    public static void main( String[] args ) {
        Integer[] intArr = { 14, 12, 10, 8, 6, 4, 2, 0, 1, 3, 5, 7, 9, 11, 13 };

        StdOut.println( "DEBUG: intArr (BEFORE): " + java.util.Arrays.toString( intArr ) );

        // insertionSort( intArr );
        int xchangeCount = sort( intArr );

        StdOut.println( "DEBUG: intArr (AFTER): " + java.util.Arrays.toString( intArr ) );
        StdOut.println( "DEBUG: insertionSort (exchangeCount - EXPECTED: 56): " + exchangeCount );
        StdOut.println( "DEBUG: mergeSort - insertionSort (exchangeCount - EXPECTED: 56): " + xchangeCount );
    }
}
