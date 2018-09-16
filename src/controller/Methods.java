/******************************************************************\
 * Class Methods, modify the interface components
 * Author: Daniel Amador Salas
 * Created: 27/08/2018.
\******************************************************************/
package controller;

import java.awt.Color;
import java.awt.Font;
import java.awt.GridLayout;
import javax.swing.JPanel;
import model.btnGrid;


public class Methods {
    // Instance of class connection.
    Main connector = new Main();
    int number=0;
    // Categories chairs.
    btnGrid[][] camelot,avalon,shambhala;
    // Colors for each zone.
    String[] colors= {"83bb40","e65224","ebc700","00c2fa"};
    /**************************************************************************\
     * Create 4 zones with 20 chairs for each category.
     * @param pane will containt the zones
     * @return a matrix with the category's elements 
     \*************************************************************************/
    public btnGrid[][] fillZone(JPanel pane){
        btnGrid bMatriz[][] = new btnGrid[4][20];
        // Change default layout by gridlayout.
        pane.setLayout(new GridLayout(4,20)); 
        for(int f=0;f<4;f++)
            for(int c=0;c<20;c++){
                bMatriz[f][c] = new btnGrid();
                bMatriz[f][c].setBackground(new Color(Integer.parseInt(colors[f], 16 )));
                //pane.setBounds(140,15,270,300);
                pane.add(bMatriz[f][c]);
            }
        // Call the method to assign the numbers.
        setNumbers(bMatriz);
        return bMatriz;
    }
    /**************************************************************************\
     * Method that call to fillzone 
     * @param camelot
     * @param avalon
     * @param shambhala 
    \**************************************************************************/
    public void fillZones(JPanel camelot,JPanel avalon,JPanel shambhala){
        this.camelot=fillZone(camelot);
        this.avalon=fillZone(avalon);
        this.shambhala=fillZone(shambhala);
    }
    /**************************************************************************\
     * This method set new number for each button in the interface.
     * @param grid matrix
     * @return void
    \**************************************************************************/
    public void setNumbers(btnGrid[][] grid){
        for (int i = 0; i < 4; i++) {
            if(i==1||i==3)
                for (int j = 0; j < 20; j++) {
                    grid[i][j].number=number;
                    grid[i][j].setText(""+number);
                    grid[i][j].setFont(new Font("Arial", Font.PLAIN, 8));
                    number++;
                }
            else
                for (int j = 19; j >= 0; j--) {
                    grid[i][j].number=number;
                    grid[i][j].setText(""+number);
                    grid[i][j].setFont(new Font("Arial", Font.PLAIN, 8));
                    number++;
                }
            
        }
    }
    /**************************************************************************\
     * Method thar call the C file to get the chairs bought number.
     * Receive.
     * @chairs number of chairs to buy.
     * @name category's name.
     * @frozen number of chairs frozen.
     * @return void.
    \**************************************************************************/
    void buyTickets(int chairs, String name,int frozen) {
        int chair[]= connector.mains(chairs,name,frozen);
        System.out.println("Entro");
        if(name=="Camelot")
            buy(chair, camelot);
        else if(name=="Avalon")
            buy(chair, avalon);
        else if(name=="Shambhala")
            buy(chair, shambhala);
       
    }
    /**************************************************************************\
     * Search the chairs bought to change the state.
     * Receive:
     * @param chair // List with the number of the chairs bought.
     * @param matrix  // The category matrix.
    \**************************************************************************/
    void buy(int chair[],btnGrid matrix[][]){
        
        for (int j = 0; j < chair.length; j++) 
            for (int k = 0; k < 4; k++) 
                for (int l = 0; l < 20; l++)
                    if(matrix[k][l].number==chair[j])
                        matrix[k][l].setBackground(Color.BLACK);
    }
    void resetColors(){
         for (int i = 0; i <4; i++) 
            for (int j = 0; j < 20; j++) {
                camelot[i][j].setBackground(new Color(Integer.parseInt(colors[i], 16 )));
                avalon[i][j].setBackground(new Color(Integer.parseInt(colors[i], 16 )));
                shambhala[i][j].setBackground(new Color(Integer.parseInt(colors[i], 16 )));
            }
         
    }
    public int fillBoughtChairs(int percent){
        System.out.println(percent);
         for (int i = 0; i < 4; i++) {
           if(i==1||i==3)
               for (int j = 0; j < 20; j++) { 
                    if(percent>0){
                        camelot[i][j].setBackground(Color.gray);
                        avalon[i][j].setBackground(Color.gray);
                        shambhala[i][j].setBackground(Color.gray);
                        percent--;
                    }else
                        return 0;
               }
           else
               for (int j = 19; j >= 0; j--) {
                   if(percent>0){
                        camelot[i][j].setBackground(Color.gray);
                        avalon[i][j].setBackground(Color.gray);
                        shambhala[i][j].setBackground(Color.gray);
                        percent--;
                    }else
                       return 0;
                   
               }

       }
         return 0;
    }
}
