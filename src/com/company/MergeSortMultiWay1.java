package com.company;
import edu.princeton.cs.algs4.*;
import java.util.ArrayList;

public class MergeSortMultiWay1 {

    private static class Separator {
        public int index = -1;
        public int low = -1;
        public int high = -1;
        public int mid = -1;

        public boolean isOutOfBound() {
            return index > high;
        }
    }

    public static boolean less( Comparable a, Comparable b ) {
        return a.compareTo( b ) == -1;
    }

    public static void sort( Comparable[] a, int way ) {
        Comparable[] aux = new Comparable[ a.length ];
        sort( a, aux, way, 0, a.length - 1 );
    }

    public static void sort( Comparable[] a, Comparable[] aux, int way, int low, int high ) {
        if ( low >= high ) return;
        // if ( high - low < way ) return;

        // Divide a into chunks
        // If high - low + 1 is too small to divide into "way" arrays (high - low + 1 <= way )
        // Loop through high - low + 1 elements from low to high to construct separators of size 1 each.
        // Then call merge on this one.
        // Otherwise, if high - low + 1 > way, keep dividing the array further (call sort())
        //
        // When does the divide stop?

        // Divide a into chunks
        int chunkSize = ( high - low + 1 ) / way;
        int separatorsCount = chunkSize > 1 ? way : high - low + 1;
        ArrayList< Separator > separators = new ArrayList< Separator >();
        int separatorsIdx = 0;
        if ( chunkSize > 0 ) {
            for ( int i = 0; i < separatorsCount; ++i ) {
                Separator sep = new Separator();
                sep.index = low + i * chunkSize;
                sep.low = low + i * chunkSize;
                sep.high = i == way - 1 ? high : low + ( i + 1 ) * chunkSize - 1;
                separators.add( i, sep );
                ++separatorsIdx;
            }
        } else {
            for ( int i = 0; i < separatorsCount; ++i ) {
                Separator sep = new Separator();
                sep.index = low + i;
                sep.low = low + i;
                sep.high = sep.index;
                separators.add( i, sep );
                ++separatorsIdx;
            }
        }

        // Recursively sort each chunk
        for ( int i = 0; i < separatorsCount; ++i ) {
            sort( a, aux, way, separators.get( i ).low, separators.get( i ).high );
        }

        // DEBUG
        for ( int i = 0; i < separators.size(); ++i ) {
            StdOut.println( "DEBUG: separators: size: " + separators.size() + " ; index: " + separators.get( i ).index +
                    " ; low: " + separators.get( i ).low + " ; high: " + separators.get( i ).high +
                    " ; mid: " + separators.get( i ).mid + " ; chunkSize: " + chunkSize +
                    " ; separatorsCount: " + separatorsCount + " ; LOW: " + low + " ; HIGH: " + high );
        }
        // END OF DEBUG

        // Now merge all ways (separators) into 1 array
        merge( a, aux, separators );
    }

    public static Separator getMinSeparator( Comparable[] a, ArrayList< Separator > separators ) {
        Separator sep = null;
        for ( int i = 0; i < separators.size(); ++i ) {
            if ( ! separators.get( i ).isOutOfBound() ) {
                if ( ( sep == null ) || ( less( a[ separators.get( i ).index ], a[ sep.index ] ) ) ) {
                    sep = separators.get( i );
                }
            }
        }
        return sep;
    }

    public static void merge( Comparable[] a, Comparable[] aux, ArrayList< Separator > separators ) {
        // First copy all eles from index separators[ 0 ].low to separators[ separators.length - 1 ].high
        // from a to aux
        for ( int i = separators.get( 0 ).index; i <= separators.get( separators.size() - 1 ).high; ++i ) {
            aux[ i ] = a[ i ];
        }

        // Now invoking a function that chooses the Separator among all separators[] that has minimum element
        // We do this by looping thru separators, examine separators[ i ].index & find the smallest
        // aux[ separators[ i ].index ]. Note that separators[ i ].isOutOfBound() must be false
        // We also increment that separators[ i ].index by 1.
        //
        // We keep doing this until there's only 1 valid separator left ( separators[ i ].isOutOfBound() == false )
        // If so, copy the rest of the elements to a[]

        Separator minSep = null;
        int index = separators.get( 0 ).low;
        int orgIndex = index;
        do {
            minSep = getMinSeparator( aux, separators );

            if ( minSep == null ) break;

            // DEBUG
            StdOut.println( "DEBUG: SELECTED Ele: " + aux[ minSep.index ] );
            // END OF DEBUG

            a[ index++ ] = aux[ minSep.index++ ];

            // ++minSep.index;
        } while ( minSep != null );

        // DEBUG
        String str = "";
        for ( int i = orgIndex; i < index; ++i ) {
            str += a[ i ] + ", ";
        }
        StdOut.println( "DEBUG: Sorted: " + str );
        // END OF DEBUG
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
