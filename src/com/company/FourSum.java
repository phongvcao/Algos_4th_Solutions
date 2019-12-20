package com.company;
import edu.princeton.cs.algs4.*;
import java.util.Arrays;

public class FourSum {

    public static int fourSumFast( int[] arr ) {
        Arrays.sort( arr );
        int N = arr.length;
        int count = 0;
        for ( int i = 0; i < N; ++i ) {
            for ( int j = i + 1; j < N; ++j ) {
                for ( int k = j + 1; k < N; ++k ) {
                    if ( binarySearch( arr, - arr[ i ] - arr[ j ] - arr[ k ] ) > k ) {
                        ++count;
                    }
                }
            }
        }

        return count;
    }

    public static int binarySearch( int[] arr, int value ) {
        // Search for value in sorted array arr
        int low = 0;
        int high = arr.length - 1;

        while ( low < high ) {

            StdOut.println( "DEBUG: low: " + low + "; high: " + high );

            int mid = ( low + high ) / 2;
            if ( value < arr[ mid ] ) high = mid - 1;
            else if ( value > arr[ mid ] ) low = mid + 1;
            else return mid;
        }

        return -1;
    }

    public static void main( String[] args ) {
        int[] intArr = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, -1, -2 };

        StdOut.println( "DEBUG: " + fourSumFast( intArr ) );
    }
}
