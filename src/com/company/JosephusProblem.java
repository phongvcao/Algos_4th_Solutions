package com.company;
import edu.princeton.cs.algs4.*;

public class JosephusProblem {

    private DoubleNode first = null;
    private DoubleNode last = null;
    private int N = 0;

    // Implementing circular linked list
    private class DoubleNode {
        int index = 0;
        DoubleNode next = null;
        DoubleNode prev = null;
    }

    public void add( int item ) {
        DoubleNode newNode = new DoubleNode();
        newNode.index = item;

        if ( isEmpty() ) {
            first = newNode;
            last = newNode;
            first.next = last;
            last.next = first;
            first.prev = last;
            last.prev = first;
        } else {
            newNode.next = first;
            newNode.prev = last;
            first.prev = newNode;
            last.next = newNode;

            first = newNode;
            // last.next = first;
        }

        ++N;
    }

    public boolean isEmpty() {
        return N == 0;
    }

    public int size() {
        return N;
    }

    public String toString() {
        String rv = "{";
        DoubleNode ptr = first;

        while ( ptr.index != last.index ) {
            try {
                rv += " " + ptr.index;
                if ( ptr.prev != null ) {
                    rv += ", prev: " + ptr.prev.index;
                }

                if ( ptr.next != null ) {
                    rv += ", next: " + ptr.next.index;
                }

                rv += ";";
            } catch ( java.lang.NullPointerException e ) {
                rv += " " + ptr.index + ";;";
            }
            ptr = ptr.next;
        }

        rv += " " + ptr.index;
        if ( ptr.prev != null ) {
            rv += ", prev: " + ptr.prev.index;
        }

        if ( ptr.next != null ) {
            rv += ", next: " + ptr.next.index;
        }

        rv += "; ( first: " + first.index + "; last: " + last.index + " ) ";

        rv += " }";
        return rv;
    }

    public String toStringReverse() {
        String rv = "{";
        DoubleNode ptr = last;

        while ( ptr.index != first.index ) {
            rv += " " + ptr.index + ",";
            ptr = ptr.prev;
        }

        rv += " " + ptr.index + ",";

        rv += " }";
        return rv;
    }

    private void removeNode( DoubleNode node ) {
        StdOut.print( "DEBUGGING: removeNode(): node.index: " + node.index + "; " );
        if ( node.prev != null ) {
            StdOut.print( "node.prev.next.index (BEFORE): " + node.prev.next.index );
            node.prev.next = node.next;
            StdOut.print( "; node.prev.next.index (AFTER): " + node.prev.next.index );

            if ( node.next != null ) {
                StdOut.print( "; node.next.index (AFTER): " + node.next.index );
            }
        }

        if ( node.next != null ) {
            StdOut.print( "; node.next.prev.index (BEFORE): " + node.next.prev.index );
            node.next.prev = node.prev;
            StdOut.print( "; node.next.prev.index (AFTER): " + node.next.prev.index );

            if ( node.prev != null ) {
                StdOut.print( "; node.prev.index (AFTER): " + node.prev.index );
            }
        }
        StdOut.println();

        StdOut.println( "DEBUG: N (BEFORE): " + N );
        --N;
        StdOut.println( "DEBUG: N (AFTER): " + N );
    }

    public void killEvery( int M, int[] intArr ) {
        DoubleNode ptr = first;
        int index = 0;

        while ( N > 1 ) {
            for ( int i = 0; i < M - 1; ++i ) {
                StdOut.print( "DEBUG: Looping: " + ptr.index + "; first: " + first.index + "; last: " + last.index );
                if ( ptr.prev != null ) {
                    StdOut.print( "; prev: " + ptr.prev.index );
                }

                if ( ptr.next != null ) {
                    StdOut.print( "; next: " + ptr.next.index );
                }
                StdOut.println();
                ptr = ptr.next;
            }

            StdOut.println( "DEBUG: REMOVING: " + ptr.index + "; N: " + N );
            intArr[ index++ ] = ptr.index;
            StdOut.println( "DEBUG: REMOVED SO FAR: " + java.util.Arrays.toString( intArr ) + "; N: " + N );

            try {
                StdOut.println( "DEBUGGGING: N (BEFORE): " + N );
                removeNode( ptr );

                StdOut.println( "DEBUGGGING: N (AFTER): " + N );

                if ( N <= 1 ) return;
            } catch ( java.lang.NullPointerException e ) {
                StdOut.println( "; EXCEPTION THROWN while REMOVING node.index: " + ptr.index );
                break;
            }


            ptr = ptr.next;
        }
    }

    public static void main( String[] args ) {
        int N = 7;
        JosephusProblem linkedList = new JosephusProblem();

        for ( int i = N - 1; i >= 0; --i ) {
            linkedList.add( i );
        }

        StdOut.println( "DEBUG: " + linkedList.toString() );
        StdOut.println( "DEBUG: " + linkedList.toStringReverse() );

        int[] intArr = new int[N];
        linkedList.killEvery( 2, intArr );

        if ( N % 2 == 0 ) {
            intArr[ intArr.length - 1 ] = linkedList.first.index;
        } else {
            intArr[ intArr.length - 1 ] = linkedList.last.index;
        }

        // StdOut.println( "DEBUG (AFTER KILL): " + linkedList.toString() );
        StdOut.println( "DEBUG (AFTER KILL): intArr: " + java.util.Arrays.toString( intArr ) );
    }
}
