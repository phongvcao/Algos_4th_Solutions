package com.company;
import edu.princeton.cs.algs4.*;
import java.util.Random;

public class HeapSamplingFromDiscreteDistribution {

    private double[] tree;
    private int N = 0;
    public int T = 0;

    public HeapSamplingFromDiscreteDistribution( double[] arr ) {
        tree = new double[ arr.length + 1 ];
        tree[ 0 ] = -1;
        for ( int i = 0; i < arr.length; ++i ) {
            insert( arr[ i ] );
        }
    }

    public void insert( double v ) {
        tree[ ++N ] = v;
        swim( N );
    }

    public void swim( int k ) {
        double kValue = tree[ k ];
        while ( k > 1 ) {
            tree[ k / 2 ] += kValue;
            k /= 2;
        }
    }

    public int random() {
        Random random = new Random();
        double randDouble = random.nextFloat() * tree[ 1 ];

        return sink( 1, randDouble );
    }

    public int sink( int k, double value ) {
        while ( 2 * k <= N ) {
            int j = 2 * k;
            value -= tree[ j ];

            if ( value < 0 ) {
                break;
            }

            if ( value > tree[ j ] ) {
                ++j;
            }
            k = j;
        }
        return k;
    }

    public void change( int i, double v ) {
        double leftChildValue = i * 2 < N ? tree[ i * 2 ] : 0;
        double rightChildValue = i * 2 + 1 < N ? tree[ i * 2 + 1 ] : 0;
        double orgValue = tree[ i ] - leftChildValue - rightChildValue;
        tree[ i ] = 0 - orgValue;
        swim( i );
        tree[ i ] = v;
        swim( i );
        tree[ i ] = v + leftChildValue + rightChildValue;
    }

    public String toString() {
        return java.util.Arrays.toString( tree );
    }

    public static void main( String[] args ) {
        double[] doubleArr = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0 };
        HeapSamplingFromDiscreteDistribution heapSampling = new HeapSamplingFromDiscreteDistribution( doubleArr );

        StdOut.println( "DEBUG: heapSampling (BEFORE): " + heapSampling.toString() );

        StdOut.println( "DEBUG: heapSampling (random): " + heapSampling.random() );
        StdOut.println( "DEBUG: heapSampling (random): " + heapSampling.random() );
        StdOut.println( "DEBUG: heapSampling (random): " + heapSampling.random() );

        heapSampling.change( 9, 8.0 );
        StdOut.println( "DEBUG: heapSampling (AFTER): " + heapSampling.toString() );
    }
}
