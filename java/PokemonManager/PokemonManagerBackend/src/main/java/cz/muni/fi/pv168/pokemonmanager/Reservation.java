/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package cz.muni.fi.pv168.pokemonmanager;

import java.time.LocalDateTime;
import java.util.List;
import java.util.Objects;
/**
 *
 * @author mutinar
 */
public class Reservation {
    
    private Long id;
    private LocalDateTime from;
    private LocalDateTime to;
    private Pokemon pokemon;
    private Customer customer;

    public Long getId() {
        return id;
    }

    public LocalDateTime getFrom() {
        return from;
    }

    public LocalDateTime getTo() {
        return to;
    }

    public Pokemon getPokemon() {
        return pokemon;
    }

    public Customer getCustomer() {
        return customer;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public void setFrom(LocalDateTime from) {
        this.from = from;
    }

    public void setTo(LocalDateTime to) {
        this.to = to;
    }

    public void setPokemon(Pokemon pokemon) {
        this.pokemon = pokemon;
    }

    public void setCustomer(Customer customer) {
        this.customer = customer;
    }
    
    @Override
    public String toString() {
        return "Reservation{"
                + "id = " + id
                + ", from = " + from
                + ", to = " + to
                + ", customer = " + customer.getName()
                + ", pokemon = " + pokemon.toString()
                + '}';
    }
    @Override
    public boolean equals(Object obj) {
        if (obj == null) {
            return false;
        }
        if (getClass() != obj.getClass()) {
            return false;
        }
        final Reservation other = (Reservation) obj;
        if (obj != this && this.id == null) {
            return false;
        }
        return Objects.equals(this.id, other.id);
    }

    @Override
    public int hashCode() {
        return Objects.hash(this.id);
    }
    
}
