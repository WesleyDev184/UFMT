package Person;

public class Address {

    private String PublicPlace;
    private int Number;
    private int CEP;
    private String Neighborhood;

    public Address(String PublicPlace, int Number, int CEP, String Neighborhood) {
        this.PublicPlace = PublicPlace;
        this.Number = Number;
        this.CEP = CEP;
        this.Neighborhood = Neighborhood;
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

    public int getCEP() {
        return CEP;
    }

    public void setCEP(int CEP) {
        this.CEP = CEP;
    }

    public String getNeighborhood() {
        return Neighborhood;
    }

    public void setNeighborhood(String Neighborhood) {
        this.Neighborhood = Neighborhood;
    }

}
