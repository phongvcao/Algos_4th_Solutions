package com.company;
import edu.princeton.cs.algs4.*;

public class BinarySearchAddSubtractOnly {

    public static int binarySearchFibonacci( int[] intArr, int value ) {
        int aux;
        int fibonacciBeforeN = 0;
        int fibonacciN = 1;

        // Compute F(k)
        while ( fibonacciN < intArr.length - 1 ) {
            aux = fibonacciN;
            fibonacciN = fibonacciBeforeN + fibonacciN;
            fibonacciBeforeN = aux;
        }

        int low = 0;
        int high = low + fibonacciN;

        while ( low <= high ) {
            // Compute F( k - 2 )
            aux = fibonacciBeforeN;
            fibonacciBeforeN = fibonacciN - fibonacciBeforeN; // F( k - 2 )
            fibonacciN = aux; // F( k -1 )

            int elementToCheck = low + fibonacciBeforeN;

            if ( intArr[ elementToCheck ] == value ) {
                return elementToCheck;
            } else if ( intArr[ elementToCheck ] < value ) {
                low = fibonacciBeforeN;
            } else {
                high = fibonacciBeforeN;
            }
        }

        return -1;
    }

    public static void main( String[] args ) {
        int[] intArr = { 1, 3, 5, 7, 9, 10, 12, 14, 16, 18 };

        StdOut.println( "DEBUG: " + binarySearchFibonacci( intArr, 10 ) );
        StdOut.println( "DEBUG: " + binarySearchFibonacci( intArr, 11 ) );
        StdOut.println( "DEBUG: " + binarySearchFibonacci( intArr, 16 ) );
    }
}
