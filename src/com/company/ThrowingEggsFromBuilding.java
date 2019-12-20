package com.company;
import edu.princeton.cs.algs4.*;

public class ThrowingEggsFromBuilding {

    public static int findFloor2LogN( int[] intArr ) {
        int low = 0;
        int high = intArr.length - 1;

        // while ( low + 1 < high ) {
        while ( low < high ) {
            int mid = ( low + high ) / 2;

            if ( intArr[ mid ] + intArr[ mid + 1 ] == 1 ) {
                return intArr[ mid ] == 0 ? mid + 1 : mid;
            } else if ( intArr[ mid ] + intArr[ mid + 1 ] == 0 ) {
                // Recurse to the right
                low = mid;
            } else {
                // Recurse to the left
                high = mid;
            }
        }

        return -1;
    }

    public static int findFloor2LogF( int[] intArr ) {
        int low = 0;
        int high = intArr.length - 1;
        int step = 1;

        int index = low;
        while ( index < high ) {
            if ( intArr[ index ] == 1 ) {
                high = index;
                low += step / 2;
                break;
            }

            step *= 2;
            index = low + step;
        }

        StdOut.println( "DEBUG: low: " + low + "; high: " + high );

        while ( low < high ) {
            int mid = ( low + high ) / 2;

            if ( intArr[ mid ] + intArr[ mid + 1 ] == 1 ) {
                return intArr[ mid ] == 0 ? mid + 1 : mid;
            } else if ( intArr[ mid ] + intArr[ mid + 1 ] == 0 ) {
                // Recurse to the right
                low = mid;
            } else {
                // Recurse to the left
                high = mid;
            }
        }

        return -1;
    }

    public static void main( String[] args ) {
        int N = 300;
        int F = 10;
        int[] intArr = new int[ N ];

        for ( int i = 0; i < F; ++i ) {
            intArr[ i ] = 0;
        }

        for ( int i = F; i < N; ++i ) {
            intArr[ i ] = 1;
        }

        // StdOut.println( "DEBUG: " + findFloor2LogN( intArr ) );
        StdOut.println( "DEBUG: " + findFloor2LogF( intArr ) );
    }
}
