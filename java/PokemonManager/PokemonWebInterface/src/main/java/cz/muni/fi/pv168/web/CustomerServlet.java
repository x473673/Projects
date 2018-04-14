package cz.muni.fi.pv168.web;

import cz.muni.fi.pv168.pokemonmanager.Customer;
import cz.muni.fi.pv168.exceptions.ValidationException;
import cz.muni.fi.pv168.pokemonmanager.CustomerManagerImpl;
import cz.muni.fi.pv168.pokemonmanager.PokemonManagerImpl;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

/**
 * Servlet for managing customers.
 *
 * @author Robin Mutina
 */
@WebServlet(CustomerServlet.URL_MAPPING + "/*")
public class CustomerServlet extends HttpServlet {

    private static final String LIST_JSP = "/list.jsp";
    public static final String URL_MAPPING = "/customers";

    private final static Logger log = LoggerFactory.getLogger(CustomerServlet.class);

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        log.debug("GET ...");
        showLists(request, response);
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        //support non-ASCII characters in form
        request.setCharacterEncoding("utf-8");
        //action specified by pathInfo
        String action = request.getPathInfo();
        log.debug("POST ... {}",action);
        switch (action) {
            case "/add":
                //getting POST parameters from form
                String name = request.getParameter("name");
                //form data validity check
                if (name == null || name.length() == 0) {
                    request.setAttribute("Cerror", "Je nutné vyplnit všechny hodnoty !");
                    log.debug("form data invalid");
                    showLists(request, response);
                    return;
                }
                //form data processing - storing to database
                try {
                    Customer customer = new Customer();
                    customer.setName(name);
                    
                    getCustomerManager().createCustomer(customer);
                    //redirect-after-POST protects from multiple submission
                    log.debug("redirecting after POST");
                    response.sendRedirect(request.getContextPath()+URL_MAPPING);
                    return;
                } catch (ValidationException e) {
                    log.error("Cannot add customer", e);
                    response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, e.getMessage());
                    return;
                }
            case "/delete":
                try {
                    Long id = Long.valueOf(request.getParameter("id"));
                    getCustomerManager().deleteCustomer(getCustomerManager().getCustomer(id));
                    log.debug("redirecting after POST");
                    response.sendRedirect(request.getContextPath()+URL_MAPPING);
                    return;
                } catch (ValidationException e) {
                    log.error("Cannot delete customer", e);
                    response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, e.getMessage());
                    return;
                }
            default:
                log.error("Unknown action " + action);
                response.sendError(HttpServletResponse.SC_NOT_FOUND, "Unknown action " + action);
        }
    }

    /**
     * Gets PokemonManager from ServletContext, where it was stored by {@link StartListener}.
     *
     * @return PokemonManager instance
     */
    private PokemonManagerImpl getPokemonManager() {
        return (PokemonManagerImpl) getServletContext().getAttribute("pokemonManager");
    }
    
    /**
     * Gets PokemonManager from ServletContext, where it was stored by {@link StartListener}.
     *
     * @return PokemonManager instance
     */
    private CustomerManagerImpl getCustomerManager() {
        return (CustomerManagerImpl) getServletContext().getAttribute("customerManager");
    }

    /**
     * Stores the list of pokemons and customers to request attributes "pokemons" and "customers" and forwards to the JSP to display it.
     */
    private void showLists(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        try {
            log.debug("showing tables");
            request.setAttribute("pokemons", getPokemonManager().findAllPokemon());
            request.setAttribute("customers", getCustomerManager().findAllCustomer());
            request.getRequestDispatcher(LIST_JSP).forward(request, response);
        } catch (ValidationException e) {
            log.error("Cannot show tables", e);
            response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, e.getMessage());
        }
    }

}

