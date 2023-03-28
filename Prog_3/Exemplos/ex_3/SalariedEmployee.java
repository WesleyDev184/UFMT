public class SalariedEmployee extends Employee {
    private double weeklySalary;

    public SalariedEmployee(String FirstName, String LastName, int SocialSecurityNumber, double weeklySalary) {
        super(FirstName, LastName, SocialSecurityNumber);
        this.weeklySalary = weeklySalary;
    }

    public double getWeeklySalary() {
        return weeklySalary;
    }

    public void setWeeklySalary(double weeklySalary) {
        this.weeklySalary = weeklySalary;
    }

    @Override
    public double earnings() {
        return getWeeklySalary();
    }

    @Override
    public String toString() {
        return String.format("Salaried Employee: %s %s %d %.2f", getFirstName(), getLastName(),
                getSocialSecurityNumber(),
                getWeeklySalary());
    }
}
