package com.company;
import edu.princeton.cs.algs4.*;

public class MoveToFront {

    private class Node {
        char value = '\0';
        Node next = null;
    }

    private Node first = null;
    private Node last = null;

    public void insert( char c ) {
        Node newNode = new Node();
        newNode.value = c;

        if ( first == null ) {
            first = newNode;
            last = newNode;
        } else {
            Node ptr = first;
            Node beforePtr = null;
            boolean isFound = false;

            while ( ptr != null ) {
                // StdOut.println( "DEBUG: ptr != null" );
                if ( c == ptr.value ) {
                    // Remove ptr from list
                    if ( beforePtr != null ) {
                        beforePtr.next = ptr.next;
                    } else {
                        first = null;
                        last = null;
                    }

                    // Then insert at beginning
                    newNode.next = first;
                    first = newNode;
                    isFound = true;
                }
                beforePtr = ptr;
                ptr = ptr.next;
            }

            if ( ! isFound ) {
                // Insert at the beginning
                newNode.next = first;
                first = newNode;
            }
        }
    }

    public String toString() {
        String rv = "{";
        Node ptr = first;

        while ( ptr != null ) {
            rv += " " + ptr.value + ",";
            ptr = ptr.next;
        }

        rv += " }";
        return rv;
    }

    public static void main( String[] args ) {
        char[] charArr = { '0', '1', '2', '3', '4', '5', '4', '2', '0' };
        MoveToFront linkedList = new MoveToFront();

        for ( int i = 0; i < charArr.length; ++i ) {
            // StdOut.println( "DEBUG: Looping through ( 0 ): " + i );
            // StdOut.println( "DEBUG: " + linkedList.toString() );
            linkedList.insert( charArr[ i ] );
            // StdOut.println( "DEBUG: Looping through ( 1 ): " + i );
        }

        StdOut.println( "DEBUG: " + linkedList.toString() );
    }
}
