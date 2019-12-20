package com.company;
import edu.princeton.cs.algs4.*;
import java.util.ArrayList;

public class EightPuzzleGame {

    private static class Matrix implements Comparable< Matrix > {

        public int numMoves = 0;
        public int numWrongPos = 0;
        public int priority = 0;
        public int[][] data = null;
        public int[] blankIndex = null;

        public static int[][] sortedMatrix = {
                { 1, 2, 3 },
                { 4, 5, 6 },
                { 7, 8, 0 },
        };

        public Matrix( int[][] data, int[] blankIndex, int numMoves ) {
            this.data = data;
            this.numMoves = numMoves;
            this.numWrongPos = this.isSorted();
            this.priority = this.numMoves + this.numWrongPos;
            this.blankIndex = blankIndex;
        }

        public String toString() {
            String rv = "===================================\n";
            rv += "Priority : " + this.priority + " ; numMoves : " + this.numMoves + " ; numWrongPos : " + this.numWrongPos + "\n";
            for ( int i = 0; i < this.data.length; ++i ) {
                rv += java.util.Arrays.toString( this.data[ i ] ) + "\n";
            }
            return rv;
        }

        public int isSorted() {
            int wrongMovesCount = 0;
            for ( int i = 0; i < this.data.length; ++i ) {
                for ( int j = 0; j < this.data.length; ++j ) {
                    if ( ( this.data[ i ][ j ] != Matrix.sortedMatrix[ i ][ j ] ) && ( this.data[ i ][ j ] != 0 ) ) {
                        ++wrongMovesCount;
                    }
                }
            }
            return wrongMovesCount;
        }

        public int compareTo( Matrix other ) {
            if ( this.priority < other.priority ) {
                return -1;
            } else if ( this.priority > other.priority ) {
                return 1;
            }

            return 0;
        }

        private void exchange( int[][] movesArr, int i1, int j1, int i2, int j2 ) {
            int temp = movesArr[ i1 ][ j1 ];
            movesArr[ i1 ][ j1 ] = movesArr[ i2 ][ j2 ];
            movesArr[ i2 ][ j2 ] = temp;
        }

        private int[][] move( int x, int y ) {
            int[][] movesArr = new int[ this.data.length ][ this.data.length ];
            for ( int i = 0; i < this.data.length; ++i ) {
                for ( int j = 0; j < this.data.length; ++j ) {
                    movesArr[ i ][ j ] = this.data[ i ][ j ];
                }
            }
            exchange( movesArr, x, y, this.blankIndex[ 0 ], this.blankIndex[ 1 ] );
            return movesArr;
        }

        public boolean isDuplicate( Matrix matrix ) {
            for ( int i = 0; i < matrix.data.length; ++i ) {
                for ( int j = 0; j < matrix.data.length; ++j ) {
                    if ( this.data[ i ][ j ] != matrix.data[ i ][ j ] ) {
                        return false;
                    }
                }
            }
            return true;
        }

        public void generateMoves( MatrixMaxPQ maxPQ, Matrix prevMatrix ) {
            if ( this.blankIndex[ 0 ] > 0 ) {
                int[] newBlankIndex = { this.blankIndex[ 0 ] - 1, this.blankIndex[ 1 ] };
                Matrix newMatrix = new Matrix( move( newBlankIndex[ 0 ], newBlankIndex[ 1 ] ), newBlankIndex, this.numMoves + 1 );
                if ( ( prevMatrix == null ) || ( !newMatrix.isDuplicate( prevMatrix ) ) ) {
                    StdOut.println( "DEBUG: GENERATED MOVE: " + newMatrix.toString() + " FROM: " + prevMatrix.toString() );

                    maxPQ.insert( newMatrix );
                }
            }

            if ( this.blankIndex[ 0 ] < this.data.length - 1 ) {
                int[] newBlankIndex = { this.blankIndex[ 0 ] + 1, this.blankIndex[ 1 ] };
                Matrix newMatrix = new Matrix( move( newBlankIndex[ 0 ], newBlankIndex[ 1 ] ), newBlankIndex, this.numMoves + 1 );
                if ( ( prevMatrix == null ) || ( !newMatrix.isDuplicate( prevMatrix ) ) ) {
                    StdOut.println( "DEBUG: GENERATED MOVE: " + newMatrix.toString() + " FROM: " + prevMatrix.toString() );
                    maxPQ.insert( newMatrix );
                }
            }

            if ( this.blankIndex[ 1 ] > 0 ) {
                int[] newBlankIndex = { this.blankIndex[ 0 ], this.blankIndex[ 1 ] - 1 };
                Matrix newMatrix = new Matrix( move( newBlankIndex[ 0 ], newBlankIndex[ 1 ] ), newBlankIndex, this.numMoves + 1 );
                if ( ( prevMatrix == null ) || ( !newMatrix.isDuplicate( prevMatrix ) ) ) {
                    StdOut.println( "DEBUG: GENERATED MOVE: " + newMatrix.toString() + " FROM: " + prevMatrix.toString() );
                    maxPQ.insert( newMatrix );
                }
            }

            if ( this.blankIndex[ 1 ] < this.data.length - 1 ) {
                int[] newBlankIndex = { this.blankIndex[ 0 ], this.blankIndex[ 1 ] + 1 };
                Matrix newMatrix = new Matrix( move( newBlankIndex[ 0 ], newBlankIndex[ 1 ] ), newBlankIndex, this.numMoves + 1 );
                if ( ( prevMatrix == null ) || ( !newMatrix.isDuplicate( prevMatrix ) ) ) {
                    StdOut.println( "DEBUG: GENERATED MOVE: " + newMatrix.toString() + " FROM: " + prevMatrix.toString() );
                    maxPQ.insert( newMatrix );
                }
            }
        }
    }

    private static class MatrixMaxPQ {
        private Matrix[] pq;
        private int N = 0;

        public MatrixMaxPQ( int maxN ) {
            pq = new Matrix[ maxN + 1 ];
        }

        public String toString() {
            return java.util.Arrays.toString( pq );
        }

        public int size() {
            return N;
        }

        public boolean isEmpty() {
            return size() == 0;
        }

        private void exchange( int i, int j ) {
            Matrix temp = pq[ i ];
            pq[ i ] = pq[ j ];
            pq[ j ] = temp;
        }

        private boolean less( int i, int j ) {
            return pq[ i ].compareTo( pq[ j ] ) == -1;
        }

        private void sink( int k ) {
            while ( 2 * k <= N ) {
                int j = 2 * k;
                if ( j < N && less( j, j + 1 ) ) ++j;
                if ( ! less( k, j ) ) break;
                exchange( k, j );
                k = j;
            }
        }

        private void swim( int k ) {
            while ( k > 1 && less( k / 2, k ) ) {
                exchange( k / 2, k );
                k /= 2;
            }
        }

        public Matrix delMax() {
            Matrix max = pq[ 1 ];
            exchange( 1, N-- );
            pq[ N + 1 ] = null;
            sink( 1 );
            return max;
        }

        public Matrix max() {
            return pq[ 1 ];
        }

        public void insert( Matrix matrix ) {
            pq[ ++N ] = matrix;
            swim( N );
        }

        public void findMoves() {

            while ( ! this.isEmpty() ) {
                Matrix prevMatrix = this.delMax();
                if ( prevMatrix.isSorted() == 0 ) {
                    StdOut.println( "DEBUG: Solution found: " + prevMatrix.toString() );
                    break;
                }

                prevMatrix.generateMoves( this, prevMatrix );
            }
        }
    }

    public static void main( String[] args ) {
        int[][] intArr = {
                { 1, 0, 5 },
                { 2, 3, 4 },
                { 7, 6, 8 },
        };
        int[] blankIndex = { 0, 1 };

        Matrix matrix = new Matrix( intArr, blankIndex, 0 );
        MatrixMaxPQ maxPQ = new MatrixMaxPQ( 1000000000 );
        maxPQ.insert( matrix );
        maxPQ.findMoves();
    }
}
