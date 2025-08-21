import java.io.*;
import java.sql.*;
import java.util.*;
import oracle.jdbc.driver.*;

public class Student{
    static Connection con;
    static Statement stmt;

    public static void main(String argv[]){
        connectToDatabase();    
        
    }

    public static void databaseDriver(){
        Scanner myObj = new Scanner(System.in);
        String inputString = myObj.nextLine();
        while(inputString != "4"){
            inputString = myObj.nextLine();
            System.out.println("1. View table contents/n2. Search by PUBLICATIONID/n3.Update URL by PUBLICATIONID/n4. Exit");
            switch(inputString) {
                case "1":
                    databaseDump();
                    break;
                case "2":
                    databaseSearch();
                    break;
                case "3":
                    break;
                case "4":
                    System.out.println("Exiting Program. Have a nice day!");
                    myObj.close();
                    return;
                default:
                    System.out.println("[ERROR 1] Invalid option. Please try again.");
            }   
        }
        myObj.close();
        return;
    }

    public static void databaseDump(){
        Scanner myObj = new Scanner(System.in);
        String inputString = myObj.nextLine();
        System.out.println("Which would you like to see? Select the corresponding number./n/t1) Publications/n/t2)Authors");
        try{
            Integer input = Integer.valueOf(inputString);
            if(input == 1 || input == 2){
                //printOutput(input);
                myObj.close();
                return;
            }   
            else{
                System.out.println("[ERROR 2] Invalid input.");
                databaseDump();                
            }                 
        }
        catch (NumberFormatException ex){
            System.out.println("[ERROR 2] Invalid input.");
            databaseDump();
        }
    }

    public static void databaseSearch(){
        Scanner myObj = new Scanner(System.in);
        String inputString = myObj.nextLine();
        System.out.println("Please enter the PUBLICATIONID:");
        try{
            Integer number = Integer.valueOf(inputString);
            //locateID(number); 
            myObj.close();
            return;                      
        }
        catch (NumberFormatException ex){
            System.out.println("[ERROR 2] Invalid input.");
            databaseSearch();
        }
    }

    public static void databaseUpdate(){


        Scanner myObj = new Scanner(System.in);
        String inputString = myObj.nextLine();
        System.out.println("Please enter the filepath to url.csv:");
        //check if file is in directory
        //prompt for id
        //check if id holds, else prompt again or allow them to exit.
    }

    public static void connectToDatabase(){
	String driverPrefixURL="jdbc:oracle:thin:@";
	String jdbc_url="artemis.vsnet.gmu.edu:1521/vse18c.vsnet.gmu.edu";
	
        // IMPORTANT: DO NOT PUT YOUR LOGIN INFORMATION HERE. INSTEAD, PROMPT USER FOR HIS/HER LOGIN/PASSWD
        //Scanner sc= new Scanner(System.in);
        //prompt for user
        String username="nlocklea";
        //String user= sc.nextLine();
        //prompt for password
        String password="oolselty";
	    //String pass= sc.nextLine();
        try{
	    //Register Oracle driver
            DriverManager.registerDriver(new oracle.jdbc.driver.OracleDriver());
        } catch (Exception e) {
            System.out.println("Failed to load JDBC/ODBC driver.");
            return;
        }

       try{
            System.out.println(driverPrefixURL+jdbc_url);
            con=DriverManager.getConnection(driverPrefixURL+jdbc_url, username, password);
            DatabaseMetaData dbmd=con.getMetaData();
            stmt=con.createStatement();

            System.out.println("Connected.");

            if(dbmd==null){
                System.out.println("No database meta data");
            }
            else {
                System.out.println("Database Product Name: "+dbmd.getDatabaseProductName());
                System.out.println("Database Product Version: "+dbmd.getDatabaseProductVersion());
                System.out.println("Database Driver Name: "+dbmd.getDriverName());
                System.out.println("Database Driver Version: "+dbmd.getDriverVersion());
                databaseDriver();
            }
        }catch( Exception e) {e.printStackTrace();}

    }// End of connectToDatabase()
}// End of class

