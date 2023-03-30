public class SalariedEmployee extends Employee {
    private double weeklySalary;

    public SalariedEmployee(String FirstName, String LastName, int SocialSecurityNumber, double weeklySalary,
            BirthDate birthDate) {
        super(FirstName, LastName, SocialSecurityNumber, birthDate);
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
        return String.format("Salaried Employee:\n Name: %s %s\n Social Number: %d\n Weekly salary %.2f\n BirthDate %s",
                getFirstName(), getLastName(),
                getSocialSecurityNumber(),
                getWeeklySalary(), getBirthDate());
    }
}
