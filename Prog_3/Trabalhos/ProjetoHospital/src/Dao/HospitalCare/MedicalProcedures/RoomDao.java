package Dao.HospitalCare.MedicalProcedures;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

import Connection.CreateConnection;
import Entities.HospitalCare.MedicalProcedures.Room;

public class RoomDao {
  private Connection connection;

  public RoomDao() throws ClassNotFoundException, SQLException {
    // Obter uma conexão com o banco de dados
    connection = CreateConnection.getConnection();
  }

  public void insert(Room room) throws SQLException {
    String query = "INSERT INTO rooms (name) VALUES (?)";
    PreparedStatement statement = connection.prepareStatement(query);
    statement.setString(1, room.getName());
    statement.executeUpdate();
  }

  public List<Room> getAll() throws SQLException {
    String query = "SELECT * FROM rooms";
    PreparedStatement statement = connection.prepareStatement(query);
    ResultSet resultSet = statement.executeQuery();

    List<Room> rooms = new ArrayList<>();

    while (resultSet.next()) {
      Room room = createRoomFromResultSet(resultSet);
      rooms.add(room);
    }

    return rooms;
  }

  public Room getById(int id) throws SQLException {
    String query = "SELECT * FROM rooms WHERE id = ?";
    PreparedStatement statement = connection.prepareStatement(query);
    statement.setInt(1, id);
    ResultSet resultSet = statement.executeQuery();

    if (resultSet.next()) {
      Room room = createRoomFromResultSet(resultSet);
      return room;
    }

    return null; // Sala não encontrada
  }

  public void update(Room room) throws SQLException {
    String query = "UPDATE rooms SET name = ? WHERE id = ?";
    PreparedStatement statement = connection.prepareStatement(query);
    statement.setString(1, room.getName());
    statement.setInt(2, room.getId());
    statement.executeUpdate();
  }

  public void delete(int id) throws SQLException {
    String query = "DELETE FROM rooms WHERE id = ?";
    PreparedStatement statement = connection.prepareStatement(query);
    statement.setInt(1, id);
    statement.executeUpdate();
  }

  private Room createRoomFromResultSet(ResultSet resultSet) throws SQLException {
    int id = resultSet.getInt("id");
    String name = resultSet.getString("name");

    Room room = new Room(id, name);
    return room;
  }
}