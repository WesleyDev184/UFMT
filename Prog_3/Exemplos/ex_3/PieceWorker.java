public class PieceWorker extends Employee {
    private double wage;
    private int pieces;

    public PieceWorker(String FirstName, String LastName, int SocialSecurityNumber, double wage, int pieces,
            BirthDate birthDate) {
        super(FirstName, LastName, SocialSecurityNumber, birthDate);
        this.wage = wage;
        this.pieces = pieces;
    }

    public double getWage() {
        return wage;
    }

    public void setWage(double wage) {
        this.wage = wage;
    }

    public double getPieces() {
        return pieces;
    }

    public void setPieces(int pieces) {
        this.pieces = pieces;
    }

    @Override
    public double earnings() {
        return getWage() * getPieces();
    }

    @Override
    public String toString() {
        return String.format(
                "Piece Worker:\n Name: %s %s\n Social Number: %d\n Wage: %.2f\n Pieces: %.2f\n BirthDate %s",
                getFirstName(), getLastName(),
                getSocialSecurityNumber(),
                getWage(), getPieces(), getBirthDate());
    }
}
