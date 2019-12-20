package com.company;
import edu.princeton.cs.algs4.*;

public class MergeSortMultiWay {

    public static boolean less( Comparable a, Comparable b ) {
        return a.compareTo( b ) == -1;
    }

    public static void sort( Comparable[] a, int way ) {
        Comparable[] aux = new Comparable[ a.length ];
        sort( a, aux, way, 0, a.length - 1 );
    }

    public static void sort( Comparable[] a, Comparable[] aux, int way, int low, int high ) {
        if ( low >= high ) return;
        // Divide a into chunks
        int chunkSize = a.length / way;
        int[] separator = new int[ way + 1 ];
        int separatorIdx = 0;
        for ( int i = 0; i < way; ++i ) {
            separator[ separatorIdx++ ] = low + i * chunkSize;
        }

        separator[ separatorIdx++ ] = high;

        for ( int i = 0; i < separator.length - 1; ++i ) {
            sort( a, aux, way, separator[ i ], separator[ i + 1 ] );
        }

        merge( a, aux, separator );

        StdOut.println( "DEBUG: separator: " + java.util.Arrays.toString( separator ) );
        /* for ( int i = 0; i <= way; ++i ) {
            int chunkLow = low + i * chunkSize + 1;
            int chunkHigh = i == way ? high : low + ( i + 1 ) * chunkSize;
            int chunkMid = ( chunk )
        } */
    }

    public static void merge( Comparable[] a, Comparable[] aux, int[] separator ) {
        for ( int k = separator[ 0 ]; k <= separator[ separator.length - 1 ]; ++k ) {
            aux[ k ] = a[ k ];
        }

        int[] separatorIndexes = new int[ separator.length - 1 ];
        System.arraycopy( separator, 0, separatorIndexes, 0, separator.length - 1 );

        int[] validSeparators = new int[ separator.length - 1 ];
        System.arraycopy( separator, 0, separatorIndexes, 0, separator.length - 1 );

        for ( int k = separator[ 0 ]; k <= separator[ separator.length - 1 ]; ++k ) {
            boolean isValidSeparators = true;
            for ( int l = 0; l < separator.length - 1; ++l ) {
                // Check to see if more than 2 separators are active
                // If less than 2 separators are active, get out of the loop
                int validSeparatorsCount = 0;
                for ( int m = 0; m < validSeparators.length; ++m ) {
                    if ( validSeparators[ m ] != -1 ) {
                        ++validSeparatorsCount;
                    }
                }
                if ( validSeparatorsCount <= 1 ) {
                    isValidSeparators = false;
                    break;
                }
                // END OF Check to see if more than 2 separators are active

                if ( separatorIndexes[ l ] > separatorIndexes[ l + 1 ] ) {
                    validSeparators[ l ] = -1;
                }

            }

            if ( ! isValidSeparators ) break;
        }
    }

    public static void main( String[] args ) {
        Integer[] intArr = {
                14, 12, 10,  8,  6,  4,  2,  0,  1,  3,  5,  7,  9, 11, 13,
                34, 32, 30, 28, 26, 24, 22, 20, 21, 23, 25, 27, 29, 31, 33,
                54, 52, 50, 48, 46, 44, 42, 40, 41, 43, 45, 47, 49, 51, 53,
                74, 72, 70, 68, 66, 64, 62, 60, 61, 63, 65, 67, 69, 71, 73,
                94, 92, 90, 88, 86, 84, 82, 80, 81, 83, 85, 87, 89, 91, 93,
        };

        StdOut.println( "DEBUG: intArr (BEFORE): " + java.util.Arrays.toString( intArr ) );

        sort( intArr, 5 );

        StdOut.println( "DEBUG: intArr (AFTER): " + java.util.Arrays.toString( intArr ) );
    }
}
