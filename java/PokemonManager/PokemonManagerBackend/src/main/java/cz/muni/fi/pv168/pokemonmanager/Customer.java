/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package cz.muni.fi.pv168.pokemonmanager;

import java.util.Objects;

/**
 * This entity represents Customer.
 * Customer has some name and id.
 * @author mutinar
 */
public class Customer {
    
    private Long id;
    private String name;

    public Long getId() {
        return id;
    }

    public String getName() {
        return name;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public void setName(String name) {
        this.name = name;
    }
    
    @Override
    public String toString() {
        return "Body{"
                + "id=" + id
                + ", name=" + name
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
        final Customer other = (Customer) obj;
        if (obj != this && this.id == null) {
            return false;
        }
        return ((this.id == other.id) && (this.name.equals(other.name)));
    }

    @Override
    public int hashCode() {
        return Objects.hash(this.id);
    }
    
}
