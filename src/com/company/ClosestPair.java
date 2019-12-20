package com.company;
import java.util.Arrays;
import edu.princeton.cs.algs4.*;
import java.lang.Math.*;

public class ClosestPair {

    public static double[] findClosestPair( double[] doubleArr ) {
        double[] closestPair = new double[ 2 ];
        Arrays.fill( closestPair, -1 );
        double minDistance = -1;
        Arrays.sort( doubleArr );

        for ( int i = 0; i < doubleArr.length - 1; ++i ) {
            if ( ( Math.abs( doubleArr[ i ] - doubleArr[ i + 1 ] ) < minDistance ) || ( minDistance == -1 ) ) {
                minDistance = Math.abs( doubleArr[ i ] - doubleArr[ i + 1 ] );
                closestPair[ 0 ] = doubleArr[ i ];
                closestPair[ 1 ] = doubleArr[ i + 1 ];
            }
        }

        return closestPair;
    }

    public static void main( String[] args ) {
        double[] doubleArr = { -5, -2, 4, 6, 10, 11 };
        double[] closestPair = findClosestPair( doubleArr );
        StdOut.println( "DEBUG: " + closestPair[ 0 ] + ", " + closestPair[ 1 ] );
    }
}
