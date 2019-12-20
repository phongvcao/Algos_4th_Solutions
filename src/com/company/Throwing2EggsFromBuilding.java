package com.company;
import edu.princeton.cs.algs4.*;
import java.lang.Math;

public class Throwing2EggsFromBuilding {

    public static int findFloor2SqrtN( int[] intArr ) {
        int step = (int)Math.sqrt( intArr.length );
        int index = 0;

        while ( index < intArr.length ) {
            if ( intArr[ index ] == 1 ) {
                break;
            }
            index += step;
        }

        for ( int i = index - step; i < index; ++i ) {
            if ( intArr[ i ] == 1 ) {
                return i;
            }
        }

        return -1;
    }

    public static int findFloorCSqrtF( int[] intArr ) {
        int step = 1;
        int count = 1;
        int index = 0;

        while ( index < intArr.length ) {
            if ( intArr[ step ] == 1 ) {
                break;
            }

            ++count;
            step += count;
        }

        StdOut.println( "DEBUG: step: " + step + "; count: " + count );

        for ( int i = step - count; i < step + 1; ++i ) {
            if ( intArr[ i ] == 1 ) {
                return i;
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
        // StdOut.println( "DEBUG: " + findFloor2SqrtN( intArr ) );
        StdOut.println( "DEBUG: " + findFloorCSqrtF( intArr ) );
    }
}
