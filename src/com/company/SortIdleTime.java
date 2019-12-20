package com.company;
import edu.princeton.cs.algs4.*;
import java.util.ArrayList;

public class SortIdleTime {

    private static class Interval implements Comparable< Interval > {

        public Integer start = null;
        public Integer end = null;
        public Integer duration = null;

        public Interval( Integer start, Integer end ) {
            this.start = start;
            this.end = end;
            this.duration = this.end - this.start;
        }

        public int compareTo( Interval other ) {
            return this.start.compareTo( other.start );
        }

        public Interval join( Interval other ) {
            Integer[] overlapTime = new Integer[ 2 ];
            Interval overlapJob = null;
            if ( this.start >= other.start && this.start <= other.end ) {
                overlapTime[ 0 ] = other.start;
                if ( this.end <= other.end ) {
                    overlapTime[ 1 ] = other.end;
                } else {
                    overlapTime[ 1 ] = this.end;
                }
                overlapJob = new Interval( overlapTime[ 0 ], overlapTime[ 1 ] );
            } else if ( other.start >= this.start && other.start <= this.end ) {
                overlapTime[ 0 ] = this.start;
                if ( other.end <= this.end ) {
                    overlapTime[ 1 ] = this.end;
                } else {
                    overlapTime[ 1 ] = other.end;
                }
                overlapJob = new Interval( overlapTime[ 0 ], overlapTime[ 1 ] );
            }

            return overlapJob;
        }

        public String toString() {
            return this.start + " " + this.end + " " + this.duration;
        }
    }

    public static void heapSort( Interval[] a ) {
        for ( int i = a.length / 2; i >= 1; --i ) {
            sink( a, i, a.length );
        }

        StdOut.println( "DEBUG: jobArr (DURING): " + java.util.Arrays.toString( a ) );

        int N = a.length;
        while ( N > 0 ) {
            exchange( a, 1, N-- );
            sink( a, 1, N );
        }
    }

    public static void sink( Interval[] a, int k, int N ) {
        while ( 2 * k <= N ) {
            int j = 2 * k;
            if ( j < N && less( a, j, j + 1 ) ) ++j;
            if ( ! less( a, k, j ) ) break;
            exchange( a, j, k );
            k = j;
        }
    }

    public static boolean less( Interval[] a, int i, int j ) {
        return a[ i - 1 ].compareTo( a[ j - 1 ] ) == -1;
    }

    public static void exchange( Interval[] a, int i, int j ) {
        Interval temp = a[ i - 1 ];
        a[ i - 1 ] = a[ j - 1 ];
        a[ j - 1 ] = temp;
    }

    public static void main( String[] args ) {
        Integer[][] jobs = {
                { 1, 3 }, { 1, 4 }, { 1, 5 }, { 4, 8 },
                { 9, 11 }, { 14, 20 }, { 12, 14 }, { 30, 31 },
                { 33, 34 }, { 34, 35 }, { 36, 37 }, { 37, 38 },
        };

        Interval[] jobArr = new Interval[ jobs.length ];
        for ( int i = 0; i < jobs.length; ++i ) {
            jobArr[ i ] = new Interval( jobs[ i ][ 0 ], jobs[ i ][ 1 ] );
        }

        StdOut.println( "DEBUG: jobArr (BEFORE): " + java.util.Arrays.toString( jobArr ) );

        heapSort( jobArr );

        StdOut.println( "DEBUG: jobArr (AFTER): " + java.util.Arrays.toString( jobArr ) );

        ArrayList< Interval > nonIdleList = new ArrayList< Interval >();
        int jobArrIdx = 0;
        Interval nonIdleMax = null;

        while ( jobArrIdx < jobs.length ) {
            if ( nonIdleList.isEmpty() ) {
                nonIdleList.add( jobArr[ jobArrIdx ] );
            } else {
                Interval lastInsertedJob = nonIdleList.get( nonIdleList.size() - 1 );
                Interval joinedJob = lastInsertedJob.join( jobArr[ jobArrIdx ] );
                if ( joinedJob != null ) {
                    nonIdleList.remove( nonIdleList.size() - 1 );
                    nonIdleList.add( nonIdleList.size(), joinedJob );
                } else {
                    nonIdleList.add( nonIdleList.size(), jobArr[ jobArrIdx ] );
                }
            }
            if ( ( nonIdleMax == null ) || ( nonIdleList.get( nonIdleList.size() - 1 ).duration.compareTo( nonIdleMax.duration ) == 1 ) ) {
                nonIdleMax = nonIdleList.get( nonIdleList.size() - 1 );
            }
            ++jobArrIdx;
        }

        StdOut.println( "DEBUG: nonIdleList (FINAL): " + nonIdleList.toString() );

        ArrayList< Interval > idleList = new ArrayList< Interval >();
        int idleListArrIdx = 0;
        Interval idleMax = null;
        for ( int i = 1; i < nonIdleList.size(); ++i ) {
            idleList.add( idleListArrIdx++, new Interval( nonIdleList.get( i - 1 ).end, nonIdleList.get( i ).start ) );

            if ( ( idleMax == null ) || ( idleList.get( idleList.size() - 1 ).duration.compareTo( idleMax.duration ) == 1 ) ) {
                idleMax = idleList.get( idleList.size() - 1 );
            }
        }

        StdOut.println( "DEBUG: idleList (FINAL): " + idleList.toString() );
        StdOut.println( "DEBUG: nonIdleMax (FINAL): " + nonIdleMax );
        StdOut.println( "DEBUG: idleMax (FINAL): " + idleMax );
    }
}
