package testes;

import java.sql.SQLException;
import java.util.List;

import Dao.HospitalCare.MedicalProcedures.RoomDao;
import Entities.HospitalCare.MedicalProcedures.Room;

public class RoomDaoTeste {
  public static void main(String[] args) {
    try {
      // Criar instância do DAO
      RoomDao roomDao = new RoomDao();

      // Inserir uma sala
      Room room1 = new Room(0, "Sala 1");
      roomDao.insert(room1);
      System.out.println("Sala inserida com sucesso!");

      // Inserir uma sala
      Room room2 = new Room(0, "Sala 1");
      roomDao.insert(room1);
      System.out.println("Sala inserida com sucesso!");

      // Obter todas as salas
      List<Room> rooms = roomDao.getAll();
      System.out.println("Lista de Salas:");
      for (Room room : rooms) {
        System.out.println(room.getName());
      }

      // Atualizar uma sala
      Room roomToUpdate = rooms.get(0);
      roomToUpdate.setName("Sala Atualizada");
      roomDao.update(roomToUpdate);
      System.out.println("Sala atualizada com sucesso!");

      // Obter uma sala por ID
      Room retrievedRoom = roomDao.getById(roomToUpdate.getId());
      if (retrievedRoom != null) {
        System.out.println("Sala encontrada: " + retrievedRoom.getName());
      } else {
        System.out.println("Sala não encontrada");
      }

      // Excluir uma sala
      // Room roomToDelete = rooms.get(roomToUpdate.getId());
      // roomDao.delete(roomToDelete.getId());
      // System.out.println("Sala excluída com sucesso!");

    } catch (ClassNotFoundException | SQLException e) {
      e.printStackTrace();
    }
  }
}
