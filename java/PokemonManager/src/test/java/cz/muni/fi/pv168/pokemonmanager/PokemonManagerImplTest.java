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
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.sql.DataSource;
import org.apache.derby.jdbc.EmbeddedDataSource;
import static org.assertj.core.api.Assertions.assertThat;
import static org.assertj.core.api.Assertions.assertThatThrownBy;
import org.junit.After;

import org.junit.Assert;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;
import org.junit.Before;
import org.junit.Test;

/**
 *
 * @author mutinar
 */
public class PokemonManagerImplTest {
    private PokemonManagerImpl manager;
    private Pokemon validPokemon;
    private Pokemon nullIdPokemon;
    private Pokemon invalidPokemon;
    private static final Logger logger = Logger.getLogger(
            PokemonManagerImpl.class.getName());
    private EmbeddedDataSource ds;
    
    @Before
    public void setUp(){
        ds = new EmbeddedDataSource ();
        ds.setDatabaseName("C:\\Users\\trnka\\AppData\\Roaming\\NetBeans\\Derby\\pokemonReservationDatabase");
        //ds.setDatabaseName("C:\\Users\\mutinar\\AppData\\Roaming\\NetBeans\\Derby\\pokemonReservationDatabase");
        
        createTables(ds);
        manager = new PokemonManagerImpl(ds);
        validPokemon = new Pokemon();
        validPokemon.setName("Psyduck");
        validPokemon.setHealth(100);
        validPokemon.setPower(14);
        
        
        nullIdPokemon = new Pokemon();
        nullIdPokemon.setName("Psyduck");
        nullIdPokemon.setHealth(100);
        nullIdPokemon.setPower(14);
        
        manager.createPokemon(validPokemon);
        
        invalidPokemon = new Pokemon();
    }
    
    @After
    public void setDown(){
        dropTables(ds);
    }
    
    @Test (expected = IllegalArgumentException.class)
    public void testNullPokemon(){
        manager.createPokemon(null);
    }
    
    @Test (expected = IllegalEntityException.class)
    public void testAssignedId(){
        manager.createPokemon(validPokemon);
    }
    
    @Test (expected = ValidationException.class)
    public void testNullName(){
        manager.createPokemon(invalidPokemon);
    }
    @Test (expected = ValidationException.class)
    public void testNegativeHealth(){
        nullIdPokemon.setHealth(-5);
        manager.createPokemon(nullIdPokemon);
    }
    @Test (expected = ValidationException.class)
    public void testNegativePower(){
        nullIdPokemon.setPower(-5);
        manager.createPokemon(nullIdPokemon);
    }
    
    @Test
    public void testCreatingPokemons(){
        Assert.assertNotNull(validPokemon);
        Assert.assertNotNull(validPokemon.getId());
        assertEquals(nullIdPokemon.getName(), validPokemon.getName());
        assertEquals(nullIdPokemon.getHealth(), validPokemon.getHealth());
        assertEquals(nullIdPokemon.getPower(), validPokemon.getPower());
    }
   
    
    @Test (expected = IllegalArgumentException.class)
    public void testNullId(){
        manager.getPokemon(null);
    }
    
    @Test
    public void getRightPokemon(){
        Long pokemonId = validPokemon.getId();
        assertEquals(validPokemon, manager.getPokemon(pokemonId));
        Assert.assertNull(manager.getPokemon(pokemonId+1));
    }
    
    @Test (expected = IllegalArgumentException.class)
    public void updateTestNullPokemon(){
        manager.updatePokemon(null);
    }
    
    @Test (expected = IllegalEntityException.class)
    public void updateTestNullId(){
        manager.updatePokemon(nullIdPokemon);
    }
    
    @Test (expected = IllegalEntityException.class)
    public void updateTestMissingInDb(){
        Pokemon secondPokemon = new Pokemon();
        secondPokemon.setId(validPokemon.getId()+1);
        secondPokemon.setName("Bulbasaur");
        manager.updatePokemon(secondPokemon);
    }
    
    @Test (expected = ValidationException.class)
    public void updateTestNullName(){
        Pokemon nonamePokemon = validPokemon;
        nonamePokemon.setName(null);
        manager.updatePokemon(nonamePokemon);
    }
    
    @Test (expected = ValidationException.class)
    public void updateTestNegativeHealth(){
        Pokemon nonamePokemon = validPokemon;
        nonamePokemon.setHealth(-5);
        manager.updatePokemon(nonamePokemon);
    }
    
    @Test (expected = ValidationException.class)
    public void updateTestNegativePower(){
        Pokemon nonamePokemon = validPokemon;
        nonamePokemon.setPower(-5);
        manager.updatePokemon(nonamePokemon);
    }
    
    @Test
    public void testRightUpdate(){
        Pokemon changedPokemon = validPokemon;
        changedPokemon.setName("Golduck");
        changedPokemon.setHealth(300);
        changedPokemon.setPower(30);
        manager.updatePokemon(changedPokemon);
        Pokemon rightPokemon = manager.getPokemon(validPokemon.getId());
        Assert.assertNotNull(rightPokemon);
        Assert.assertNotNull(rightPokemon.getId());
        assertTrue(rightPokemon.equals(changedPokemon));
    }
    
    @Test (expected = IllegalArgumentException.class)
    public void deleteTestNullPokemon(){
        manager.deletePokemon(null);
    }
    
    @Test (expected = IllegalEntityException.class)
    public void deleteTestNullId(){
        manager.deletePokemon(nullIdPokemon);
    }
    
    @Test (expected = IllegalEntityException.class)
    public void deleteTestMissingInDb(){ 
        Pokemon secondPokemon = validPokemon;
        secondPokemon.setId(validPokemon.getId()+1);
        manager.deletePokemon(secondPokemon);
    }
    
    @Test (expected = IllegalEntityException.class)
    public void deleteTestIncorrectInDb(){ 
        Pokemon secondPokemon = validPokemon;
        secondPokemon.setName("Meow");
        manager.deletePokemon(secondPokemon);
    }
   
    
    @Test
    public void testRightDelete(){
        manager.deletePokemon(validPokemon);
        Assert.assertNull(manager.getPokemon(validPokemon.getId()));
    }
    
    @Test
    public void testFindAllPokemon(){
        List<Pokemon> list = manager.findAllPokemon();
        assertThat(list).containsOnly(validPokemon);
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
