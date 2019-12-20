package com.company;
import edu.princeton.cs.algs4.*;

public class HeapSortPreorder {

    public static int preorderIndex = 1;

    public static void exchange( Comparable[] a, int i, int j ) {
        Comparable temp = a[ i - 1 ];
        a[ i - 1 ] = a[ j - 1 ];
        a[ j - 1 ] = temp;
    }

    public static boolean less( Comparable[] a, int i, int j ) {
        return a[ i - 1 ].compareTo( a[ j - 1 ] ) == -1;
    }

    public static void exchange( Comparable[] a, int[] path, int i, int j ) {
        Comparable temp = a[ path[ i ] ];
        a[ path[ i ] ] = a[ path[ j ] ];
        a[ path[ j ] ] = temp;
    }

    public static boolean less( Comparable[] a, int[] path, int i, int j ) {
        return a[ path[ i ] ].compareTo( a[ path[ j ] ] ) == -1;
    }

    public static void sort( Comparable[] a ) {
        for ( int i = a.length / 2; i >= 1; --i ) {
            sink( a, i, a.length );
        }

        int N = a.length;
        while ( N > 1 ) {
            exchange( a, 1, N-- );
            sink( a, 1, N );
        }
    }

    public static void sink( Comparable[] a, int k, int N ) {
        while ( 2 * k <= N ) {
            int j = 2 * k;
            if ( j < N && less( a, j, j + 1 ) ) ++j;
            if ( ! less( a, k, j ) ) break;
            exchange( a, k, j );
            k = j;
        }
    }

    public static void sortPreorder( Comparable[] a ) {
        int[] path = new int[ a.length + 1 ];
        generatePreorderIndices( path, 1, a.length );

        for ( int i = a.length / 2; i >= 1; --i ) {
            // sinkPreorder( a, path, i, a.length );
        }

        int N = a.length;
        while ( N > 1 ) {
            exchange( a, path, 1, N-- );
            // sinkPreorder( a, path, 1, N );
        }
    }

    public static void sinkPreorder( Comparable[] a, int[] path, int currentIndex, int startPathIndex, int N ) {
        /* while ( 2 * k <= N ) {
            StdOut.println( "DEBUG: path: " + java.util.Arrays.toString( path ) );
            int j = 2 * startPathIndex;

            if ( startPathIndex < N ) {
                if ( less( a, path[ startPathIndex * 2 + 1 ], path[ startPathIndex * 2 ] ) ) {
                    j = startPathIndex * 2 + 1;
                }
            }

            // if ( ! less( a, currentIndex,  ) ) break;
            exchange( a, path, k, j );
            k = j;
        } */
    }

    public static void generatePreorderIndices( int[] path, int i, int N ) {
        if ( i >= N ) return;
        path[ preorderIndex++ ] = i;
        generatePreorderIndices( path, 2 * i, N );
        generatePreorderIndices( path, 2 * i + 1, N );
    }

    public static void main( String[] args ) {
        Integer[] intArr = { 14, 12, 10, 8, 6, 4, 2, 0, 1, 3, 5, 7, 9, 11, 13 };

        StdOut.println( "DEBUG: intArr (BEFORE): " + java.util.Arrays.toString( intArr ) );

        // sort( intArr );
        sortPreorder( intArr );

        StdOut.println( "DEBUG: intArr (AFTER): " + java.util.Arrays.toString( intArr ) );
    }
}
