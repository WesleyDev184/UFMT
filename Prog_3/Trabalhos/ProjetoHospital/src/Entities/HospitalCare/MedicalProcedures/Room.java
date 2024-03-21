package Entities.HospitalCare.MedicalProcedures;

public class Room {
  private int id;
  private String name;

  public Room(int id, String name) {
    this.id = id;
    this.name = name;
  }

  public void setId(int id) {
    this.id = id;
  }

  public int getId() {
    return this.id;
  }

  public String getName() {
    return this.name;
  }

  public void setName(String name) {
    this.name = name;
  }

  public String toStrint() {
    return "id:" + this.id + " Room: " + this.name;
  }

  public String toString() {
    return "id:" + this.id + " Room: " + this.name;
  }
}
