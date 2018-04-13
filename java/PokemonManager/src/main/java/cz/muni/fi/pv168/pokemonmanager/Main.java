/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package cz.muni.fi.pv168.pokemonmanager;

import cz.muni.fi.pv168.exceptions.ServiceFailureException;
import org.apache.commons.dbcp2.BasicDataSource;
import java.sql.Connection;
import java.sql.Date;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.sql.Statement;
import java.sql.Timestamp;
import java.time.LocalDateTime;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.sql.DataSource;
import org.apache.derby.jdbc.EmbeddedDataSource;
import org.apache.derby.jdbc.EmbeddedDriver;



/**
 *
 * @author trnka
 *
 *
 *
 */

public class Main {

    private static final Logger logger = Logger.getLogger(
            CustomerManagerImpl.class.getName());
    
    
    public static DataSource createMemoryDatabase() {
        BasicDataSource bds = new BasicDataSource();
        //set JDBC driver and URL
        bds.setDriverClassName(EmbeddedDriver.class.getName());
        bds.setUrl("jdbc:derby:memory:pokemonDB;create=true");
        //populate db with tables and data
        createTables(bds);
        return bds;
    }
    
    
    public static DataSource createStorageDatabase() {
        
        EmbeddedDataSource ds = new EmbeddedDataSource ();
        //ds.setDatabaseName("C:\\Users\\trnka\\AppData\\Roaming\\NetBeans\\Derby\\pokemonReservationDatabase");
        ds.setDatabaseName("C:\\Users\\mutinar\\AppData\\Roaming\\NetBeans\\Derby\\pokemonReservationDatabase");
        createTables(ds);
      
        
        return ds;

    }
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        
        logger.info("zaciname");

        DataSource dataSource = createStorageDatabase();
        PokemonManager pokemonManager = new PokemonManagerImpl(dataSource);

        List<Pokemon> allPokemons = pokemonManager.findAllPokemon();
        System.out.println("allPokemons = " + allPokemons);
        
        
        /*
        // TODO code application logic here
        System.out.println("Hello, World");
        EmbeddedDataSource ds = new EmbeddedDataSource ();
        //ds.setDatabaseName("C:\\Users\\trnka\\AppData\\Roaming\\NetBeans\\Derby\\pokemonReservationDatabase");
        ds.setDatabaseName("C:\\Users\\mutinar\\AppData\\Roaming\\NetBeans\\Derby\\pokemonReservationDatabase");
      
      
        createTables(ds);
        ReservationManager manager = new ReservationManagerImpl(ds);
        CustomerManager cusManager = new CustomerManagerImpl(ds);
        PokemonManager pokManager = new PokemonManagerImpl(ds);

        Customer customer = new Customer();
        customer.setName("Bedrich");
        cusManager.createCustomer(customer);

        Pokemon pokemon = new Pokemon();
        pokemon.setName("Psyduck");
        pokemon.setHealth(20);
        pokemon.setPower(20);
        pokManager.createPokemon(pokemon);

        System.out.println(pokemon.getId());
        System.out.println(customer.getId());
        System.out.println();

        Reservation reservation = new Reservation();
        reservation.setFrom(LocalDateTime.of(2018,  11, 2, 13, 00));
        
        System.out.println(reservation.getFrom());
        System.out.println(Timestamp.valueOf(reservation.getFrom()));
        System.out.println();
                
        reservation.setTo(LocalDateTime.of(2018,  12, 2, 13, 00));
        System.out.println(reservation.getTo());
        System.out.println(Timestamp.valueOf(reservation.getTo()));
        
        reservation.setCustomer(customer);
        reservation.setPokemon(pokemon);
        manager.createReservation(reservation);
        
        
        reservation.setFrom(LocalDateTime.of(2018,  4, 2, 15, 00));
        reservation.setTo(LocalDateTime.of(2018,  5, 2, 13, 00));;
       
        manager.updateReservation(reservation);
        
        System.out.println(reservation.getId());
        dropTables(ds);
     */
    }
   

    private static void createTables(DataSource ds){
        Connection conn = null;
        try {
            conn = ds.getConnection();
        Statement ps = conn.createStatement();
        ps.execute("CREATE TABLE \"CUSTOMER\" (\n" +
"    \"ID\" INT NOT NULL PRIMARY KEY GENERATED ALWAYS AS IDENTITY,\n" +
"    \"NAME\" VARCHAR(63) NOT NULL)");
            ps.execute("CREATE TABLE \"POKEMON\" (\n" +
"    \"ID\" INT NOT NULL PRIMARY KEY GENERATED ALWAYS AS IDENTITY,\n" +
"    \"NAME\" VARCHAR(63) NOT NULL,\n" +
"    \"POWER\" INT NOT NULL,\n" +
"    \"HEALTH\" INT NOT NULL)");
             ps.execute("CREATE TABLE \"RESERVATION\" (\n" +
"    \"ID\" INT NOT NULL PRIMARY KEY GENERATED ALWAYS AS IDENTITY,\n" +
"    \"FROMDATE\" TIMESTAMP NOT NULL,\n" +
"    \"TODATE\" TIMESTAMP NOT NULL,\n" +
"    \"POKEMONID\" INT NOT NULL,\n" +
"     \"CUSTOMERID\" INT NOT NULL,\n" +
      "CONSTRAINT POKEMONFK FOREIGN KEY (POKEMONID) REFERENCES POKEMON (ID),\n"+
      "CONSTRAINT CUSTOMERFK FOREIGN KEY (CUSTOMERID) REFERENCES CUSTOMER (ID))"
             );
        
        } catch (SQLException ex) {
            String msg = "Error when creating tables in DB";
            logger.log(Level.SEVERE, msg, ex);
            throw new ServiceFailureException(msg, ex);
        } finally {
            if(conn !=null){
                try {
                        conn.close();
                    } catch (SQLException ex) {
                        logger.log(Level.SEVERE, "Error closing connection: ", ex);
                    }
            }
        }
    }
  private static void dropTables(DataSource ds){
        Connection conn = null;
        try {
            conn = ds.getConnection();
            Statement ps = conn.createStatement();
            ps.execute("DROP TABLE \"RESERVATION\"");
            ps.execute("DROP TABLE \"CUSTOMER\"");
            ps.execute("DROP TABLE \"POKEMON\"");
        } catch (SQLException ex) {
            String msg = "Error when dropping tables in DB";
            logger.log(Level.SEVERE, msg, ex);
            throw new ServiceFailureException(msg, ex);
        } finally {
            if(conn !=null){
                try {
                        conn.close();
                    } catch (SQLException ex) {
                        logger.log(Level.SEVERE, "Error closing connection: ", ex);
                    }
            }
        }
           
    }

}
