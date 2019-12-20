package com.company;
import edu.princeton.cs.algs4.*;
import java.util.Iterator;

public class RandomGrid {

    private static class Connection {
        int p;
        int q;

        public Connection( int p, int q ) {
            this.p = p;
            this.q = q;
        }

        public String toString() {
            return " | p : " + p + " ; q : " + q + " | ";
        }
    }

    public static Connection[] generate( int N ) {
        Connection[] connArr = new Connection[ N * N ];
        RandomBag< RandomBag< Connection > > randomBag2 = new RandomBag< RandomBag< Connection > >( 10 );

        for ( int i = 0; i < N; ++i ) {
            RandomBag< Connection > randomBag1 = new RandomBag< Connection >( N );
            for ( int j = 0; j < N; ++j ) {
                randomBag1.add( new RandomGrid.Connection( i, j ) );
                // StdOut.println( "DEBUG: randomBag1: " + java.util.Arrays.toString( randomBag1.array ) );
            }
            randomBag2.add( randomBag1 );
        }

        int index = 0;
        Iterator< RandomBag< Connection > > randomBag2Iter = randomBag2.iterator();
        while ( randomBag2Iter.hasNext() ) {
            RandomBag< Connection > randomBag1 = randomBag2Iter.next();
            Iterator< Connection > randomBag1Iter = randomBag1.iterator();

            while ( randomBag1Iter.hasNext() ) {
                connArr[ index++ ] = randomBag1Iter.next();
            }
        }

        return connArr;
    }

    public static void main( String[] args ) {
        int N = 10;
        Connection[] connArr = generate( N );

        for ( int i = 0; i < connArr.length; ++i ) {
            StdOut.println( "DEBUG: connArr.size(): " + connArr.length + "; i : " + i + " ; " + connArr[ i ].toString() );
        }
    }
}
