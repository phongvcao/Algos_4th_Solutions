package com.company;
import edu.princeton.cs.algs4.*;

public class ShellSort {

    public static boolean less( Comparable v, Comparable w ) {
        return v.compareTo( w ) < 0;
    }

    public static void exchange( Comparable[] a, int i, int j ) {
        Comparable t = a[ i ];
        a[ i ] = a[ j ];
        a[ j ] = t;
    }

    public static boolean isSorted( Comparable[] a ) {
        for ( int i = 1; i < a.length; ++i ) {
            if ( less( a[ i ], a[ i - 1 ] ) ) {
                return false;
            }
        }
        return true;
    }

    public static void sort( Comparable[] a ) {
        // Sort a[] into increasing order
        int N = a.length;
        int h = 1;
        while ( h < N / 3 ) {
            h = 3 * h + 1;
        }

        while ( h >= 1 ) {
            for ( int i = h; i < N; ++i ) {
                StdOut.println( "DEBUG: h : " + h + " ; i : " + i );
                for ( int j = i; j >= h && less( a[ j ], a[ j - h ] ); j -= h ) {
                    // DEBUG
                    StdOut.println( "DEBUG: h : " + h + " ; i : " + i + " ; j : " + j );
                    StdOut.println( "DEBUG: h : " + h + " ; Exchanging { " + j + " : " + a[ j ] + " | " + ( j - h ) + " : " + a[ j - h ] + " }" );
                    StdOut.println( "DEBUG: h : " + h + " ; Array Content: " + toString( a ) + "\n" );
                    // END OF DEBUG

                    exchange( a, j, j-h );
                }
            }
            h /= 3;
        }
    }

    public static String toString( Comparable[] a ) {
        String rv = "{ ";

        for ( int i = 0; i < a.length; ++i ) {
            rv += " | " + i + " : " + a[ i ] + " | ";
        }

        rv += " }";
        return rv;
    }

    public static void main( String[] args ) {
        Integer[] intArr = { 8, 6, 4, 2, 0, 1, 3, 5, 7, 9 };

        sort( intArr );
        assert isSorted( intArr );

        StdOut.println( "DEBUG: " + java.util.Arrays.toString( intArr ) );
    }
}
