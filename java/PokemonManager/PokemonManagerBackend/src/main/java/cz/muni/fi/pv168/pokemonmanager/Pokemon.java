/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package cz.muni.fi.pv168.pokemonmanager;

import java.util.Objects;

/**
 *
 * @author mutinar
 */
public class Pokemon {
   
    private Long id;
    private String name;
    private int health;
    private int power;

    public Long getId() {
        return id;
    }

    public String getName() {
        return name;
    }

    public int getHealth() {
        return health;
    }

    public int getPower() {
        return power;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public void setName(String name) {
        this.name = name;
    }

    public void setHealth(int health) {
        this.health = health;
    }

    public void setPower(int power) {
        this.power = power;
    }
    
    @Override
    public String toString() {
        return "Pokemon {"
                + "id=" + id
                + ", name=" + name
                + ", health=" + health
                + ", power=" + power
               
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
        final Pokemon other = (Pokemon) obj;
        if (obj != this && this.id == null) {
            return false;
        }
        return (this.id == other.id) && 
                (this.name.equals(other.name)) && 
                (this.power == other.power) && 
                (this.health == other.health);
    }

    @Override
    public int hashCode() {
        return Objects.hash(this.id);
    }
 
}
