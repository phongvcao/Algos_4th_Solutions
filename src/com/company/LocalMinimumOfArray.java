package com.company;
import edu.princeton.cs.algs4.*;
import java.util.Arrays;

public class LocalMinimumOfArray {

    public static int localMinimumOfArray( int[] intArr ) {
        int low = 0;
        int high = intArr.length - 1;

        // DEBUG
        int debugCount = 0;
        // END OF DEBUG

        while ( low < high ) {
            int mid = ( low + high ) / 2;

            // DEBUG
            if ( debugCount < 10 ) {
                StdOut.println( "DEBUG: low: " + low + "; mid: " + mid + "; high: " + high );
                StdOut.println( "DEBUG: lowEle: " + intArr[ low ] + "; midEle: " + intArr[ mid ] + "; highEle: " + intArr[ high ] );
                StdOut.println( "DEBUG: intArr: " + Arrays.toString( intArr ) );
                StdOut.println( "==========================================================" );
            }
            ++debugCount;
            // END OF DEBUG

            if ( ( intArr[ mid - 1 ] < intArr[ mid ] ) && ( intArr[ mid ] < intArr[ mid + 1 ] ) ) {
                return mid;
            } else {
                if ( intArr[ mid - 1 ] < intArr[ mid ] ) {
                    high = mid;
                } else if ( intArr[ mid + 1 ] < intArr[ mid ] ) {
                    low = mid;
                } else {
                    low = mid;
                }
            }
        }
        return -1;
    }

    public static void main( String[] args ) {
        int[] intArr = { 10, -9, 20, 25, 21, 40, 50, -20 };

        StdOut.println( "DEBUG: " + localMinimumOfArray( intArr ) );
    }
}
