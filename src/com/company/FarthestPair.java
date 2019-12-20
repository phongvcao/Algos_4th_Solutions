package com.company;
import java.util.Arrays;
import edu.princeton.cs.algs4.*;

public class FarthestPair {

    public static double[] findFarthestPair( double[] doubleArr ) {
        double[] farthestPair = new double[ 2 ];
        Arrays.fill( farthestPair, -1 );

        double maxDistance = -1;
        Arrays.sort( doubleArr );

        farthestPair[ 0 ] = doubleArr[ 0 ];
        farthestPair[ 1 ] = doubleArr[ doubleArr.length - 1 ];

        return farthestPair;
    }

    public static void main( String[] args ) {
        double[] doubleArr = { -5, -2, 4, 6, 10, 11 };
        double[] closestPair = findFarthestPair( doubleArr );
        StdOut.println( "DEBUG: " + closestPair[ 0 ] + ", " + closestPair[ 1 ] );
    }
}
