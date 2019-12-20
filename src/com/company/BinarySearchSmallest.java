package com.company;
import java.util.Arrays;
import edu.princeton.cs.algs4.*;

public class BinarySearchSmallest {

    private class Element {
        int item = 0;
        int index = -1;
    }

    public int compareElement( Element ele1, Element ele2 ) {
        if ( ele1.item < ele2.item ) {
            return -1;
        } else if ( ele1.item > ele2.item ) {
            return 1;
        } else {
            if ( ele1.index < ele2.index ) {
                return -1;
            } else if ( ele1.index > ele2.index ) {
                return 1;
            } else {
                return 0;
            }
        }
    }

    public void quickSort( Element[] arr, int first, int last ) {
        int left = first;
        int right = last;

        Element pivot = arr[ ( left + right ) / 2 ];

        if ( first >= last ) return;

        do {
            while ( compareElement( arr[ left ], pivot ) == -1 ) ++left;
            while ( compareElement( arr[ right ], pivot ) == 1 ) --right;

            if ( left <= right ) {
                Element tempEle = arr[ left ];
                arr[ left ] = arr[ right ];
                arr[ right ] = tempEle;

                ++left;
                --right;
            }
        } while ( left <= right );

        quickSort( arr, first, right );
        quickSort( arr, left, last );
    }

    public int binarySearchSmallestIndex( int item, Element[] arr ) {
        int rv = -1;
        quickSort( arr, 0, arr.length - 1 );

        // DEBUG
        for ( int i = 0; i < arr.length; ++i ) {
            StdOut.println( "DEBUG: Element[]: index: " + arr[ i ].index + "; i: " + i + ": item: " + arr[ i ].item );
        }
        // END OF DEBUG

        int midEleIndex = ( arr.length - 1 ) / 2;
        Element midEle = arr[ midEleIndex ];
        Element[] foundEle = new Element[ arr.length ];
        int foundEleIndex = 0;

        StdOut.println( "DEBUG: midEleIndex: " + midEleIndex );
        StdOut.println( "DEBUG: midEle: " + midEle );

        while ( true ) {
            if ( item < midEle.item ) {
                midEleIndex = midEleIndex / 2;
                midEle = arr[ midEleIndex ];
            } else if ( item > midEle.item ) {
                midEleIndex = ( midEleIndex + arr.length ) / 2;
                midEle = arr[ midEleIndex ];
            } else {
                foundEle[ foundEleIndex++ ] = midEle;

                StdOut.println( "DEBUG: FOUND ( 0 ) at index: " + midEle.index + "; value: " + arr[ midEleIndex ].item );
                // break;
            }

            StdOut.println( "DEBUG: midEleIndex: " + midEleIndex );
            StdOut.println( "DEBUG: midEle: " + midEle );

            if ( midEleIndex == 0 ) {
                break;
            } else if ( ( midEleIndex == midEleIndex / 2 ) || ( midEleIndex == ( midEleIndex + arr.length ) / 2 ) ) {
                StdOut.println( "DEBUG: FOUND ( 0.1 ) at index: " + midEle.index + "; value: " + arr[ midEleIndex ].item );
                // break;
            } else {
                StdOut.println( "DEBUG: FOUND ( 0.2 ) at index: " + midEle.index + "; value: " + arr[ midEleIndex ].item );
                midEleIndex = midEleIndex / 2;
                midEle = arr[ midEleIndex ];
            }


            /* if ( ( midEleIndex == midEleIndex / 2 ) || ( midEleIndex == ( midEleIndex + arr.length ) / 2 ) ) {

                if ( item == midEle.item ) {
                    rv = midEle.index;
                    StdOut.println( "DEBUG: FOUND ( 1 ) at index: " + midEle.index + "; value: " + midEle.item );
                }

                break;
            } */
        }

        int minFoundEleIndex = -1;
        for ( int i = 0; i < foundEleIndex; ++i ) {
            // StdOut.println( "DEBUG: foundEleIndex: " + foundEle[ i ].index + "; i: " + i );
            if ( ( foundEle[ i ].index < minFoundEleIndex ) || ( minFoundEleIndex == -1 ) ) {
                minFoundEleIndex = foundEle[ i ].index;
            }
        }

        if ( minFoundEleIndex != -1 ) {
            rv = minFoundEleIndex;
        }

        return rv;
    }

    public Element[] constructElementArray( int[] intArr ) {
        Element[] eleArr = new Element[ intArr.length ];

        for ( int i = 0; i < intArr.length; ++i ) {
            eleArr[ i ] = new Element();
            eleArr[ i ].index = i;
            eleArr[ i ].item = intArr[ i ];

            StdOut.println( "DEBUG: index: " + i + "; value: " + intArr[ i ] );
        }

        return eleArr;
    }

    public static void main( String[] args ) {
        int[] intArr = { 0, 1, 2, 3, 0, 4, 5, 6, 7, 8, 0, 0, 0, 0, 9 };

        BinarySearchSmallest binarySearch = new BinarySearchSmallest();

        StdOut.println( "DEBUG: " + binarySearch.binarySearchSmallestIndex( 0, binarySearch.constructElementArray( intArr ) ) );
    }
}
