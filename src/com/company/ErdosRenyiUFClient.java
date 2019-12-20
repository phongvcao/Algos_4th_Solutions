package com.company;
import edu.princeton.cs.algs4.*;
import java.util.Random;

public class ErdosRenyiUFClient {

    public static int count( int N ) {
        Random rand = new Random();
        int N1 = rand.nextInt( N );
        int N2 = rand.nextInt( N );

        UF uf = new UF( N );
        int countUnion = 0;

        do {

            if ( ! uf.connected( N1, N2 ) ) {
                uf.union( N1, N2 );
                ++countUnion;
            }

            N1 = rand.nextInt( N );
            N2 = rand.nextInt( N );
        } while ( uf.count() > 1 );
        return countUnion;
    }

    public static void main( String[] args ) {
        // StdOut.println( "DEBUG: N: " + N + "; count: " + count( N ) );
        int N = 50;
        StdOut.println( "DEBUG: N: " + N + "; countUnion: " + count( N ) );
    }
}
