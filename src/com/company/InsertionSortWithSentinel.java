package com.company;
import edu.princeton.cs.algs4.*;

public class InsertionSortWithSentinel {

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
        for ( int i = 1; i < a.length; ++i ) {
            for ( int j = i; j > 0; --j ) {
                if ( less( a[ j ], a[ j - 1 ] ) ) {
                    exchange( a, j, j - 1 );
                }
            }
        }
    }

    public static void sortWithSentinel( Comparable[] a ) {
        for ( int i = 0; i < a.length; ++i ) {
            if ( less( a[ i ], a[ 0 ] ) ) {
                exchange( a, i, 0 );
            }
        }

        for ( int i = 1; i < a.length; ++i ) {
            int j = i;

            while ( less( a[ j ], a[ j - 1] ) ) {
                exchange( a, j, j -1 );
                --j;
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
        Integer[] intArr = { 12, 10, 8, 6, 4, 2, 0, 1, 3, 5, 7, 9, 11 };

        // sort( intArr );
        sortWithSentinel( intArr );
        isSorted( intArr );
        StdOut.println( "DEBUG: " + toString( intArr ) );
    }
}
