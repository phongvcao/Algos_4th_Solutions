package com.company;
import edu.princeton.cs.algs4.*;
import java.lang.Math;

public class HotOrCold {

    public static int VALUE = 40;
    public static int N = 100;

    public static int binarySearch( int[] intArr, int value, int low, int high ) {
        int left = low;
        int right = high;

        while ( left < right ) {
            int mid = ( left + right ) / 2;
            if ( intArr[ mid ] == value ) {
                return mid;
            } else if ( intArr[ mid ] < value ) {
                left = mid;
            } else {
                right = mid;
            }
        }
        return -1;
    }

    public static boolean isHot( int currentGuess, int lastGuess ) {
        if ( Math.abs( VALUE - currentGuess ) > Math.abs( VALUE - lastGuess ) ) {
            return false;
        } else {
            return true;
        }
    }

    public static int guessSecret2LogN( int[] intArr, int low, int high ) {
        int mid = ( low + high ) / 2;
        if ( VALUE == intArr[ mid ] ) {
            return mid;
        }

        if ( isHot( intArr[ low ], intArr[ high ] ) ) {
            // VALUE is on the left
            return guessSecret2LogN( intArr, low, mid );
        } else {
            // VALUE is on the right
            return guessSecret2LogN( intArr, mid, high );
        }
    }

    public static void main( String[] args ) {
        // DEBUG
        /* int[] intArr = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        StdOut.println( "DEBUG: " + binarySearch( intArr, 3, 0, intArr.length - 1 ) ); */
        // END OF DEBUG

        int[] intArr = new int[ N ];
        for ( int i = 0; i < N; ++i ) {
            intArr[ i ] = i + 1;
        }

        StdOut.println( "DEBUG: " + guessSecret2LogN( intArr, 0, intArr.length - 1 ) );
    }
}
