package com.company;
import java.util.Arrays;
import edu.princeton.cs.algs4.*;

public class FasterTwoSumAndThreeSum {

    public static int fasterTwoSum( int[] intArr ) {
        int count = 0;
        Arrays.sort( intArr );

        if ( ( intArr[ intArr.length - 1 ] < 0 ) || ( intArr[ 0 ] > 0 ) ) return 0;

        int negIdx = 0;
        int posIdx = 0;
        for ( int i = 0; i < intArr.length; ++i ) {
            if ( intArr[ i ] > -1 ) {
                posIdx = i;
                negIdx = i - 1;
                break;
            }
        }

        while ( ( negIdx >= 0 ) && ( posIdx < intArr.length ) ) {
            if ( - intArr[ negIdx ] < intArr[ posIdx ] ) {
                --negIdx;
            } else if ( - intArr[ negIdx ] > intArr[ posIdx ] ) {
                ++posIdx;
            } else {
                ++count;

                int tempIdx = negIdx - 1;
                while ( ( tempIdx >= 0 ) && ( intArr[ negIdx ] + intArr[ posIdx ] == 0 ) ) {
                    ++count;
                    --negIdx;
                }

                tempIdx = posIdx + 1;
                while ( ( tempIdx < intArr.length ) && ( intArr[ negIdx ] + intArr[ posIdx ] == 0 ) ) {
                    ++count;
                    ++posIdx;
                }

                --negIdx;
                ++posIdx;
            }
        }
        return count;
    }

    public static int fasterThreeSum( int[] intArr ) {
        int count = 0;
        Arrays.sort( intArr );

        if ( ( intArr[ intArr.length - 1 ] < 0 ) || ( intArr[ 0 ] > 0 ) ) return 0;

        for ( int i = 0; i < intArr.length; ++i ) {
            int startIdx = 0;
            int endIdx = intArr.length - 1;

            while ( startIdx < endIdx ) {
                if ( intArr[ i ] + intArr[ startIdx ] + intArr[ endIdx ] > 0 ) {
                    --endIdx;
                } else if ( intArr[ i ] + intArr[ startIdx ] + intArr[ endIdx ] < 0 ) {
                    ++startIdx;
                } else {
                    ++count;

                    StdOut.println( "DEBUG: " + intArr[ i ] + ", " + intArr[ startIdx ] + ", " + intArr[ endIdx ] );

                    int tempIdx = startIdx + 1;
                    while ( ( tempIdx < intArr.length ) && ( intArr[ tempIdx ] + intArr[ i ] + intArr[ endIdx ] == 0 ) ) {
                        ++count;
                        ++tempIdx;
                    }

                    tempIdx = endIdx - 1;
                    while ( ( tempIdx > startIdx ) && ( intArr[ tempIdx ] + intArr[ i ] + intArr[ startIdx ] == 0 ) ) {
                        ++count;
                        --tempIdx;
                    }

                    ++startIdx;
                    --endIdx;
                }
            }
        }

        return count;
    }

    public static void main( String[] args ) {
        int[] intArr = { 0, 1, 2, -1, -2, -3 };

        StdOut.println( "DEBUG: " + fasterTwoSum( intArr ) );
        StdOut.println( "DEBUG: " + fasterThreeSum( intArr ) );
    }
}
