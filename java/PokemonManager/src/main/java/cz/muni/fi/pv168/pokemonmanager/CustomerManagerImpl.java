/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package cz.muni.fi.pv168.pokemonmanager;

import cz.muni.fi.pv168.exceptions.DBUtils;
import cz.muni.fi.pv168.exceptions.IllegalEntityException;
import cz.muni.fi.pv168.exceptions.ServiceFailureException;
import cz.muni.fi.pv168.exceptions.ValidationException;
import java.sql.*;
import java.util.ArrayList;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.sql.DataSource;


public class CustomerManagerImpl implements CustomerManager {

    private DataSource ds;
    private static final Logger logger = Logger.getLogger(
            CustomerManagerImpl.class.getName());       //?
    
    public CustomerManagerImpl(DataSource ds) {
        this.ds = ds;
    }
    
    private void checkDataSource() {
        if (ds == null) {
            throw new IllegalStateException("DataSource is not set");
        }
    }
    
    private void validate(Customer customer) {
        if (customer == null) {
            throw new IllegalArgumentException("customer is null");
        }
        if (customer.getName() == null) {
            throw new ValidationException("name is null");
        }
    }
    
    @Override
    public void createCustomer(Customer customer) throws ServiceFailureException, ValidationException, IllegalEntityException {
        Connection conn = null;
        if (customer == null) {
            throw new IllegalArgumentException("customer is null");
        }
        if (customer.getId() != null) {
            throw new IllegalEntityException("id allready assigned");
        }
        checkDataSource();
        validate(customer);
        try{
            conn = ds.getConnection();
            PreparedStatement ps = conn.prepareStatement("INSERT INTO CUSTOMER (name) VALUES (?)",Statement.RETURN_GENERATED_KEYS);
            ps.setString(1, customer.getName());
            ps.executeUpdate();
            ResultSet keys = ps.getGeneratedKeys(); //?
            if(keys.next()){
                long key = keys.getLong(1);
                customer.setId(key);
            }
        } catch (SQLException ex) {   
            String msg = "Error executing insert: ";//?
            logger.log(Level.SEVERE, msg, ex);
            throw new ServiceFailureException(msg, ex);
        }finally{
            if(conn !=null){
                try {
                        conn.close();
                    } catch (SQLException ex) {
                        logger.log(Level.SEVERE, "Error closing connection: ", ex);
                    }
            }
        }
    }

    @Override
    public Customer getCustomer(Long id) throws ServiceFailureException {
        checkDataSource();
        if (id == null) {
            throw new IllegalArgumentException("id is null");
        }
        Connection conn = null;
        try {
            conn = ds.getConnection();
            PreparedStatement ps = conn.prepareStatement(
                    "SELECT id, name FROM customer WHERE id = ?");
            ps.setLong(1, id);
            return executeQueryForSingleCustomer(ps);
        } catch (SQLException ex) {
            String msg = "Error when getting customer with id = " + id + " from DB";
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
    
    
    static Customer executeQueryForSingleCustomer(PreparedStatement st) throws SQLException, ServiceFailureException {
    ResultSet rs = st.executeQuery();
        if (rs.next()) {
            Customer result = rowToCustomer(rs);                
            if (rs.next()) {
                throw new ServiceFailureException(
                        "Internal integrity error: more bodies with the same id found!");
            }
            return result;
        } else {
            return null;
        }
    }
        
        static private Customer rowToCustomer(ResultSet rs) throws SQLException {
        Customer result = new Customer();
        result.setId(rs.getLong("id"));
        result.setName(rs.getString("name"));
        return result;
    }

    @Override
    public void updateCustomer(Customer customer) throws ServiceFailureException, ValidationException, IllegalEntityException {
        checkDataSource();
        validate(customer);
        
        
        if (customer == null) {
            throw new IllegalArgumentException("customer is null");
        }
        if (customer.getId() == null) {
            throw new IllegalEntityException("customer id is null");
        }        
        Connection conn = null;
        PreparedStatement ps = null;
        try {
            conn = ds.getConnection();          
            ps = conn.prepareStatement(
                    "UPDATE customer SET name = ? WHERE id = ?");
            ps.setString(1, customer.getName());
            ps.setLong(2, customer.getId());
            int count = ps.executeUpdate();
            DBUtils.checkUpdatesCount(count, customer, false);
        } catch (SQLException ex) {
            String msg = "Error when updating customer in the db";
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


    @Override
    public void deleteCustomer(Customer customer) throws ServiceFailureException, IllegalEntityException {
        checkDataSource();
        if (customer == null) {
            throw new IllegalArgumentException("customer is null");
        }        
        if (customer.getId() == null) {
            throw new IllegalEntityException("customer id is null");
        }        
        Customer dbCustomer = getCustomer(customer.getId());     
        if (!customer.equals(dbCustomer)) {
            throw new IllegalEntityException("customer is incorrect in db");
        }        
        Connection conn = null;
        PreparedStatement ps = null;
        try {
            conn = ds.getConnection();
            ps = conn.prepareStatement("DELETE FROM customer WHERE id = ?");
            ps.setLong(1, customer.getId());

            int count = ps.executeUpdate();
            DBUtils.checkUpdatesCount(count, customer, false);
        } catch (SQLException ex) {
            String msg = "Error when deleting customer from the db";
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


    @Override
    public List<Customer> findAllCustomer() throws ServiceFailureException {
        checkDataSource();
        Connection conn = null;
        try {
            conn = ds.getConnection();
            PreparedStatement ps = conn.prepareStatement(
                    "SELECT id, name FROM customer");
            ResultSet rs = ps.executeQuery();
            List<Customer> customers = new ArrayList<>();
            while(rs.next()) {
                Customer customer = new Customer();
                customer.setId(rs.getLong("id"));
                customer.setName(rs.getString("name"));
                customers.add(customer);
            }
            return customers;
        } catch (SQLException ex) {
            String msg = "Error when getting all customer from DB";
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
