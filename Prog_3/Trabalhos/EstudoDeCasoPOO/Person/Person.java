package Person;

public abstract class Person {

    private String Name;
    private DateOfBirth DateOfBirth;
    private Address Address;

    protected Person(String Name, DateOfBirth DateOfBirth, Address Address) {
        this.Name = Name;
        this.DateOfBirth = DateOfBirth;
        this.Address = Address;
    }

    public String getName() {
        return Name;
    }

    public void setName(String Name) {
        this.Name = Name;
    }

    public DateOfBirth getBirthDate() {
        return DateOfBirth;
    }

    public void setBirthDate(DateOfBirth DateOfBirth) {
        this.DateOfBirth = DateOfBirth;
    }

    public Address getAddress() {
        return Address;
    }

    public void setAddress(Address Address) {
        this.Address = Address;
    }

    public abstract String toString();

}
