package Entities.Person;

public abstract class Person {

  private String Name;
  private String BirthDate;
  private Address Address;

  protected Person(String Name, String BirthDate, Address Address) {
    this.Name = Name;
    this.BirthDate = BirthDate;
    this.Address = Address;
  }

  public String getName() {
    return Name;
  }

  public void setName(String Name) {
    this.Name = Name;
  }

  public String getBirthDate() {
    return BirthDate;
  }

  public void setBirthDate(String BirthDate) {
    this.BirthDate = BirthDate;
  }

  public Address getAddress() {
    return Address;
  }

  public void setAddress(Address Address) {
    this.Address = Address;
  }

  public String toString() {
    return String.format("Name: %s %s %s", Name, BirthDate, Address);
  }

}