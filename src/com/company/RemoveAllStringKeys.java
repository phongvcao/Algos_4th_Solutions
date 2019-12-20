package com.company;
import edu.princeton.cs.algs4.*;

 class Node {
    String key = "";
    Node next = null;
}

public class RemoveAllStringKeys {
    private Node first;

    private int N = 0;

    public boolean isEmpty() { return first == null; }
    public int size() { return N; }

    public void prepend( String key ) {
        Node oldFirst = first;
        first = new Node();
        first.key = key;
        first.next = oldFirst;
        ++N;
    }

    public void remove( String key ) {
        Node ptr = this.first;
        Node beforePtr = ptr;

        while ( ptr != null ) {
            if ( ptr.key == key ) {
                if ( ptr == beforePtr ) {
                    beforePtr = this.first.next;
                    ptr = this.first.next;
                    this.first = this.first.next;
                } else {
                    // Remove current ptr
                    StdOut.println( "DEBUG: TO BE REMOVED ( - ): " + ptr.key );
                    beforePtr.next = ptr.next;
                }
            }

            // Move one more place
            beforePtr = ptr;
            ptr = ptr.next;
        }
    }

    public Node getFirst() {
        return first;
    }

    public String toString() {
        String rv = "{";
        Node ptr = first;
        while ( ptr != null ) {
            rv += " " + ptr.key + ",";
            ptr = ptr.next;
        }
        rv += " }";
        return rv;
    }

    public static String toString( RemoveAllStringKeys linkedList ) {
        String rv = "{";
        Node ptr = linkedList.getFirst();
        while ( ptr != null ) {
            rv += " " + ptr.key +",";
            ptr = ptr.next;
        }
        rv += " )";
        return rv;
    }

    public static void main( String[] args ) {
        String[] strArr = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
                "0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
                "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
        RemoveAllStringKeys linkedList = new RemoveAllStringKeys();

        for ( int i = 0; i < strArr.length; ++i ) {
            linkedList.prepend( strArr[ i ] );
        }

        Node innerLinkedList = linkedList.first;

        StdOut.println( "DEBUG: linkedList: " + toString( linkedList ) );
        StdOut.println( "DEBUG: strArr: " + java.util.Arrays.toString( strArr ) );

        linkedList.remove( "9" );

        StdOut.println( "DEBUG: linkedList (AFTER): " + toString( linkedList ) );

    }
}
