package com.company;
import edu.princeton.cs.algs4.*;

class IntNode {
    int key = 0;
    IntNode next = null;
}

public class IntegerLinkedList {
    public static int max( IntNode first ) {
        int max = first.key;
        IntNode ptr = first;
        while ( ptr != null ) {
            if ( max < ptr.key ) {
                max = ptr.key;
            }
            ptr = ptr.next;;
        }
        return max;
    }

    public static int maxRecursive( IntNode first, int maxKey ) {
        if ( first == null ) {
            return maxKey;
        }

        if ( maxKey < first.key ) {
            return first.key;
        } else {
            return maxRecursive( first.next, maxKey );
        }
    }

    public static IntNode createLinkedList( int[] intArr ) {
        IntNode first = new IntNode();
        IntNode prev = null;
        for ( int i = 0; i < intArr.length; ++i ) {
            first.key = intArr[ i ];
            if ( prev != null ) {
                prev = first;
            } else {
                prev = first;
            }
        }
        return first;
    }

    public static void main( String[] args ) {
        int[] intArr = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        IntNode first = createLinkedList( intArr );
        StdOut.println( "MAX: " + max( first ) );
        StdOut.println( "MAX: " + maxRecursive( first, first.key ) );
    }
}
