package Dao.Person;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.List;

import Connection.CreateConnection;
import Entities.Person.Address;

public class AddressDao {
  private Connection connection;

  public AddressDao() throws ClassNotFoundException, SQLException {
    this.connection = CreateConnection.getConnection();
  }

  public Address insert(Address address) throws SQLException {
    String query = "INSERT INTO addresses (public_place, number, cep, neighborhood) VALUES (?, ?, ?, ?)";
    try (PreparedStatement statement = connection.prepareStatement(query, Statement.RETURN_GENERATED_KEYS)) {
      statement.setString(1, address.getPublicPlace());
      statement.setInt(2, address.getNumber());
      statement.setInt(3, address.getCEP());
      statement.setString(4, address.getNeighborhood());
      statement.executeUpdate();

      ResultSet generatedKeys = statement.getGeneratedKeys();
      if (generatedKeys.next()) {
        int generatedId = generatedKeys.getInt(1);
        address.setId(generatedId); // Define o ID gerado no objeto Address
      }

      return address;
    } catch (SQLException e) {
      System.out.println(e.getMessage());
      throw e;
    }
  }

  public Address getById(int id) throws SQLException {
    String query = "SELECT * FROM addresses WHERE id = ?";
    try (PreparedStatement statement = connection.prepareStatement(query)) {
      statement.setInt(1, id);
      try (ResultSet resultSet = statement.executeQuery()) {
        if (resultSet.next()) {
          return createAddressFromResultSet(resultSet);
        }
      }
    }
    return null;
  }

  public List<Address> getAll() throws SQLException {
    List<Address> addresses = new ArrayList<>();
    String query = "SELECT * FROM addresses";
    try (PreparedStatement statement = connection.prepareStatement(query);
        ResultSet resultSet = statement.executeQuery()) {
      while (resultSet.next()) {
        Address address = createAddressFromResultSet(resultSet);
        addresses.add(address);
      }
    }
    return addresses;
  }

  public Address update(Address address) throws SQLException {
    String query = "UPDATE addresses SET public_place = ?, number = ?, cep = ?, neighborhood = ? WHERE id = ?";
    try (PreparedStatement statement = connection.prepareStatement(query)) {
      statement.setString(1, address.getPublicPlace());
      statement.setInt(2, address.getNumber());
      statement.setFloat(3, address.getCEP());
      statement.setString(4, address.getNeighborhood());
      statement.setInt(5, address.getId());
      statement.executeUpdate();
    }

    return address; // Retorna o objeto atualizado
  }

  public void delete(int id) throws SQLException {
    String query = "DELETE FROM addresses WHERE id = ?";
    try (PreparedStatement statement = connection.prepareStatement(query)) {
      statement.setInt(1, id);
      statement.executeUpdate();
    }
  }

  private static Address createAddressFromResultSet(ResultSet resultSet) throws SQLException {
    int id = resultSet.getInt("id");
    String publicPlace = resultSet.getString("public_place");
    int number = resultSet.getInt("number");
    int cep = resultSet.getInt("cep");
    String neighborhood = resultSet.getString("neighborhood");
    return new Address(id, publicPlace, number, cep, neighborhood);
  }
}