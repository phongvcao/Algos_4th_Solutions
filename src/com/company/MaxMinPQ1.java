package com.company;
import edu.princeton.cs.algs4.*;

public class MaxMinPQ1 {

    private static class Item {
        public Comparable value = null;
        public int maxPQIndex = -1;
        public int minPQIndex = -1;

        public int compareTo( Item other ) {
            return this.value.compareTo( other.value );
        }

        public String toString() {
            return "" + this.value;
        }
    }

    private Item[] maxPQ;
    private Item[] minPQ;
    private int maxN = 0;
    private int minN = 0;

    public MaxMinPQ1( int N ) {
        maxPQ = new Item[ N + 1 ];
        minPQ = new Item[ N + 1 ];
    }

    private boolean less( Item a, Item b ) {
        return a.compareTo( b ) == -1;
    }

    public int size() {
        return maxN;
    }

    public boolean isEmpty() {
        return size() == 0;
    }

    public static void main( String[] args ) {

    }
}
