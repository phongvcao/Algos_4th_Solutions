package com.company;
import edu.princeton.cs.algs4.*;

import javax.swing.*;
import java.util.Map;
import java.util.HashMap;

public class Parentheses {
    public static void main( String[] args ) {
        Stack< String > parenStack = new Stack< String >();
        boolean mismatch = false;
        Map< String, String > itemsDict = new HashMap< String, String >();
        itemsDict.put( "(", ")" );
        itemsDict.put( "{", "}" );
        itemsDict.put( "[", "]" );

        while ( !StdIn.isEmpty() ) {
            String item = StdIn.readString();

            // DEBUG
            // StdOut.println( "DEBUG: while loop: item: " + item );
            // END OF DEBUG

            if ( ( item.equals( "[" ) ) || ( item.equals( "(" ) ) || ( item.equals( "{" ) ) ) {
                parenStack.push( item );
            } else if ( ! parenStack.isEmpty() ) {
                String topItem = parenStack.peek();

                // DEBUG
                // StdOut.println( "DEBUG: topItem: " + topItem + " !!!" );
                // StdOut.println( "DEBUG: item: " + item + " !!!" );
                // END OF DEBUG

                if ( ! topItem.isEmpty() ) {
                    if ( item.equals( itemsDict.get( topItem ) ) ) {

                        // DEBUG
                        // StdOut.println( "DEBUG: topItem: " + topItem + " ( 0 )!!!" );
                        // StdOut.println( "DEBUG: item: " + item + " ( 0 )!!!" );
                        // END OF DEBUG

                        parenStack.pop();
                    } else {

                        // DEBUG
                        // StdOut.println( "DEBUG: topItem: " + topItem + "( 1 )!!!" );
                        // END OF DEBUG

                        if ( ( item.equals( "]" ) ) || ( item.equals( ")" ) ) || ( item.equals( "}" ) ) ) {

                            // DEBUG
                            // StdOut.println( "DEBUG: topItem: " + topItem + "( 2 )!!!" );
                            // END OF DEBUG

                            // StdOut.println( "FIRST MISMATCH: item: " + item );
                            mismatch = true;
                            break;
                        }
                    }
                }

            } else {
                if ( ( item.equals( "]" ) ) || ( item.equals( ")" ) ) || ( item.equals( "}" ) ) ) {
                    // StdOut.println( "SECOND MISMATCH" );
                    mismatch = true;
                    break;
                }
            }

            if ( item.contains( "EOF" ) ) {
                break;
            }
        }

        if ( ! parenStack.isEmpty() ) {
            // StdOut.println( "THIRD MISMATCH" );
            mismatch = true;
        }

        if ( mismatch ) {
            StdOut.println( "PARENTHESES MIS-MATCHED!!!" );
        } else {
            StdOut.println( "PARENTHESES MATCHED!!!" );
        }
    }
}
