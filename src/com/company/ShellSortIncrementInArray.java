package com.company;
import edu.princeton.cs.algs4.*;

public class ShellSortIncrementInArray {

    public static boolean isSorted( Comparable[] a ) {
        for ( int i = 1; i < a.length; ++i ) {
            if ( less( a[ i ], a[ i - 1 ] ) ) {
                return false;
            }
        }
        return true;
    }

    public static void exchange( Comparable[] a, int i, int j ) {
        Comparable temp = a[ i ];
        a[ i ] = a[ j ];
        a[ j ] = temp;
    }

    public static boolean less( Comparable v, Comparable w ) {
        return v.compareTo( w ) < 0;
    }

    public static void sort( Comparable[] a ) {
        int h = 0;
        int[] incArray = new int[ a.length / 3 - 1 ];
        int incArrayIdx = 0;
        while ( h < a.length / 3 ) {
            h = h * 3 + 1;
            incArray[ incArrayIdx++ ] = h;
        }

        for ( int i = incArray.length - 1; i >= 0; --i ) {
            for ( int j = incArray[ i ]; j < a.length; ++j ) {
                for ( int k = j; k >= incArray[ i ]; k -= incArray[ i ] ) {
                    if ( less( a[ k ], a[ k - incArray[ i ] ] ) ) {
                        exchange( a, k, k - incArray[ i ] );
                    }
                }
            }
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
        StdOut.println( "DEBUG: " + toString( intArr ) );
    }
}
