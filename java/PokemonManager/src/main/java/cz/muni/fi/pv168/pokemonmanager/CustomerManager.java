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
public interface CustomerManager {
    
    /**
     * Stores new customer into database. Id for the new body is automatically
     * generated and stored into id attribute.
     * 
     * @param customer customer to be created.
     * @return address to a just created customer
     * @throws IllegalArgumentException when customer is null.
     * @throws IllegalEntityException when customer has already assigned id.
     * @throws ValidationException when customer has null name.
     * @throws ServiceFailureException when db operation fails.
     */
    void createCustomer(Customer customer) throws ServiceFailureException, ValidationException, IllegalEntityException;

    /**
     * Returns customer with given id.
     * 
     * @param id primary key of requested Customer.
     * @return customer with given id or null if such customer does not exist.
     * @throws IllegalArgumentException when given id is null.
     * @throws ServiceFailureException when db operation fails.
     */
    Customer getCustomer(Long id) throws ServiceFailureException;
    
    /**
     * Returns body with given id.
     * 
     * @param customer updated customer to be stored into database.
     * @throws ValidationException when customer has null name.
     * @throws IllegalEntityException when customer is not in the database.
     * @throws IllegalArgumentException when given customer or his id is null.
     * @throws ServiceFailureException when db operation fails.
     * 
     */
    void updateCustomer(Customer customer) throws ServiceFailureException, ValidationException, IllegalEntityException;

    /**
     * Deletes customer from database. 
     * 
     * @param customer customer to be deleted from db.
     * @throws IllegalArgumentException when customer is null.
     * @throws IllegalEntityException when given customer does not exist in the database
     * @throws ServiceFailureException when db operation fails.
     */
    void deleteCustomer(Customer customer) throws ServiceFailureException, IllegalEntityException;
    
    /**
     * Returns list of all bodies in the database.
     * 
     * @return list of all bodies in database.
     * @throws ServiceFailureException when db operation fails.
     */
    List<Customer> findAllCustomer() throws ServiceFailureException;
    }
