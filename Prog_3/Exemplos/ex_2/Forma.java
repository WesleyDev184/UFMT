public class Forma {
    private double raio;
    private double lado;

    public Forma(double raio, double lado) {
        this.raio = raio;
        this.lado = lado;
    }

    public double getRaio() {
        return raio;
    }

    public void setRaio(double raio) {
        this.raio = raio;
    }

    public double getLado() {
        return lado;
    }

    public void setLado(double lado) {
        this.lado = lado;
    }

    public double getArea() {
        return 0;
    }

    public double getVolume() {
        return 0;
    }

    public double getPerimetro() {
        return 0;
    }
}
