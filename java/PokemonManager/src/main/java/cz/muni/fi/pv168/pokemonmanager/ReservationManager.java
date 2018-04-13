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
public interface ReservationManager {
    
    /**
     * Creates new reservation in db
     * @param reservation reservation to be created
     * @return created reservation with assigned id
     * @throws ServiceFailureException when db operations fail
     * @throws ValidationException when invalid reservation has to be created
     * (from is null || to is null || from is bigger than to || customer is null ||
     * || customer has null id || customer is not in db || pokemon has null id ||
     * || pokemon is not in db)
     * @throws IllegalEntityException when reservation has already assigned id
     * @throws IllegalArgumentException when reservation is null
     */
    void createReservation(Reservation reservation) throws ServiceFailureException, ValidationException, IllegalEntityException;
    
    /**
     * gets reservation by id
     * @param id id of the reservation
     * @return reservation with specified id
     * @throws ServiceFailureException when db operations fail
     * @throws IllegalArgumentException when id is null
     */
    Reservation getReservation(Long id) throws ServiceFailureException;
    
    /**
     * updates existing reservation
     * @param reservation to be updated
     * @throws ServiceFailureException when db operations fail
     * @throws ValidationException when invalid reservation has to be updated
     * @throws IllegalEntityException when id of reservation is not in db
     * @throws IllegalArgumentException when reservation is null
     */
    void updateReservation(Reservation reservation) throws ServiceFailureException, ValidationException, IllegalEntityException;
    
    /**
     * deletes existing reservation
     * @param reservation reservation to be removed
     * @throws ServiceFailureException when db operations fail
     * @throws IllegalEntityException when id is null or does not exist in db
     * @throws IllegalArgumentException when reservation is null
     */
    void deleteReservation(Reservation reservation) throws ServiceFailureException, IllegalEntityException;
    
    /**
     * lists all reservations
     * @return list of all reservation 
     * @throws ServiceFailureException when db operations fail
     */
    List<Reservation> findAllReservation() throws ServiceFailureException;
    
    /**
     * lists all reservations of one customer 
     * @param customer customer associated with the reservations
     * @return list of all reservations of one customer
     * @throws ServiceFailureException when db operations fail
     * @throws IllegalEntityException when id is null
     */
    List<Reservation> findCustomerReservation(Customer customer) throws ServiceFailureException, IllegalEntityException;
    
    /**
     * lists all reservations of one pokemon 
     * @param pokemon pokemon associated with the reservations
     * @return list of all reservations of one pokemon
     * @throws ServiceFailureException when db operations fail
     * @throws IllegalEntityException when id is null
     */
    List<Reservation> findPokemonReservation(Pokemon pokemon) throws ServiceFailureException, IllegalEntityException;
}
