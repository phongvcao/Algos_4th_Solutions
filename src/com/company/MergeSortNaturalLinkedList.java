package com.company;
import edu.princeton.cs.algs4.*;

public class MergeSortNaturalLinkedList {

    // Singly Linked-List
    public static class Node {
        Comparable value = 0;
        Node next = null;
    }

    public static Node head = null;
    public static int size = 0;

    public static String toString( Node node ) {
        String rv = "{ ";
        Node ptr = node;

        while ( ptr != null ) {
            rv += " " + ptr.value + ", ";
            ptr = ptr.next;
        }

        rv += " }";
        return rv;
    }

    public static void insertAtEnd( Node headNode, Comparable item ) {
        Node ptr = headNode;

        while ( ptr.next != null ) {
            ptr = ptr.next;
        }

        ptr.next = new Node();
        ptr.next.value = item;
    }

    // MergeSortNaturalLinkedList codes
    public static boolean less( Comparable a, Comparable b ) {
        return a.compareTo( b ) == -1;
    }

    public static void merge( Node node, Node aux, Node startNode, int leftSize, Node startNode2, int rightSize ) {
        // First copy everything to aux Linked-List
        Node ptr = startNode;
        int ptrIdx = 0;

        // This is for later merge
        Node ptrLeft = aux;
        Node ptrRight = aux;
        // END OF This is for later merge
        while ( ptrIdx < leftSize + rightSize ) {
            // Insert into aux
            if ( ptrIdx == 0 ) {
                aux.value = ptr.value;
            } else {
                insertAtEnd( aux, ptr.value );
            }
            ptr = ptr.next;
            ++ptrIdx;

            if ( ptrIdx <= leftSize ) {
                ptrRight = ptr;
            }

        }

        // Now merge [ startNode, startNode + leftSize ] with [ startNode2, startNode2 + rightSize ]
        int leftIdx = 0;
        int rightIdx = leftSize;
        ptr = startNode;
        for ( int i = 0; i < leftSize + rightSize; ++i ) {
            if ( leftIdx >= leftSize ) {
                ptr.value = ptrRight.value;
                ptr = ptr.next;
                ptrRight = ptrRight.next;
                ++rightIdx;
            } else if ( rightIdx >= leftSize + rightSize ) {
                ptr.value = ptrLeft.value;
                ptr = ptr.next;
                ptrLeft = ptrLeft.next;
                ++leftIdx;
            } else if ( less( ptrRight.value, ptrLeft.value ) ) {
                ptr.value = ptrRight.value;
                ptr = ptr.next;
                ptrRight = ptrRight.next;
                ++rightIdx;
            } else {
                ptr.value = ptrLeft.value;
                ptr = ptr.next;
                ptrLeft = ptrLeft.next;
                ++leftIdx;
            }
        }
    }

    public static void sort( Node node, Node aux ) {
        int leftSize = 1;
        Node startNode = node;
        Node prevNode = startNode;
        Node curNode = prevNode.next;
        while ( prevNode.value.compareTo( curNode.value ) <= 0 ) {
            prevNode = curNode;
            curNode = curNode.next;
            ++leftSize;
        }

        if ( curNode == null ) {
            return;
        }

        int rightSize = 1;
        Node startNode2 = curNode;
        Node prevNode2 = startNode2;
        Node curNode2 = prevNode2.next;
        while ( prevNode2.value.compareTo( curNode2.value ) <= 0 ) {
            prevNode2 = curNode2;
            curNode2 = curNode2.next;
            ++rightSize;
        }

        // Merge [ startNode, prevNode ] & [ startNode2, prevNode2 ]
        merge( node, aux, startNode, leftSize, startNode2, rightSize );
        sort( node, aux );
    }

    public static void sort( Node node ) {
        Node aux = new Node();
        sort( node, aux );
    }

    public static void main( String[] args ) {
        Integer[] intArr = { 14, 12, 10, 8, 6, 4, 2, 0, 1, 3, 5, 7, 9, 11 };

        // Build the Linked-List
        for ( int i = intArr.length - 1; i >= 0; --i ) {
            Node node = new Node();
            node.value = intArr[ i ];

            if ( head != null ) {
                node.next = head;
            }
            head = node;
            ++size;
        }

        // Print out the result
        StdOut.println( "DEBUG: (BEFORE): " + toString( head ) );

        sort( head );

        StdOut.println( "DEBUG: (AFTER): " + toString( head ) );
    }
}
