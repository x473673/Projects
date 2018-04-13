/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package cz.muni.fi.pv168.pokemonmanager;

import cz.muni.fi.pv168.exceptions.IllegalEntityException;
import cz.muni.fi.pv168.exceptions.ServiceFailureException;
import cz.muni.fi.pv168.exceptions.ValidationException;
import java.sql.Connection;
import java.sql.SQLException;
import java.sql.Statement;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.sql.DataSource;
import org.apache.derby.jdbc.EmbeddedDataSource;
import static org.assertj.core.api.Assertions.assertThat;
import org.junit.After;
import org.junit.AfterClass;
import org.junit.Assert;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;
import static org.junit.Assert.*;

/**
 *
 * @author mutinar
 */
public class ReservationManagerImplTest {
    
    private ReservationManagerImpl manager;
    private CustomerManagerImpl cusManager;
    private PokemonManagerImpl pokManager;
    private Reservation reservation;
    
    private Reservation invalidReservation;
    private Customer customer;
    private Pokemon pokemon;
    private Customer invalidCustomer;
    private Pokemon invalidPokemon;
    
    private static final Logger logger = Logger.getLogger(
            CustomerManagerImpl.class.getName());
    private EmbeddedDataSource ds;
    
    @Before
    public void setUp(){
        
        ds = new EmbeddedDataSource ();
        //ds.setDatabaseName("C:\\Users\\mutinar\\AppData\\Roaming\\NetBeans\\Derby\\pokemonReservationDatabase");
        ds.setDatabaseName("C:\\Users\\trnka\\AppData\\Roaming\\NetBeans\\Derby\\pokemonReservationDatabase");
        
        
        createTables(ds);
        manager = new ReservationManagerImpl(ds);
        cusManager = new CustomerManagerImpl(ds);
        pokManager = new PokemonManagerImpl(ds);
        
        customer = new Customer();
        customer.setName("Bedrich");
        cusManager.createCustomer(customer);
        
        pokemon = new Pokemon();
        pokemon.setName("Psyduck");
        pokemon.setHealth(20);
        pokemon.setPower(20);
        pokManager.createPokemon(pokemon);
        
        reservation = new Reservation();
        reservation.setFrom(LocalDateTime.of(2018,  11, 2, 13, 00));
        reservation.setTo(LocalDateTime.of(2018,  12, 2, 13, 00));
        reservation.setCustomer(customer);
        reservation.setPokemon(pokemon);
        manager.createReservation(reservation);
        
        invalidReservation = new Reservation();
        invalidReservation.setFrom(LocalDateTime.of(2017,  11, 2, 13, 00));
        invalidReservation.setTo(LocalDateTime.of(2017,  12, 2, 13, 00));
        invalidReservation.setCustomer(customer);
        invalidReservation.setPokemon(pokemon);
        
        
        invalidCustomer= new Customer();
        invalidPokemon = new Pokemon();
        
    }
    
    @After
    public void setDown(){
        dropTables(ds);
    }
    
    
    @Test (expected = IllegalArgumentException.class)
    public void testNullReservation(){
        manager.createReservation(null);
    }
    
    @Test (expected = IllegalEntityException.class)
    public void testAssignedId(){
        manager.createReservation(reservation);
    }
   
    @Test (expected = ValidationException.class)
    public void testNullCustomer(){
        invalidReservation.setCustomer(null);
        manager.createReservation(invalidReservation);
    }
    
    @Test (expected = ValidationException.class)
    public void testNullIdCustomer(){
        invalidReservation.getCustomer().setId(null);
        manager.createReservation(invalidReservation);
    }
   
     
    
    @Test (expected = ValidationException.class)
    public void testNullPokemon(){
        invalidReservation.setPokemon(null);
        manager.createReservation(invalidReservation);
    }
    
    @Test (expected = ValidationException.class)
    public void testNullIdPokemon(){
        invalidReservation.getPokemon().setId(null);
        manager.createReservation(invalidReservation);
    }

    @Test (expected = ValidationException.class)
    public void testNullTo(){
        invalidReservation.setTo(null);
        manager.createReservation(invalidReservation);
    }
     
    @Test (expected = ValidationException.class)
    public void testNullFrom(){
        invalidReservation.setFrom(null);
        manager.createReservation(invalidReservation);
    }
     
    @Test (expected = ValidationException.class)
    public void testInvalidDate(){
        invalidReservation.setFrom((LocalDateTime.of(2017,  11, 2, 13, 00)));
        invalidReservation.setTo(LocalDateTime.of(2016,  11, 2, 13, 00));
        manager.createReservation(invalidReservation);
    }
    
    @Test
    public void testCreatingReservations(){
        Assert.assertNotNull(reservation);
        Assert.assertNotNull(reservation.getId());
        assertEquals(reservation.getCustomer(), customer);
        assertEquals(reservation.getPokemon(), pokemon);
        assertEquals(reservation.getTo(),LocalDateTime.of(2018,  12, 2, 13, 00));
        assertEquals(reservation.getFrom(), LocalDateTime.of(2018,  11, 2, 13, 00));
    }
    
    @Test (expected = IllegalArgumentException.class)
    public void testNullId(){
        manager.getReservation(null);
    }
    
    @Test
    public void getRightReservation(){
        assertEquals(reservation, manager.getReservation(reservation.getId()));
        Assert.assertNull(manager.getReservation(reservation.getId()+1));
    }
    
    @Test (expected = IllegalArgumentException.class)
    public void updateTestNullReservation(){
        manager.updateReservation(null);
    }
    
    @Test (expected = IllegalEntityException.class)
    public void updateTestNullId(){
        manager.updateReservation(invalidReservation);
    }
    
    
    @Test (expected = ValidationException.class)
    public void updateTestNullTo(){
        Reservation secondReservation = reservation;
        secondReservation.setTo(null);
        manager.updateReservation(secondReservation);
    }
    
    @Test (expected = ValidationException.class)
    public void updateTestNullFrom(){
        Reservation secondReservation = reservation;
        secondReservation.setFrom(null);
        manager.updateReservation(secondReservation);
    }
    
    @Test (expected = ValidationException.class)
    public void updateTestInvalidDate(){
        reservation.setFrom((LocalDateTime.of(2017,  11, 2, 13, 00)));
        reservation.setTo(LocalDateTime.of(2016,  11, 2, 13, 00));
        manager.updateReservation(reservation);
    }
    
    @Test (expected = ValidationException.class)
    public void updateTestNullCustomer(){
        Reservation secondReservation = reservation;
        secondReservation.setCustomer(null);
        manager.updateReservation(secondReservation);
    }
    
    @Test (expected = ValidationException.class)
    public void updateTestNullIdCustomer(){
        Reservation secondReservation = reservation;
        secondReservation.getCustomer().setId(null);
        manager.updateReservation(secondReservation);
    }
   
    
    @Test (expected = ValidationException.class)
    public void updateTestNullPokemon(){
        Reservation secondReservation = reservation;
        secondReservation.setPokemon(null);
        manager.updateReservation(secondReservation);
    }
    
    @Test (expected = ValidationException.class)
    public void updateTestNullIdPokemon(){
        Reservation secondReservation = reservation;
        secondReservation.getPokemon().setId(null);
        manager.updateReservation(secondReservation);
    }
    
     
    @Test
    public void testRightUpdate(){       
         
       
        reservation.setFrom(LocalDateTime.of(2018,  4, 2, 15, 00));
        reservation.setTo(LocalDateTime.of(2018,  5, 2, 13, 00));;
       
        manager.updateReservation(reservation);
        
        Reservation compareReservation = manager.getReservation(reservation.getId());
      
        Assert.assertNotNull(compareReservation);
        Assert.assertNotNull(compareReservation.getId());
        assertEquals(reservation.getTo(),compareReservation.getTo());
        assertEquals(reservation.getFrom(),compareReservation.getFrom());
        
      
    }

    @Test (expected = IllegalArgumentException.class)
    public void deleteTestNullReservation(){
        manager.deleteReservation(null);
    }
    
    @Test (expected = IllegalEntityException.class)
    public void deleteTestNullId(){
        manager.deleteReservation(invalidReservation);
    }
    
    @Test
    public void testRightDelete(){
        manager.deleteReservation(reservation);
        Assert.assertNull(manager.getReservation(reservation.getId()));
    }
    
    @Test
    public void testFindAllReservation(){
        List<Reservation> list = manager.findAllReservation();
        assertThat(list).containsOnly(reservation);
    }
    
    @Test (expected = IllegalEntityException.class)
    public void testFindNullCustomer(){
        manager.findCustomerReservation(null);
    }
    
    @Test (expected = IllegalEntityException.class)
    public void testFindNullIdCustomer(){
        manager.findCustomerReservation(invalidCustomer);
    }
    
    @Test
    public void testFindCustomerReservation(){

        assertThat(manager.findCustomerReservation(customer)).containsOnly(reservation);
        
        Customer changedCustomer = new Customer();
        changedCustomer.setName("franta");
        cusManager.createCustomer(changedCustomer);
        
        assertThat(manager.findCustomerReservation(changedCustomer)).isEmpty();
    }
    
    @Test (expected = IllegalArgumentException.class)
    public void testFindNullPokemon(){
        manager.findPokemonReservation(null);
    }
    
    @Test (expected = IllegalEntityException.class)
    public void testFindNullIdPokemon(){
        manager.findPokemonReservation(invalidPokemon);
    }
    
    @Test
    public void testFindPokemonReservation(){
        assertThat(manager.findPokemonReservation(pokemon)).containsOnly(reservation);
        
         Pokemon changedPokemon = new Pokemon();
        changedPokemon.setName("drtikol");
        changedPokemon.setHealth(20);
        changedPokemon.setPower(20);
        pokManager.createPokemon(changedPokemon);
        

        assertThat(manager.findPokemonReservation(changedPokemon)).isEmpty();
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

