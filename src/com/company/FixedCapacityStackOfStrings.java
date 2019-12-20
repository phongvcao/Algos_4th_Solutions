package com.company;

public class FixedCapacityStackOfStrings
{
    private String[] a; // stack entries
    private int N; // size
    public FixedCapacityStackOfStrings( int cap ) { a = new String[ cap ]; }
    public boolean isEmpty() { return N == 0; }
    public int size() { return N; }
    public void push( String item ) { a[ N++ ] = item; }
    public String pop() { return a[ --N ]; }
    public boolean isFull() { return N == a.length; }

    // Exercise 1.3.6
    public String peek() { return a[ N - 1 ]; }
}