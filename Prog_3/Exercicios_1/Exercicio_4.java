public class Exercicio_4 {
    public static void main(String[] args) {
        int currentPopulation = 788800000;
        double growthRate = 0.09;

        for (int i = 1; i <= 5; i++) {
            int estimatedPopulation = (int) (currentPopulation * (1 + growthRate));
            System.out.println("Estimativa populacional em " + i + " ano: " + estimatedPopulation);
            currentPopulation = estimatedPopulation;
        }
    }
}

