public abstract class Employee {
    private String FirstName;
    private String LastName;
    private int SocialSecurityNumber;

    protected Employee(String FirstName, String LastName, int SocialSecurityNumber) {
        this.FirstName = FirstName;
        this.LastName = LastName;
        this.SocialSecurityNumber = SocialSecurityNumber;
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

    public String toString() {
        return String.format("%s %s %d", getFirstName(), getLastName(), getSocialSecurityNumber());
    }

    public double earnings() {
        return 0;
    }
}
