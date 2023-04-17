package Person;

public class Person {

    private String Name;
    private BirthDate BirthDate;
    private Address Address;

    public Person(String Name, BirthDate BirthDate, Address Address) {
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

    public BirthDate getBirthDate() {
        return BirthDate;
    }

    public void setBirthDate(BirthDate BirthDate) {
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
