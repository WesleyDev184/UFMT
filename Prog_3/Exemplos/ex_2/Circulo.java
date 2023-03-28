public class Circulo extends FormaBidimencional {
    public Circulo(double raio) {
        super(raio, 0);
    }

    @Override
    public double getRaio() {
        return super.getRaio();
    }

    @Override
    public void setRaio(double raio) {
        super.setRaio(raio);
    }

    @Override
    public double getArea() {
        return Math.PI * Math.pow(getRaio(), 2);
    }

    @Override
    public double getPerimetro() {
        return 2 * Math.PI * getRaio();
    }
}
