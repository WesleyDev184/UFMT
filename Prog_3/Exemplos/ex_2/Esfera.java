public class Esfera extends FormaTridimencional {
    public Esfera(double raio) {
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

    public double getArea() {
        return 4 * Math.PI * Math.pow(getRaio(), 2);
    }

    public double getVolume() {
        return (4 * Math.PI * Math.pow(getRaio(), 3)) / 3;
    }
}
