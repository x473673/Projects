<%@page contentType="text/html;charset=utf-8" pageEncoding="UTF-8" %>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<html>
<body>

<h2>Pokemons:</h2>
<table border="1">
    <thead>
    <tr>
        <th>Name</th>
        <th>Health</th>
        <th>Power</th>
    </tr>
    </thead>
    <c:forEach items="${pokemons}" var="pokemon">
        <tr>
            <td><c:out value="${pokemon.name}"/></td>
            <td><c:out value="${pokemon.health}"/></td>
            <td><c:out value="${pokemon.power}"/></td>
            <td><form method="post" action="${pageContext.request.contextPath}/pokemons/delete?id=${pokemon.id}"
                      style="margin-bottom: 0;"><input type="submit" value="delete"></form></td>
        </tr>
    </c:forEach>
</table>
    
<h2>Customers:</h2>
<table border="1">
    <thead>
    <tr>
        <th>Name</th>
    </tr>
    </thead>
    <c:forEach items="${customers}" var="customer">
        <tr>
            <td><c:out value="${customer.name}"/></td>
            <td><form method="post" action="${pageContext.request.contextPath}/customers/delete?id=${customer.id}"
                      style="margin-bottom: 0;"><input type="submit" value="delete"></form></td>
        </tr>
    </c:forEach>
</table>

<h2>Insert pokemon</h2>
<c:if test="${not empty Perror}">
    <div style="border: solid 1px red; background-color: yellow; padding: 10px">
        <c:out value="${Perror}"/>
    </div>
</c:if>
<form action="${pageContext.request.contextPath}/pokemons/add" method="post">
    <table>
        <tr>
            <th>Pokemon's name:</th>
            <td><input type="text" name="name" value="<c:out value='${param.name}'/>"/></td>
        </tr>
        <tr>
            <th>Health:</th>
            <td><input type="text" name="health" value="<c:out value='${param.health}'/>"/></td>
        </tr>
        <tr>
            <th>Power:</th>
            <td><input type="text" name="power" value="<c:out value='${param.power}'/>"/></td>
        </tr>
    </table>
    <input type="Submit" value="Zadat" />
</form>
        
<h2>Insert customer</h2>
<c:if test="${not empty Cerror}">
    <div style="border: solid 1px red; background-color: yellow; padding: 10px">
        <c:out value="${Cerror}"/>
    </div>
</c:if>
<form action="${pageContext.request.contextPath}/customers/add" method="post">
    <table>
        <tr>
            <th>Customer's name:</th>
            <td><input type="text" name="name" value="<c:out value='${param.name}'/>"/></td>
        </tr>
    </table>
    <input type="Submit" value="Zadat" />
</form>

</body>
</html>