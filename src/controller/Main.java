/*********************************************\
 * Connection controller, This class connect
 * java with C file
 * Author: Daniel Amador Salas
 * Created: 27/08/2018.
\*********************************************/
package controller;


public class Main {
    /*******************************************************************************\
    * Class connector, call the function in C that realize the allocation process
    * Receive: quantity of chairs, category's name and quantity of chairs to reserve
    * Return: a array with the numbers of chairs bought.
    \********************************************************************************/
    public int[] mains(int chairs,String category, int toReserve) {
        System.out.println(chairs+" C "+ category+" R "+toReserve);
       // Charge the library.
       System.loadLibrary("Connection"); 
       // Call the C method.
        
       return nativeGreeting(chairs,category,toReserve); 
    }
    /*
    public static void main(String[] arg){
        new Main().mains(6, "Camelot", 50);
    }*/
    // Interface that allow the connection with C.
    public native int[] nativeGreeting(int chairs,String name,int toReserve);
}
