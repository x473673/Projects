package cz.muni.fi.pv168.web;

import cz.muni.fi.pv168.pokemonmanager.CustomerManagerImpl;
import cz.muni.fi.pv168.pokemonmanager.PokemonManagerImpl;
//import cz.muni.fi.pv168.books.CustomerManagerImpl;
import cz.muni.fi.pv168.pokemonmanager.Main;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import javax.servlet.ServletContext;
import javax.servlet.ServletContextEvent;
import javax.servlet.ServletContextListener;
import javax.servlet.annotation.WebListener;
import javax.sql.DataSource;

@WebListener
public class StartListener implements ServletContextListener {

    private final static Logger log = LoggerFactory.getLogger(StartListener.class);

    @Override
    public void contextInitialized(ServletContextEvent ev) {
        log.info("webová aplikace inicializována");
        ServletContext servletContext = ev.getServletContext();
        DataSource dataSource = Main.createMemoryDatabase();
        servletContext.setAttribute("pokemonManager", new PokemonManagerImpl(dataSource));
        servletContext.setAttribute("customerManager", new CustomerManagerImpl(dataSource));
        log.info("vytvořeny manažery a uloženy do atributů servletContextu");
    }

    @Override
    public void contextDestroyed(ServletContextEvent ev) {
        log.info("aplikace končí");
    }
}
