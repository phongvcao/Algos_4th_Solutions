package com.company;
import java.util.HashSet;
import edu.princeton.cs.algs4.*;

public class EightPuzzleGame1 {

    private static class Matrix implements Comparable< Matrix > {

        public int[] data = null;
        public int blankIndex = -1;
        public int numWrongPos = 0;
        public int numMoves = 0;
        public int priority = 0;
        public enum PriorityFormula {
            WRONG_POS, MANHANTTAN_DISTANCE, SQUARE_SUM,
        }
        public PriorityFormula formula = null;
        public static int[] sortedMatrix = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };

        public Matrix( int[] data, int blankIndex, int numMoves, PriorityFormula formula ) {
            this.data = data;
            this.blankIndex = blankIndex;
            this.numWrongPos = this.isSorted();
            this.numMoves = numMoves;
            this.formula = formula;
            calculatePriority();
        }

        private void calculatePriority() {
            if ( this.formula == PriorityFormula.WRONG_POS ) {
                this.priority = this.numMoves + this.numWrongPos;
            } else if ( this.formula == PriorityFormula.MANHANTTAN_DISTANCE ) {
                for ( int i = 0; i < this.data.length; ++i ) {
                    this.priority += Math.abs( i - this.data[ i ] );
                }
            } else if ( this.formula == PriorityFormula.SQUARE_SUM ) {
                int manhanttanSum = 0;
                for ( int i = 0; i < this.data.length; ++i ) {
                    manhanttanSum += Math.abs( i - this.data[ i ] );
                }
                this.priority = (int)( Math.pow( this.numMoves + this.numWrongPos, 2 ) + Math.pow( manhanttanSum, 2 ) );
            }
        }

        public int compareTo( Matrix other ) {
            if ( this.priority > other.priority ) {
                return 1;
            } else if ( this.priority < other.priority ) {
                return -1;
            }

            return 0;
        }

        public boolean isDuplicated( Matrix other ) {
            for ( int i = 0; i < this.data.length; ++i ) {
                if ( this.data[ i ] != other.data[ i ] ) {
                    return false;
                }
            }
            return true;
        }

        public int isSorted() {
            int wrongPosCount = 0;
            for ( int i = 0; i < this.data.length; ++i ) {
                if ( this.data[ i ] != Matrix.sortedMatrix[ i ] ) {
                    ++wrongPosCount;
                }
            }
            return wrongPosCount;
        }

        public String toString() {
            String rv = "DEBUG: PRIORITY : " + this.priority + " ; NUM_WRONG_POS : " + this.numWrongPos +
                        " ; NUM_MOVES : " + this.numMoves + "\n";
            rv += "DEBUG: DATA : " + java.util.Arrays.toString( this.data );
            return rv;
        }

        private void exchange( int[] a, int i, int j ) {
            int temp = a[ i ];
            a[ i ] = a[ j ];
            a[ j ] = temp;
        }

        public Matrix moveLeft() {
            Matrix newMatrix = null;
            if ( this.blankIndex % 3 > 0 ) {
                int[] newMatrixData = new int[ this.data.length ];
                System.arraycopy( this.data, 0, newMatrixData, 0, this.data.length );
                exchange( newMatrixData, this.blankIndex, this.blankIndex - 1 );
                newMatrix = new Matrix( newMatrixData, this.blankIndex - 1, this.numMoves + 1, this.formula );
            }
            return newMatrix;
        }

        public Matrix moveRight() {
            Matrix newMatrix = null;
            if ( this.blankIndex % 3 < 2 ) {
                int[] newMatrixData = new int[ this.data.length ];
                System.arraycopy( this.data, 0, newMatrixData, 0, this.data.length );
                exchange( newMatrixData, this.blankIndex, this.blankIndex + 1 );
                newMatrix = new Matrix( newMatrixData, this.blankIndex + 1, this.numMoves + 1, this.formula );
            }
            return newMatrix;
        }

        public Matrix moveUp() {
            Matrix newMatrix = null;
            if ( this.blankIndex / 3 > 0 ) {
                int[] newMatrixData = new int[ this.data.length ];
                System.arraycopy( this.data, 0, newMatrixData, 0, this.data.length );
                exchange( newMatrixData, this.blankIndex, this.blankIndex - 3 );
                newMatrix = new Matrix( newMatrixData, this.blankIndex - 3, this.numMoves + 1, this.formula );
            }
            return newMatrix;
        }

        public Matrix moveDown() {
            Matrix newMatrix = null;
            if ( this.blankIndex / 3 < 2 ) {
                int[] newMatrixData = new int[ this.data.length ];
                System.arraycopy( this.data, 0, newMatrixData, 0, this.data.length );
                exchange( newMatrixData, this.blankIndex, this.blankIndex + 3 );
                newMatrix = new Matrix( newMatrixData, this.blankIndex + 3, this.numMoves + 1, this.formula );
            }
            return newMatrix;
        }

        public boolean equals( Object other ) {
            if ( other instanceof Matrix ) {
                Matrix otherMatrix = (Matrix)other;
                for ( int i = 0; i < this.data.length; ++i ) {
                    if ( this.data[ i ] != otherMatrix.data[ i ] ) {
                        return false;
                    }
                }
                return true;
            } else {
                return false;
            }
        }

        public int hashCode() {
            return java.util.Arrays.toString( this.data ).hashCode();
        }
    }

    private static class MatrixPQ {

        private Matrix[] pq;
        private int N = 0;
        private boolean isMaxPQ = true;

        public MatrixPQ( int size, boolean isMaxPQ ) {
            pq = new Matrix[ size + 1 ];
            this.isMaxPQ = isMaxPQ;
        }

        public void insert( Matrix matrix ) {
            pq[ ++N ] = matrix;
            swim( N );
        }

        public Matrix root() {
            return pq[ 1 ];
        }

        public Matrix delRoot() {
            Matrix root = pq[ 1 ];
            exchange( 1, N-- );
            pq[ N + 1 ] = null;
            sink( 1 );
            return root;
        }

        private void exchange( int i, int j ) {
            Matrix temp = pq[ i ];
            pq[ i ] = pq[ j ];
            pq[ j ] = temp;
        }

        private boolean less( int i, int j ) {
            return pq[ i ].compareTo( pq[ j ] ) == -1;
        }

        private void swim( int k ) {
            if ( this.isMaxPQ ) {
                while ( k > 1 && less( k / 2, k ) ) {
                    exchange( k / 2, k );
                    k /= 2;
                }
            } else {
                while ( k > 1 && less( k, k / 2 ) ) {
                    exchange( k / 2, k );
                    k /= 2;
                }
            }
        }

        private void sink( int k ) {
            while ( 2 * k <= N ) {
                int j = 2 * k;
                if ( this.isMaxPQ ) {
                    if ( j < N && less( j, j + 1 ) ) ++j;
                    if ( ! less( k, j ) ) break;
                } else {
                    if ( j < N && less( j + 1, j ) ) ++j;
                    if ( ! less( j, k ) ) break;
                }
                exchange( k, j );
                k = j;
            }
        }

        public String toString() {
            String rv = "";

            for ( int i = 0; i < N; ++i ) {
                rv += pq[ i ] + " ";
            }

            return rv;
        }

        public int size() {
            return N;
        }

        public boolean isEmpty() {
            return size() == 0;
        }

        public void generateMoves() {
            HashSet< Matrix > generatedMatrices = new HashSet< Matrix >();
            generatedMatrices.add( root() );

            while ( ! isEmpty() ) {

                // StdOut.println( "DEBUG: toString(): " + toString() );

                Matrix root = delRoot();
                Matrix movedLeft = root.moveLeft();
                Matrix movedRight = root.moveRight();
                Matrix movedUp = root.moveUp();
                Matrix movedDown = root.moveDown();
                if ( ( movedLeft != null ) && ( ! generatedMatrices.contains( movedLeft ) ) ) {
                    if ( movedLeft.isSorted() == 0 ) {
                        StdOut.println( "DEBUG: FOUND: " + movedLeft );
                        return;
                    }

                    generatedMatrices.add( movedLeft );
                    insert( movedLeft );
                } else if ( generatedMatrices.contains( movedLeft ) ) {
                    StdOut.println( "DEBUG: ALREADY GENERATED: " + movedLeft );
                }

                if ( ( movedRight != null ) && ( ! generatedMatrices.contains( movedRight ) ) ) {
                    if ( movedRight.isSorted() == 0 ) {
                        StdOut.println( "DEBUG: FOUND: " + movedRight );
                        return;
                    }

                    generatedMatrices.add( movedRight );
                    insert( movedRight );
                } else if ( generatedMatrices.contains( movedRight ) ) {
                    StdOut.println( "DEBUG: ALREADY GENERATED: " + movedRight );
                }

                if ( ( movedUp != null ) && ( ! generatedMatrices.contains( movedUp ) ) ) {
                    if ( movedUp.isSorted() == 0 ) {
                        StdOut.println( "DEBUG: FOUND: " + movedUp );
                        return;
                    }

                    generatedMatrices.add( movedUp );
                    insert( movedUp );
                } else if ( generatedMatrices.contains( movedUp ) ) {
                    StdOut.println( "DEBUG: ALREADY GENERATED: " + movedUp );
                }

                if ( ( movedDown != null ) && ( ! generatedMatrices.contains( movedDown ) ) ) {
                    if ( movedDown.isSorted() == 0 ) {
                        StdOut.println( "DEBUG: FOUND: " + movedDown );
                        return;
                    }

                    generatedMatrices.add( movedDown );
                    insert( movedDown );
                } else if ( generatedMatrices.contains( movedDown ) ) {
                    StdOut.println( "DEBUG: ALREADY GENERATED: " + movedDown );
                }
            }
        }
    }

    public static void main( String[] args ) {
        int[] intArr = { 1, 0, 5, 2, 3, 4, 7, 6, 8 };
        MatrixPQ matrixPQ = new MatrixPQ( 1000000, false );

        // Matrix matrix = new Matrix( intArr, 1, 0, Matrix.PriorityFormula.WRONG_POS );
        // Matrix matrix = new Matrix( intArr, 1, 0, Matrix.PriorityFormula.MANHANTTAN_DISTANCE );
        Matrix matrix = new Matrix( intArr, 1, 0, Matrix.PriorityFormula.SQUARE_SUM );

        matrixPQ.insert( matrix );
        matrixPQ.generateMoves();
    }
}
