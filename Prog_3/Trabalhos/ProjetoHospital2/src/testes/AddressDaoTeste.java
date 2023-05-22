package testes;

import java.sql.SQLException;
import java.util.List;

import Dao.Person.AddressDao;
import Entities.Person.Address;

public class AddressDaoTeste {

  public static void main(String[] args) throws SQLException, ClassNotFoundException {

    try {
      AddressDao addressDAO = new AddressDao();

      // Obter um endereço por ID
      Address retrievedAddress = addressDAO.getById(1);
      System.out.println("Endereço recuperado: " + retrievedAddress);

      // Atualizar um endereço
      retrievedAddress.setPublicPlace("Avenida B");
      addressDAO.update(retrievedAddress);
      System.out.println("Endereço atualizado com sucesso!");

      // Obter todos os endereços
      List<Address> allAddresses = addressDAO.getAll();
      System.out.println("Todos os endereços:");
      for (Address addr : allAddresses) {
        System.out.println(addr);
      }

    } catch (Exception e) {
      e.printStackTrace();
    }

  }

}
