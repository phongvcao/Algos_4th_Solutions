package com.company;
import edu.princeton.cs.algs4.*;

public class PrintTwoSortedArrays {

    public static void main( String[] args ) {
        int[] intArr1 = { 0, 4, 8, 12, 16, 20 };
        int[] intArr2 = { 1, 3, 5, 7, 9, 11, 16, 20 };

        int intArr1Idx = 0;
        int intArr2Idx = 0;

        String output = "DEBUG: ";
        while ( ( intArr1Idx < intArr1.length ) && ( intArr2Idx < intArr2.length ) ) {
            if ( intArr1[ intArr1Idx ] <= intArr2[ intArr2Idx ] ) {
                output += "" + intArr1[ intArr1Idx++ ] + ", ";
            } else {
                output += "" + intArr2[ intArr2Idx++ ] + ", ";
            }
        }

        if ( intArr1Idx == intArr1.length ) {
            for ( int i = intArr2Idx; i < intArr2.length; ++i ) {
                output += "" + intArr2[ i ] + ", ";
            }
        }

        if ( intArr2Idx == intArr2.length ) {
            for ( int i = intArr1Idx; i < intArr1.length; ++i ) {
                output += "" + intArr1[ i ] + ", ";
            }
        }

        StdOut.println( output );
    }
}
