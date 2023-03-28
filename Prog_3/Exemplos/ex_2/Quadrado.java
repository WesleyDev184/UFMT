public class Quadrado extends FormaBidimencional {
    public Quadrado(double lado) {
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

    @Override
    public double getArea() {
        return Math.pow(getLado(), 2);
    }

    @Override
    public double getPerimetro() {
        return 4 * getLado();
    }
}
