package com.company;
import edu.princeton.cs.algs4.*;

public class SortingParallelArrays {

    public static int[] insertionSort( Comparable[] a ) {
        int[] indexArr = new int[ a.length ];
        for ( int i = 0; i < a.length; ++i ) {
            indexArr[ i ] = i;
        }

        for ( int i = 1; i < a.length; ++i ) {
            for ( int j = i; j >= 1 && less( a[ indexArr[ j ] ], a[ indexArr[ j - 1 ] ] ); --j ) {
                exchange( indexArr, j, j - 1 );
            }
        }

        return indexArr;
    }

    public static void exchange( int[] a, int i, int j ) {
        int temp = a[ i ];
        a[ i ] = a[ j ];
        a[ j ] = temp;
    }

    public static boolean less( Comparable a, Comparable b ) {
        return a.compareTo( b ) == -1;
    }

    public static void main( String[] args ) {
        Integer[] intArr = { 14, 12, 10, 8, 6, 4, 2, 0, 1, 3, 5, 7, 9, 11, 13 };
        int[] indexArr = insertionSort( intArr );

        StdOut.println( "DEBUG: intArr (AFTER): " + java.util.Arrays.toString( intArr ) );
        StdOut.println( "DEBUG: indexArr (AFTER): " + java.util.Arrays.toString( indexArr ) );

        for ( int i = 0; i < indexArr.length; ++i ) {
            StdOut.println( "DEBUG: intArr ( " + i + " ): " + intArr[ indexArr[ i ] ] );
        }
    }
}
