package com.company;

public class TwoStacksSingleDeque< Item > {

    private Deque< Item > deque;

    public TwoStacksSingleDeque() {
        deque = new Deque< Item >();
    }

    public void pushLeft( Item item ) {
        deque.pushLeft( item );
    }

    public void pushRight( Item item ) {
        deque.pushRight( item );
    }

    public Item popLeft() {
        return deque.popLeft();
    }

    public Item popoRight() {
        return deque.popRight();
    }

    public static void main( String[] args ) {

    }
}
