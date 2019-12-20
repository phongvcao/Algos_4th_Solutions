package com.company;
import edu.princeton.cs.algs4.*;
import java.util.HashSet;

public class LPTLoadBalancing {

    private static class Job implements Comparable< Job > {
        public int index = -1;
        public int time = -1;

        public Job( int index, int time ) {
            this.index = index;
            this.time = time;
        }

        public int compareTo( Job other ) {
            if ( this.time < other.time ) {
                return -1;
            } else if ( this.time > other.time ) {
                return 1;
            } else {
                return 0;
            }
        }

        public String toString() {
            return " | " + this.index + " : " + this.time + " | ";
        }
    }

    private static class Processor implements Comparable< Processor > {
        public int index = -1;
        public int time = 0;
        public HashSet< Job > jobSet;

        public Processor( int index ) {
            this.index = index;
            jobSet = new HashSet< Job >();
        }

        public void add( Job job ) {
            this.jobSet.add( job );
            this.time += job.time;
        }

        public int compareTo( Processor other ) {
            if ( this.time < other.time ) {
                return -1;
            } else if ( this.time > other.time ) {
                return 1;
            } else {
                return 0;
            }
        }

        public String toString() {
            return "\n | " + this.index + " : " + this.time + " : " + this.jobSet.toString() + " | ";
        }
    }

    private static class ProcessorQueue {

        private Processor[] pq;
        private int N = 0;

        public ProcessorQueue( int minN ) {
            pq = new Processor[ minN + 1 ];
        }

        private void swim( int k ) {
            while ( k > 1 && less( k, k / 2 ) ) {
                exchange( k / 2, k );
                k /= 2;
            }
        }

        private void sink( int k ) {
            while ( 2 * k <= N ) {
                int j = 2 * k;
                if ( j < N && less( j + 1, j ) ) ++j;
                if ( ! less( j, k ) ) break;
                exchange( k, j );
                k = j;
            }
        }

        private boolean less( int i, int j ) {
            return pq[ i ].compareTo( pq[ j ] ) == -1;
        }

        private void exchange( int i, int j ) {
            Processor temp = pq[ i ];
            pq[ i ] = pq[ j ];
            pq[ j ] = temp;
        }

        public void insert( Processor proc ) {
            pq[ ++N ] = proc;
            swim( N );
        }

        public Processor delMin() {
            Processor min = pq[ 1 ];
            exchange( 1, N-- );
            pq[ N + 1 ] = null;
            sink( 1 );
            return min;
        }

        public Processor min() {
            return pq[ 1 ];
        }

        public String toString() {
            return java.util.Arrays.toString( pq );
        }

        public String toStringDelMin() {
            String rv = "{ ";

            while ( ! isEmpty() ) {
                rv += delMin() + ", ";
            }

            rv += "}";
            return rv;
        }

        public int size() {
            return N;
        }

        public boolean isEmpty() {
            return size() == 0;
        }
    }

    public static boolean less( Job a, Job b ) {
        return a.compareTo( b ) == -1;
    }

    public static void exchange( Job[] a, int i, int j ) {
        Job temp = a[ i ];
        a[ i ] = a[ j ];
        a[ j ] = temp;
    }

    public static void quickSort( Job[] a ) {
        quickSort( a, 0, a.length - 1 );
    }

    public static void quickSort( Job[] a, int low, int high ) {
        if ( low >= high ) return;

        int j = partition( a, low, high );
        quickSort( a, low, j - 1 );
        quickSort( a, j + 1, high );
    }

    public static int partition( Job[] a, int low, int high ) {
        int i = low;
        int j = high + 1;
        Job pivot = a[ low ];

        while ( true ) {
            while ( less( pivot, a[ ++i ] ) ) if ( i == high ) break;
            while ( less( a[ --j ], pivot ) ) if ( j == low ) break;

            if ( i >= j ) break;

            exchange( a, i, j );
        }
        exchange( a, low, j );
        return j;
    }

    public static void main( String[] args ) {
        Integer[] intArr = { 14, 12, 10, 8, 6, 4, 2, 0, 1, 3, 5, 7, 9, 11, 13 };
        Job[] jobArr = new Job[ intArr.length ];
        for ( int i = 0; i < intArr.length; ++i ) {
            jobArr[ i ] = new Job( intArr[ i ], intArr[ i ] );
        }

        StdOut.println( "DEBUG: jobArr (BEFORE): " + java.util.Arrays.toString( jobArr ) );

        quickSort( jobArr );

        StdOut.println( "DEBUG: jobArr (AFTER): " + java.util.Arrays.toString( jobArr ) );

        ProcessorQueue queue = new ProcessorQueue( 5 );
        queue.insert( new Processor( 0 ) );
        queue.insert( new Processor( 1 ) );
        queue.insert( new Processor( 2 ) );
        queue.insert( new Processor( 3 ) );
        queue.insert( new Processor( 4 ) );

        StdOut.println( "DEBUG: queue (BEFORE): " + queue.toString() );

        for ( int i = 0; i < jobArr.length; ++i ) {
            Processor proc = queue.delMin();
            proc.add( jobArr[ i ] );
            queue.insert( proc );
        }

        StdOut.println( "DEBUG: queue (AFTER): " + queue.toString() );
    }
}
