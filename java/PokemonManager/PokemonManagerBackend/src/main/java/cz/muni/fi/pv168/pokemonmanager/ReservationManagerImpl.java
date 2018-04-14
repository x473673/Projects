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
import java.sql.Connection;
import java.sql.Date;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.sql.Timestamp;
import java.time.LocalDate;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.sql.DataSource;


public class ReservationManagerImpl implements ReservationManager {
    
    private static DataSource ds;
    private static final Logger logger = Logger.getLogger(
            PokemonManagerImpl.class.getName());       //?
    
    public ReservationManagerImpl(DataSource ds) {
        this.ds = ds;
    }
    
    private void checkDataSource() {
        if (ds == null) {
            throw new IllegalStateException("DataSource is not set");
        }
    }
    
    private void validate(Reservation reservation) {
        if (reservation == null) {
            throw new IllegalArgumentException("reservation is null");
        }
        if (reservation.getCustomer() == null) {
            throw new ValidationException("customer is null");
        }
        if (reservation.getPokemon() == null) {
            throw new ValidationException("pokemon is null");
        }
        if (reservation.getFrom()== null) {
            throw new ValidationException("from is null");
        }
        if (reservation.getTo()== null) {
            throw new ValidationException("to is null");
        }    
        if (reservation.getCustomer().getId() == null) {
            throw new ValidationException("customer id is null");
        }
        if (reservation.getPokemon().getId() == null) {
            throw new ValidationException("pokemon id is null");
        }
        if (reservation.getTo().isBefore(reservation.getFrom())) {
            throw new ValidationException("to is before from");
        }
    }
    
    
    @Override
    public void createReservation(Reservation reservation) throws ServiceFailureException, ValidationException, IllegalEntityException {
        Connection conn = null;
        checkDataSource();
        validate(reservation);
        if (reservation.getId()!=null) {
            throw new IllegalEntityException("ID is already assigned");
        }
        try{
            conn = ds.getConnection();
            PreparedStatement ps = conn.prepareStatement("INSERT INTO RESERVATION (FROMDATE, TODATE, POKEMONID, CUSTOMERID) VALUES (?, ?, ?, ?)",Statement.RETURN_GENERATED_KEYS);
            
            ps.setTimestamp(1, Timestamp.valueOf(reservation.getFrom()));
            ps.setTimestamp(2, Timestamp.valueOf(reservation.getTo()));
            ps.setLong(3, reservation.getPokemon().getId());
            ps.setLong(4, reservation.getCustomer().getId());
                ps.executeUpdate();
                ResultSet keys = ps.getGeneratedKeys(); //?
                if(keys.next()){
                    long key = keys.getLong(1);
                    reservation.setId(key);
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
    public Reservation getReservation(Long id) throws ServiceFailureException {
         checkDataSource();
        if (id == null) {
            throw new IllegalArgumentException("id is null");
        }
        Connection conn = null;
        try {
            conn = ds.getConnection();
            PreparedStatement ps = conn.prepareStatement(
                    "SELECT * FROM Reservation WHERE id = ?");
            ps.setLong(1, id);
            return executeQueryForSingleReservation(ps);
        } catch (SQLException ex) {
            String msg = "Error when getting Reservation with id = " + id + " from DB";
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
    
    static Reservation executeQueryForSingleReservation(PreparedStatement st) throws SQLException, ServiceFailureException {
        ResultSet rs = st.executeQuery();
        if (rs.next()) {  
            Reservation result = rowToReservation(rs);                
        if (rs.next()) {
            throw new ServiceFailureException(
                "Internal integrity error: more bodies with the same id found!");
        }
        return result;
    }else {
        return null;
    }
    }
    
    static private Reservation rowToReservation(ResultSet rs) throws SQLException {            
        Reservation result = new Reservation();
        result.setId(rs.getLong("id"));
        result.setFrom(rs.getTimestamp("Fromdate").toLocalDateTime());
        result.setTo(rs.getTimestamp("Todate").toLocalDateTime());
        
        
        
        Pokemon pokemon = new Pokemon();
        Customer customer = new Customer();
        
        PokemonManagerImpl pokemonManager = new PokemonManagerImpl(ds);
        pokemonManager.getPokemon(rs.getLong("pokemonId"));
        
        CustomerManagerImpl customerManager = new CustomerManagerImpl(ds);
        customerManager.getCustomer(rs.getLong("customerId"));
        
        
        result.setPokemon(pokemon);
        result.setCustomer(customer);
        return result;
    }

    @Override
    public void updateReservation(Reservation reservation) throws ServiceFailureException, ValidationException, IllegalEntityException {
        checkDataSource();
        validate(reservation);
        
        if (reservation.getId() == null) {
            throw new IllegalEntityException("reservation id is null");
        }        
        Connection conn = null;
        PreparedStatement ps = null;
        try {
            conn = ds.getConnection();          
            ps = conn.prepareStatement(
                    "UPDATE reservation SET FROMDATE = ?, todate = ?, pokemonId = ?, customerId = ? WHERE id = ?");
            ps.setTimestamp(1, Timestamp.valueOf(reservation.getFrom()));
            ps.setTimestamp(2, Timestamp.valueOf(reservation.getTo()));
            ps.setLong(3, reservation.getPokemon().getId());
            ps.setLong(4, reservation.getCustomer().getId());
            ps.setLong(5, reservation.getId());
            int count = ps.executeUpdate();
            DBUtils.checkUpdatesCount(count, reservation, false);
        } catch (SQLException ex) {
            String msg = "Error when updating reservation in the db";
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
    public void deleteReservation(Reservation reservation) throws ServiceFailureException, IllegalEntityException {
        checkDataSource();
        if (reservation == null) {
            throw new IllegalArgumentException("reservation is null");
        }        
        if (reservation.getId() == null) {
            throw new IllegalEntityException("reservation id is null");
        }        
        if (!this.findAllReservation().contains(reservation)) {
            throw new IllegalEntityException("reservation is not in DB");
        }      
        Connection conn = null;
        PreparedStatement ps = null;
        try {
            conn = ds.getConnection();
            ps = conn.prepareStatement("DELETE FROM Reservation WHERE id = ?");
            ps.setLong(1, reservation.getId());

            int count = ps.executeUpdate();
            DBUtils.checkUpdatesCount(count, reservation, false);
        } catch (SQLException ex) {
            String msg = "Error when deleting reservation from the db";
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
    public List<Reservation> findAllReservation() throws ServiceFailureException {
        checkDataSource();
        Connection conn = null;
        PreparedStatement st = null;
        try {
            conn = ds.getConnection();
            st = conn.prepareStatement(
                    "SELECT * FROM Reservation");
            return executeQueryForMultipleReservation(st);
        } catch (SQLException ex) {
            String msg = "Error when getting all reservations from DB";
            logger.log(Level.SEVERE, msg, ex);
            throw new ServiceFailureException(msg, ex);
        } finally {
            DBUtils.closeQuietly(conn, st);
        }          
    }
    
    static List<Reservation> executeQueryForMultipleReservation(PreparedStatement st) throws SQLException {
        ResultSet rs = st.executeQuery();
        List<Reservation> result = new ArrayList<Reservation>();
        while (rs.next()) {
            result.add(rowToReservation(rs));
        }
        return result;
    }

    @Override
    public List<Reservation> findCustomerReservation(Customer customer) throws ServiceFailureException, IllegalEntityException {
        
        if (customer == null) {
            throw new IllegalEntityException("reservation is null");
        }        
        if (customer.getId() == null) {
            throw new IllegalEntityException("reservation id is null");
        }       
        
        checkDataSource();
        Connection conn = null;
        PreparedStatement st = null;
        try {
            conn = ds.getConnection();
            st = conn.prepareStatement(
                    "SELECT * FROM Reservation WHERE customerId = ?");
            st.setLong(1, customer.getId());
            return executeQueryForMultipleReservation(st);
        } catch (SQLException ex) {
            String msg = "Error when getting all reservation of customer from DB";
            logger.log(Level.SEVERE, msg, ex);
            throw new ServiceFailureException(msg, ex);
        } finally {
            DBUtils.closeQuietly(conn, st);
        }          
    }

    @Override
    public List<Reservation> findPokemonReservation(Pokemon pokemon) throws ServiceFailureException, IllegalEntityException {
        
        if (pokemon == null) {
            throw new IllegalArgumentException("reservation is null");
        }        
        if (pokemon.getId() == null) {
            throw new IllegalEntityException("reservation id is null");
        }  
        
        checkDataSource();
        Connection conn = null;
        PreparedStatement st = null;
        try {
            conn = ds.getConnection();
            st = conn.prepareStatement(
                    "SELECT * FROM Reservation WHERE pokemonId = ?");
            st.setLong(1, pokemon.getId());
            return executeQueryForMultipleReservation(st);
        } catch (SQLException ex) {
            String msg = "Error when getting all pokemons reservation from DB";
            logger.log(Level.SEVERE, msg, ex);
            throw new ServiceFailureException(msg, ex);
        } finally {
            DBUtils.closeQuietly(conn, st);
        }          
    }
}
