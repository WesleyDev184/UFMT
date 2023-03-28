public class Main {
    public static void main(String[] args) {
        Forma[] formas = new Forma[4];
        formas[0] = new Esfera(2);
        formas[1] = new Cubo(2);
        formas[2] = new Quadrado(2);
        formas[3] = new Circulo(2);

        for (Forma forma : formas) {
            System.out.println(forma.getArea());
        }
    }
}