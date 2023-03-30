public class HourlyEmployee extends Employee {
    private double wage;
    private double hours;

    public HourlyEmployee(String FirstName, String LastName, int SocialSecurityNumber, double wage, double hours,
            BirthDate birthDate) {
        super(FirstName, LastName, SocialSecurityNumber, birthDate);
        this.wage = wage;
        this.hours = hours;
    }

    public double getWage() {
        return wage;
    }

    public void setWage(double wage) {
        this.wage = wage;
    }

    public double getHours() {
        return hours;
    }

    public void setHours(double hours) {
        this.hours = hours;
    }

    @Override
    public double earnings() {
        if (getHours() <= 40) {
            return getWage() * getHours();
        } else {
            return 40 * getWage() + (getHours() - 40) * getWage() * 1.5;
        }
    }

    @Override
    public String toString() {
        return String.format(
                "Hourly Employee:\n Name: %s %s\n Social Number: %d\n Wage: %.2f\n Hours: %.2f\n BirthDate %s",
                getFirstName(), getLastName(),
                getSocialSecurityNumber(),
                getWage(), getHours(), getBirthDate());
    }
}
