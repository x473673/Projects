/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package cz.muni.fi.pv168.pokemonmanager;

import cz.muni.fi.pv168.exceptions.IllegalEntityException;
import cz.muni.fi.pv168.exceptions.ServiceFailureException;
import cz.muni.fi.pv168.exceptions.ValidationException;
import java.util.List;

/**
 *
 * @author mutinar
 */
public interface PokemonManager {
    
    /**
     * Stores new pokemon into database. Id for the new body is automatically
     * generated and stored into id attribute.
     * 
     * @param pokemon pokemon to be created.
     * @throws IllegalArgumentException when pokemon is null.
     * @throws IllegalEntityException when pokemon has already assigned id.
     * @throws ValidationException when pokemon has null name.
     * @throws ServiceFailureException when db operation fails.
     */
    void createPokemon(Pokemon pokemon) throws ServiceFailureException, ValidationException, IllegalEntityException;
    
    /**
     * Returns pokemon with given id.
     * 
     * @param id primary key of requested pokemon.
     * @return pokemon with given id or null if such pokemon does not exist.
     * @throws IllegalArgumentException when given id is null.
     * @throws ServiceFailureException when db operation fails.
     */
    Pokemon getPokemon(Long id) throws ServiceFailureException;
    
    /**
     * Returns body with given id.
     * 
     * @param pokemon updated pokemon to be stored into database.
     * @throws ValidationException when pokemon has null name.
     * @throws IllegalEntityException when pokemon is not in the database.
     * @throws IllegalArgumentException when given id is null.
     * @throws ServiceFailureException when db operation fails.
     * 
     */
    void updatePokemon(Pokemon pokemon) throws ServiceFailureException, ValidationException, IllegalEntityException;
    
    /**
     * Deletes pokemon from database. 
     * 
     * @param pokemon pokemon to be deleted from db.
     * @throws IllegalArgumentException when pokemon is null.
     * @throws IllegalEntityException when given pokemon does not exist in the database
     * @throws ServiceFailureException when db operation fails.
     */
    void deletePokemon(Pokemon pokemon) throws ServiceFailureException, IllegalEntityException;
    
    /**
     * Returns list of all bodies in the database.
     * 
     * @return list of all bodies in database.
     * @throws ServiceFailureException when db operation fails.
     */
    List<Pokemon> findAllPokemon() throws ServiceFailureException;
}
