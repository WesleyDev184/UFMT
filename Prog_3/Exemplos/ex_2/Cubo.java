public class Cubo extends FormaTridimencional {

    public Cubo(double lado) {
        super(0, lado);
    }

    @Override
    public double getLado() {
        return super.getLado();
    }

    @Override
    public void setLado(double lado) {
        super.setLado(lado);
    }

    public double getArea() {
        return 6 * Math.pow(getLado(), 2);
    }

    public double getVolume() {
        return Math.pow(getLado(), 3);
    }
}
