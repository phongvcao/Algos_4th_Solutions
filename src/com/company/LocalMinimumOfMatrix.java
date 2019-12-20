package com.company;
import edu.princeton.cs.algs4.*;
import java.util.Arrays.*;

public class LocalMinimumOfMatrix {

    // public static int

    public static int[] smallestCloseByEle( int[][] intArr, int rowIdx, int colIdx ) {
        int[][] surroundedEles = {
                { rowIdx - 1, colIdx },
                { rowIdx + 1, colIdx },
                { rowIdx, colIdx - 1 },
                { rowIdx, colIdx + 1 },
        };

        int[] smallestEleIdx = { -1, -1 };
        for ( int i = 0; i < surroundedEles.length; ++i ) {
            if ( ( smallestEleIdx[ 0 ] == -1 ) || ( intArr[ smallestEleIdx[ 0 ] ][ smallestEleIdx[ 1 ] ] > intArr[ surroundedEles[ i ][ 0 ] ][ surroundedEles[ i ][ 1 ] ] ) ) {
                smallestEleIdx[ 0 ] = surroundedEles[ i ][ 0 ];
                smallestEleIdx[ 1 ] = surroundedEles[ i ][ 1 ];
            }
        }

        return smallestEleIdx;
    }

    public static boolean isLocalMinimum( int[][] intArr, int rowIdx, int colIdx ) {
        if ( rowIdx + 1 < intArr.length ) {
            if ( intArr[ rowIdx ][ colIdx ] >= intArr[ rowIdx + 1 ][ colIdx ] ) {
                return false;
            }
        }

        if ( colIdx + 1 < intArr.length ) {
            if ( intArr[ rowIdx ][ colIdx ] >= intArr[ rowIdx ][ colIdx + 1 ] ) {
                return false;
            }
        }

        if ( rowIdx - 1 > 0 ) {
            if ( intArr[ rowIdx ][ colIdx ] >= intArr[ rowIdx - 1 ][ colIdx ] ) {
                return false;
            }
        }

        if ( colIdx - 1 > 0 ) {
            if ( intArr[ rowIdx ][ colIdx ] >= intArr[ rowIdx ][ colIdx - 1 ] ) {
                return false;
            }
        }

        return true;
    }

    public static int[] localMinimumMatrix( int[][] intArr ) {
        int[] localMinIdx = { -1, -1 };

        // Find minimum element in midRow/midCol
        int quadrantRowLowIdx = 0;
        int quadrantRowHighIdx = intArr.length;
        int quadrantColLowIdx = 0;
        int quadrantColHighIdx = intArr.length;

        while ( ( quadrantRowLowIdx < quadrantRowHighIdx ) && ( quadrantColLowIdx < quadrantColHighIdx ) ) {
            int midRowIdx = ( quadrantRowLowIdx + quadrantRowHighIdx ) / 2;
            int midColIdx = ( quadrantColLowIdx + quadrantColHighIdx ) / 2;

            int[] currentMinEleIdx = { -1, -1 };
            int[] middleMinEleIdx = { -1, -1 };

            for ( int i = quadrantRowLowIdx; i < quadrantRowHighIdx; ++i ) {
                if ( ( middleMinEleIdx[ 0 ] == -1 ) ||
                        ( intArr[ midRowIdx ][ i ] < intArr[ middleMinEleIdx[ 0 ] ][ middleMinEleIdx[ 1 ] ] ) ) {
                    middleMinEleIdx[ 0 ] = midRowIdx;
                    middleMinEleIdx[ 1 ] = i;
                }
            }

            for ( int i = quadrantColLowIdx; i < quadrantColHighIdx; ++i ) {
                if ( ( middleMinEleIdx[ 0 ] == -1 ) ||
                        ( intArr[ i ][ midColIdx ] < intArr[ middleMinEleIdx[ 0 ] ][ middleMinEleIdx[ 1 ] ] ) ) {
                    middleMinEleIdx[ 0 ] = i;
                    middleMinEleIdx[ 1 ] = midColIdx;
                }
            }

            if ( currentMinEleIdx[ 0 ] != -1 ) {
                if ( intArr[ currentMinEleIdx[ 0 ] ][ currentMinEleIdx[ 1 ] ] < intArr[ middleMinEleIdx[ 0 ] ][ middleMinEleIdx[ 1 ] ] ) {
                    // Roll over to currentMinEleIdx's quadrant
                    if ( currentMinEleIdx[ 0 ] < midRowIdx ) {
                        quadrantRowHighIdx = midRowIdx;
                    } else {
                        quadrantRowLowIdx = midRowIdx;
                    }

                    if ( currentMinEleIdx[ 1 ] < midColIdx ) {
                        quadrantColHighIdx = midColIdx;
                    } else {
                        quadrantColLowIdx = midColIdx;
                    }

                } else {
                    // Examine middleMinEleIdx's quadrant

                    if ( middleMinEleIdx[ 0 ] < midRowIdx ) {
                        quadrantRowHighIdx = midRowIdx;
                    } else {
                        quadrantRowLowIdx = midRowIdx;
                    }

                    if ( middleMinEleIdx[ 1 ] < midColIdx ) {
                        quadrantColHighIdx = midColIdx;
                    } else {
                        quadrantColLowIdx = midColIdx;
                    }
                }
            } else {
                currentMinEleIdx = smallestCloseByEle( intArr, middleMinEleIdx[ 0 ], middleMinEleIdx[ 1 ] );

                if ( currentMinEleIdx[ 0 ] < midRowIdx ) {
                    quadrantRowHighIdx = midRowIdx;
                } else {
                    quadrantRowLowIdx = midRowIdx;
                }

                if ( currentMinEleIdx[ 1 ] < midColIdx ) {
                    quadrantColHighIdx = midColIdx;
                } else {
                    quadrantColLowIdx = midColIdx;
                }
            }

            // Start off from the minimum in midRow/midCol
            // Roll to that quadrant that contains minimum of midRow/midCol
            if ( isLocalMinimum( intArr, middleMinEleIdx[ 0 ], middleMinEleIdx[ 1 ] ) ) {
                localMinIdx[ 0 ] = middleMinEleIdx[ 0 ];
                localMinIdx[ 1 ] = middleMinEleIdx[ 1 ];
            }

            if ( ( currentMinEleIdx[ 0 ] != -1 ) && ( isLocalMinimum( intArr, currentMinEleIdx[ 0 ], currentMinEleIdx[ 1 ] ) ) ) {
                if ( localMinIdx[ 0 ] != -1 ) {
                    if ( intArr[ currentMinEleIdx[ 0 ] ][ currentMinEleIdx[ 1 ] ] < intArr[ localMinIdx[ 0 ] ][ localMinIdx[ 1 ] ] ) {
                        localMinIdx[ 0 ] = currentMinEleIdx[ 0 ];
                        localMinIdx[ 1 ] = currentMinEleIdx[ 1 ];
                    }
                }
            }

            if ( localMinIdx[ 0 ] != -1 ) {
                break;
            }
        }

        return localMinIdx;
    }

    public static void main( String[] args ) {
        int[][] intArr = {
                { 100, 100,  39, 100, 100,  50, 100, 100, 100, 100, 100 },
                { 100, 100,  38, 100, 100,  49, 100, 100, 100, 100, 100 },
                {  37,  36,  33,  34,  35,  48, 100, 100, 100, 100, 100 },
                { 100, 100,   1, 100,   9,  10, 100, 100, 100, 100, 100 },
                { 100, 100,  31, 100, 100,  47, 100, 100, 100, 100, 100 },
                {  46,  45,  35,  44,  43,  60,  51,  52,  53,  54,  55 },
                { 100, 100,   2, 100, 100,  56, 100, 100, 100, 100, 100 },
                { 100, 100, 100, 100, 100,  57, 100, 100, 100, 100, 100 },
                { 100, 100, 100, 100, 100,  58, 100, 100, 100, 100, 100 },
                { 100, 100, 100, 100, 100,  59, 100, 100, 100, 100, 100 },
        };

        int[] localMinIdx = localMinimumMatrix( intArr );

        StdOut.println( "DEBUG: i: " + localMinIdx[ 0 ] + "; j: " + localMinIdx[ 1 ] + "; localMin: " + intArr[ localMinIdx[ 0 ] ][ localMinIdx[ 1 ] ] );
    }
}
