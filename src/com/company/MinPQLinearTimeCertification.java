package com.company;
import edu.princeton.cs.algs4.*;

public class MinPQLinearTimeCertification {

    public static boolean isMinOrientedHeap( Comparable[] a ) {
        for ( int i = a.length - 1; i > 0; --i ) {
            if ( a[ i ].compareTo( a[ i / 2 ] ) < 0 ) {
                return false;
            }
        }
        return true;
    }

    public static void main( String[] args ) {
        // Integer[] intArr = { 14, 12, 10, 8, 6, 4, 2, 0, 1, 3, 5, 7, 9, 11, 13 };
        // Integer[] intArr = {0, 0, 1, 2, 3, 4, 5, 6, 7, 8};
        Integer[] intArr = {0, 0, 1, 2, -1, -5, 99, 6, 7, 8};

        if ( isMinOrientedHeap( intArr ) ) {
            StdOut.println( "DEBUG: intArr (isMinOrientedHeap): TRUE!!!" );
        } else {
            StdOut.println( "DEBUG: intArr (isMinOrientedHeap): FALSE!!!" );
        }
    }
}
