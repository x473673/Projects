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
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.sql.DataSource;


public class PokemonManagerImpl implements PokemonManager {

    private DataSource ds;
    private static final Logger logger = Logger.getLogger(
            PokemonManagerImpl.class.getName());       //?
    
    public PokemonManagerImpl(DataSource ds) {
        this.ds = ds;
    }
    
    private void checkDataSource() {
        if (ds == null) {
            throw new IllegalStateException("DataSource is not set");
        }
    }
    
    private void validate(Pokemon pokemon) {
        if (pokemon == null) {
            throw new IllegalArgumentException("pokemon is null");
        }
        if (pokemon.getName() == null) {
            throw new ValidationException("name is null");
        }
        if (pokemon.getHealth() < 0) {
            throw new ValidationException("health is negative");
        }
        if (pokemon.getPower() < 0) {
            throw new ValidationException("power is negative");
        }
    }
    
    @Override
    public void createPokemon(Pokemon pokemon) throws ServiceFailureException, ValidationException, IllegalEntityException {
        if(pokemon == null){
            throw new IllegalArgumentException("pokemon is null");
        }
        if(pokemon.getId() != null){
            throw new IllegalEntityException("id already assigned");
        }
        if((pokemon.getName() == null) || (pokemon.getHealth() < 0) || (pokemon.getPower() < 0)){
            throw new ValidationException("null name or negative attribute");
        }
        Connection conn = null;
        checkDataSource();
        validate(pokemon);
        try{
            conn = ds.getConnection();
            PreparedStatement ps = conn.prepareStatement("INSERT INTO pokemon (name, health, power) VALUES (?, ?, ?)",Statement.RETURN_GENERATED_KEYS);
            ps.setString(1, pokemon.getName());
            ps.setInt(2, pokemon.getHealth());
            ps.setInt(3, pokemon.getPower());  
            ps.executeUpdate();
                ResultSet keys = ps.getGeneratedKeys(); //?
                if(keys.next()){
                    long key = keys.getLong(1);
                    pokemon.setId(key);
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
    public Pokemon getPokemon(Long id) throws ServiceFailureException {
        checkDataSource();
        if (id == null) {
            throw new IllegalArgumentException("id is null");
        }
        Connection conn = null;
        try {
            conn = ds.getConnection();
            PreparedStatement ps = conn.prepareStatement(
                    "SELECT id, name, health, power FROM Pokemon WHERE id = ?");
            ps.setLong(1, id);
            return executeQueryForSinglePokemon(ps);
        } catch (SQLException ex) {
            String msg = "Error when getting pokemon with id = " + id + " from DB";
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
    
    static Pokemon executeQueryForSinglePokemon(PreparedStatement st) throws SQLException, ServiceFailureException {
        ResultSet rs = st.executeQuery();
        if (rs.next()) {  
            Pokemon result = rowToPokemon(rs);                
            if (rs.next()) {
                throw new ServiceFailureException(
                    "Internal integrity error: more pokemons with the same id found!");
            }
            return result;
        }else {
            return null;
        }
    }
        
    static private Pokemon rowToPokemon(ResultSet rs) throws SQLException {            
        Pokemon result = new Pokemon();
        result.setId(rs.getLong("id"));
        result.setName(rs.getString("name"));
        result.setHealth(rs.getInt("health"));
        result.setPower(rs.getInt("power"));
        return result;
    }

    @Override
    public void updatePokemon(Pokemon pokemon) throws ServiceFailureException, ValidationException, IllegalEntityException {
        checkDataSource();
        validate(pokemon);
        
        if(pokemon == null){
            throw new IllegalArgumentException("pokemon is null");
        }
        if(pokemon.getId() == null){
            throw new IllegalEntityException("id is null");
        }
        if((pokemon.getName() == null) || (pokemon.getHealth() < 0) || (pokemon.getPower() < 0)){
            throw new ValidationException("null name or negative attribute");
        }     
        Connection conn = null;
        PreparedStatement ps = null;
        try {
            conn = ds.getConnection();          
            ps = conn.prepareStatement(
                    "UPDATE pokemon SET name = ?, health = ?, power = ? WHERE id = ?");
            ps.setString(1, pokemon.getName());
            ps.setInt(2, pokemon.getHealth());
            ps.setInt(3, pokemon.getPower());
            ps.setLong(4, pokemon.getId());
            int count = ps.executeUpdate();
            DBUtils.checkUpdatesCount(count, pokemon, false);
        } catch (SQLException ex) {
            String msg = "Error when updating pokemon in the db";
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
    public void deletePokemon(Pokemon pokemon) throws ServiceFailureException, IllegalEntityException {
        checkDataSource();
        if (pokemon == null) {
            throw new IllegalArgumentException("pokemon is null");
        }        
        if (pokemon.getId() == null) {
            throw new IllegalEntityException("pokemon id is null");
        }        
        Pokemon dbPokemon = getPokemon(pokemon.getId());     
        if (!pokemon.equals(dbPokemon)) {
            throw new IllegalEntityException("pokemon is incorrect in db");
        }      
        Connection conn = null;
        PreparedStatement ps = null;
        try {
            conn = ds.getConnection();
            ps = conn.prepareStatement("DELETE FROM Pokemon WHERE id = ?");
            ps.setLong(1, pokemon.getId());

            int count = ps.executeUpdate();
            DBUtils.checkUpdatesCount(count, pokemon, false);
        } catch (SQLException ex) {
            String msg = "Error when deleting pokemon from the db";
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
    public List<Pokemon> findAllPokemon() throws ServiceFailureException {
        checkDataSource();
        Connection conn = null;
        try {
            conn = ds.getConnection();
            PreparedStatement ps = conn.prepareStatement(
                    "SELECT id, name, health, power FROM Pokemon");
            ResultSet rs = ps.executeQuery();
            List<Pokemon> pokemons = new ArrayList<>();
            while(rs.next()) {
                Pokemon pokemon = new Pokemon();
                pokemon.setId(rs.getLong("id"));
                pokemon.setName(rs.getString("name"));
                pokemon.setHealth(rs.getInt("health"));
                pokemon.setPower(rs.getInt("Power"));
                pokemons.add(pokemon);
            }
            return pokemons;
        } catch (SQLException ex) {
            String msg = "Error when getting all pokemons from DB";
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
