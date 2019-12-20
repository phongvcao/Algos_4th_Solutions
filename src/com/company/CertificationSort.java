package com.company;
import edu.princeton.cs.algs4.*;
import java.util.*;

public class CertificationSort {

    public static boolean check( Comparable[] a ) {
        HashMap< Comparable, Integer > eleCountMap = new HashMap< Comparable, Integer >();
        for ( int i = 0; i < a.length; ++i ) {
            if ( eleCountMap.containsKey( a[ i ] ) ) {
                eleCountMap.put( a[ i ], eleCountMap.get( a[ i ] ) + 1 );
            } else {
                eleCountMap.put( a[ i ], 1 );
            }
        }

        Arrays.sort( a );

        if ( ! isSorted( a ) ) return false;

        for ( int i = 0; i < a.length; ++i ) {
            if ( eleCountMap.get( a[ i ] ) == 0 ) {
                return false;
            } else {
                eleCountMap.put( a[ i ], eleCountMap.get( a[ i ] ) - 1 );
            }
        }

        return true;
    }

    public static boolean isSorted( Comparable[] a ) {
        for ( int i = 1; i < a.length; ++i ) {
            if ( less( a[ i ], a[ i - 1 ] ) ) {
                return false;
            }
        }
        return true;
    }

    public static boolean less( Comparable v, Comparable w ) {
        return v.compareTo( w ) < 0;
    }

    public static void main( String[] args ) {
        Integer[] intArr = { 12, 10, 8, 6, 4, 2, 0, 1, 3, 5, 7, 9, 9, 9 };

        StdOut.println( "DEBUG: " + check( intArr ) );
    }
}
