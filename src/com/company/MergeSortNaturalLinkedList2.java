package com.company;
import edu.princeton.cs.algs4.*;

public class MergeSortNaturalLinkedList2 {

    // LINKED-LIST IMPLEMENTATION
    public static class Node {
        Comparable item = null;
        Node next = null;
    }

    public static Node head = null;

    public static void append( Comparable item ) {
        if ( head == null ) {
            head = new Node();
            head.item = item;
        } else {
            Node ptr = head;
            while ( ptr.next != null ) {
                ptr = ptr.next;
            }
            ptr.next = new Node();
            ptr.next.item = item;
        }
    }

    public static void copy( Node fromNode, Node toNode, int size ) {
        Node fromNodePtr = fromNode;
        Node toNodePtr = toNode;
        for ( int i = 0; i < size; ++i ) {
            toNodePtr.item = fromNodePtr.item;
            if ( ( i < size - 1 ) && ( toNodePtr.next == null ) ) {
                toNodePtr.next = new Node();
            }
            toNodePtr = toNodePtr.next;
            fromNodePtr = fromNodePtr.next;
        }
    }

    public static String toString( Node node ) {
        String rv = "{ ";
        Node ptr = node;

        while ( ptr != null ) {
            rv += " " + ptr.item + ",";
            ptr = ptr.next;
        }

        rv += " }";
        return rv;
    }
    // END OF LINKED-LIST IMPLEMENTATION

    public static boolean less( Comparable a, Comparable b ) {
        return a.compareTo( b ) == -1;
    }

    public static void merge( Node headNode, Node auxNode, int leftSize, int rightSize ) {
        // Copy content of headNode to auxNode
        copy( headNode, auxNode, leftSize + rightSize );

        Node headNodePtr = headNode;
        Node auxNodeLeftPtr = auxNode;
        Node auxNodeRightPtr = auxNodeLeftPtr;

        for ( int i = 0; i < leftSize; ++i ) {
            auxNodeRightPtr = auxNodeRightPtr.next;
        }

        int leftIdx = 0;
        int rightIdx = leftSize;
        for ( int i = 0; i < leftSize + rightSize; ++i ) {
            if ( leftIdx > leftSize - 1 ) {
                headNodePtr.item = auxNodeRightPtr.item;
                auxNodeRightPtr = auxNodeRightPtr.next;
                ++rightIdx;
            } else if ( rightIdx > leftSize + rightSize - 1 ) {
                headNodePtr.item = auxNodeLeftPtr.item;
                auxNodeLeftPtr = auxNodeLeftPtr.next;
                ++leftIdx;
            } else if ( less( auxNodeRightPtr.item, auxNodeLeftPtr.item ) ) {
                headNodePtr.item = auxNodeRightPtr.item;
                auxNodeRightPtr = auxNodeRightPtr.next;
                ++rightIdx;
            } else {
                headNodePtr.item = auxNodeLeftPtr.item;
                auxNodeLeftPtr = auxNodeLeftPtr.next;
                ++leftIdx;
            }

            headNodePtr = headNodePtr.next;;
        }
    }

    public static void sortNatural( Node headNode, Node auxNode ) {
        // Figure out leftSize & rightSize
        int leftSize = 1;

        Node leftHeadNodePtr = headNode;

        while ( ( leftHeadNodePtr != null ) && ( leftHeadNodePtr.next != null ) && ( leftHeadNodePtr.item.compareTo( leftHeadNodePtr.next.item ) <= 0 ) ) {
            ++leftSize;
            leftHeadNodePtr = leftHeadNodePtr.next;
        }

        if ( leftHeadNodePtr.next == null ) {
            return;
        }

        Node rightHeadNodePtr = leftHeadNodePtr.next;
        int rightSize = 1;
        while ( ( rightHeadNodePtr != null ) && ( rightHeadNodePtr.next != null ) && ( rightHeadNodePtr.item.compareTo( rightHeadNodePtr.next.item ) <= 0 ) ) {
            ++rightSize;
            rightHeadNodePtr = rightHeadNodePtr.next;
        }

        // StdOut.println( "DEBUG: leftSize: " + leftSize + "; rightSize: " + rightSize );
        merge( headNode, auxNode, leftSize, rightSize );

        // StdOut.println( "DEBUG: headNode: " + toString( headNode ) );
        // StdOut.println( "DEBUG: auxNode: " + toString( auxNode ) );

        sortNatural( headNode, auxNode );
    }

    public static void main( String[] args ) {
        Integer[] intArr = { 14, 12, 10, 8, 6, 4, 2, 0, 1, 3, 5, 7, 9 };

        for ( int i = 0; i < intArr.length; ++i ) {
            append( intArr[ i ] );
        }

        Node toNode = new Node();
        copy( head, toNode, intArr.length );

        // sort( intArr );
        Node aux = new Node();
        StdOut.println( "DEBUG: head (BEFORE): " + toString( head ) );
        sortNatural( head, aux );

        StdOut.println( "DEBUG: head (AFTER): " + toString( head ) );
        StdOut.println( "DEBUG: toNode: " + toString( toNode ) );

        /* Integer[] intArr = { 0, 2, 4, 6, 8, 10, 12, 14, 1, 3, 5, 7, 9 };

        for ( int i = 0; i < intArr.length; ++i ) {
            append( intArr[ i ] );
        }

        Node aux = new Node();

        StdOut.println( "DEBUG: head (BEFORE): " + toString( head ) );

        // merge( head, aux, 8, 5 );
        sortNatural( head, aux );

        StdOut.println( "DEBUG: head (AFTER): " + toString( head ) ); */
    }
}
