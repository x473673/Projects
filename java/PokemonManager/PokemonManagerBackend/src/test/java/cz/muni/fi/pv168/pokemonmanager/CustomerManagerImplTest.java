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

import org.junit.After;
import org.junit.AfterClass;
import org.junit.Assert;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.fail;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;

/**
 *
 * @author Matous Trnka
 */
public class CustomerManagerImplTest {
    
    private CustomerManagerImpl manager;
    private Customer validCustomer;
    private Customer nullIdCustomer;
    private Customer invalidCustomer;
    private static final Logger logger = Logger.getLogger(
            CustomerManagerImpl.class.getName());
    private EmbeddedDataSource ds;
    
    @Before
    public void setUp(){
        ds = new EmbeddedDataSource ();
        //ds.setDatabaseName("C:\\Users\\mutinar\\AppData\\Roaming\\NetBeans\\Derby\\pokemonReservationDatabase");
        ds.setDatabaseName("C:\\Users\\trnka\\AppData\\Roaming\\NetBeans\\Derby\\pokemonReservationDatabase");
        
        createTables(ds);
        manager = new CustomerManagerImpl(ds);
        validCustomer = new Customer();
        validCustomer.setName("Robert");
        
        
        nullIdCustomer = new Customer();
        nullIdCustomer.setName("Robert");
        
        manager.createCustomer(validCustomer);
        
        invalidCustomer = new Customer();
    }
    
    @After
    public void setDown(){
        dropTables(ds);
    }
    
    @Test (expected = IllegalArgumentException.class)
    public void testNullCustomer(){
        manager.createCustomer(null);
    }
    
    @Test (expected = IllegalEntityException.class)
    public void testAssignedId(){
        manager.createCustomer(validCustomer);
    }
    
    @Test (expected = ValidationException.class)
    public void testNullName(){
        manager.createCustomer(invalidCustomer);
    }
    
    @Test
    public void testCreatingCustomers(){
        Assert.assertNotNull(validCustomer);
        Assert.assertNotNull(validCustomer.getId());
        assertEquals(nullIdCustomer.getName(), validCustomer.getName());
    }
   
    
    @Test (expected = IllegalArgumentException.class)
    public void testNullId(){
        manager.getCustomer(null);
    }
    
    @Test
    public void getRightCustomer(){
        Long customerId = validCustomer.getId();
        assertEquals(validCustomer, manager.getCustomer(customerId));
        Assert.assertNull(manager.getCustomer(customerId+1));
    }
    
    @Test (expected = IllegalArgumentException.class)
    public void updateTestNullCustomer(){
        manager.updateCustomer(null);
    }
    
    @Test (expected = IllegalEntityException.class)
    public void updateTestNullId(){
        manager.updateCustomer(nullIdCustomer);
    }
    
    @Test (expected = IllegalEntityException.class)
    public void updateTestMissingInDb(){
        Customer secondCustomer = new Customer();
        secondCustomer.setId(validCustomer.getId()+1);
        secondCustomer.setName("Richard");
        manager.updateCustomer(secondCustomer);
    }
    
    @Test (expected = ValidationException.class)
    public void updateTestNullName(){
        Customer nonameCustomer = validCustomer;
        nonameCustomer.setName(null);
        manager.updateCustomer(nonameCustomer);
    }
    
    @Test
    public void testRightUpdate(){
        Customer changedCustomer = validCustomer;
        changedCustomer.setName("Rupert");
        manager.updateCustomer(changedCustomer);
        Customer rightCustomer = manager.getCustomer(validCustomer.getId());
        Assert.assertNotNull(rightCustomer);
        Assert.assertNotNull(rightCustomer.getId());
        assertEquals(rightCustomer.getName(),"Rupert");
    }
    
    @Test (expected = IllegalArgumentException.class)
    public void deleteTestNullCustomer(){
        manager.deleteCustomer(null);
    }
    
    @Test (expected = IllegalEntityException.class)
    public void deleteTestNullId(){
        manager.deleteCustomer(nullIdCustomer);
    }
    
    @Test (expected = IllegalEntityException.class)
    public void deleteTestMissingInDb(){ 
        Customer secondCustomer = validCustomer;
        secondCustomer.setId(validCustomer.getId()+1);
        manager.deleteCustomer(secondCustomer);
    }
    
    @Test (expected = IllegalEntityException.class)
    public void deleteTestIncorrectInDb(){ 
        Customer secondCustomer = validCustomer;
        secondCustomer.setName("Roman");
        manager.deleteCustomer(secondCustomer);
    }
   
    
    @Test
    public void testRightDelete(){
        manager.deleteCustomer(validCustomer);
        Assert.assertNull(manager.getCustomer(validCustomer.getId()));
    }
    
    @Test
    public void testFindAllCustomer(){
        List<Customer> list = manager.findAllCustomer();
        assertThat(list).containsOnly(validCustomer);
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
