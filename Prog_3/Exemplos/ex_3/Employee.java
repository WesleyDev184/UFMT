public abstract class Employee {
    private String FirstName;
    private String LastName;
    private int SocialSecurityNumber;
    private BirthDate birthDate;

    protected Employee(String FirstName, String LastName, int SocialSecurityNumber, BirthDate birthDate) {
        this.FirstName = FirstName;
        this.LastName = LastName;
        this.SocialSecurityNumber = SocialSecurityNumber;
        this.birthDate = birthDate;
    }

    public String getFirstName() {
        return FirstName;
    }

    public void setFirstName(String FirstName) {
        this.FirstName = FirstName;
    }

    public String getLastName() {
        return LastName;
    }

    public void setLastName(String LastName) {
        this.LastName = LastName;
    }

    public int getSocialSecurityNumber() {
        return SocialSecurityNumber;
    }

    public void setSocialSecurityNumber(int SocialSecurityNumber) {
        this.SocialSecurityNumber = SocialSecurityNumber;
    }

    public BirthDate getBirthDate() {
        return birthDate;
    }

    public void setBirthDate(BirthDate birthDate) {
        this.birthDate = birthDate;
    }

    public String toString() {
        return String.format("%s %s %d", getFirstName(), getLastName(), getSocialSecurityNumber());
    }

    public abstract double earnings();
}
