package com.company;
import java.util.Iterator;
import java.util.ConcurrentModificationException;

public class FailFastIterator< Item > implements Iterable< Item > {

    private int N = 0;
    private Node first = null;
    private int pushCount = 0;
    private int popCount = 0;

    private class Node {
        Item item = null;
        Node next = null;
    }

    public boolean isEmpty() {
        return N == 0;
    }

    public int size() {
        return N;
    }

    public void push( Item item ) {
        Node oldFirst = first;
        first = new Node();
        first.item = item;
        first.next = oldFirst;
        ++N;
    }

    public Item pop() {
        Item item = first.item;
        first = first.next;
        --N;
        return item;
    }

    public Iterator< Item > iterator() {
        return new StackIterator();
    }

    private class StackIterator implements Iterator< Item > {
        private int iterPushCount = 0;
        private int iterPopCount = 0;
        private Node current = first;

        public StackIterator() {
            iterPushCount = pushCount;
            iterPopCount = popCount;
        }

        public boolean hasNext() {
            if ( ( iterPushCount != pushCount ) || ( iterPopCount != popCount ) ) {
                throw new ConcurrentModificationException();
            }
            return current != null;
        }

        public Item next() {
            if ( ( iterPushCount != pushCount ) || ( iterPopCount != popCount ) ) {
                throw new ConcurrentModificationException();
            }

            Item item = current.item;
            current = current.next;
            return item;
        }
    }

    public static void main( String[] args ) {

    }
}
