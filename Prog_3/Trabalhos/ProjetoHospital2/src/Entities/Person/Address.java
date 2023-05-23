package Entities.Person;

public class Address {
  private int Id;
  private String PublicPlace;
  private int Number;
  private long CEP;
  private String Neighborhood;

  public Address(int id, String PublicPlace, int Number, long CEP, String Neighborhood) {
    this.Id = id;
    this.PublicPlace = PublicPlace;
    this.Number = Number;
    this.CEP = CEP;
    this.Neighborhood = Neighborhood;
  }

  public int getId() {
    return Id;
  }

  public void setId(int id) {
    this.Id = id;
  }

  public String getPublicPlace() {
    return PublicPlace;
  }

  public void setPublicPlace(String PublicPlace) {
    this.PublicPlace = PublicPlace;
  }

  public int getNumber() {
    return Number;
  }

  public void setNumber(int Number) {
    this.Number = Number;
  }

  public long getCEP() {
    return CEP;
  }

  public void setCEP(long CEP) {
    this.CEP = CEP;
  }

  public String getNeighborhood() {
    return Neighborhood;
  }

  public void setNeighborhood(String Neighborhood) {
    this.Neighborhood = Neighborhood;
  }

  public String toString() {
    return "Address [Id=" + Id + ", PublicPlace=" + PublicPlace + ", Number=" + Number + ", CEP=" + CEP
        + ", Neighborhood=" + Neighborhood + "]";
  }

}
