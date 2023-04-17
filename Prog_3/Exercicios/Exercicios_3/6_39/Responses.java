public class Responses {
    public static void badResponses(int index) {
        String[] badResponses = { "Não. Por favor, tente novamente.", "Errado. Tente mais uma vez.", "Não desista!",
                "Não. Continue tentando." };

        switch (index) {
            case 0:
                System.out.println(badResponses[0]);
                break;
            case 1:
                System.out.println(badResponses[1]);
                break;
            case 2:
                System.out.println(badResponses[2]);
                break;
            case 3:
                System.out.println(badResponses[3]);
                break;
            default:
                System.out.println("Opção inválida. Tente novamente.");
                break;
        }

    }

    public static void goodResponses(int index) {
        String[] goodResponses = { "Muito bom!", "Excelente!", "Bom trabalho!", "Mantenha um bom trabalho!" };

        switch (index) {
            case 0:
                System.out.println(goodResponses[0]);
                break;
            case 1:
                System.out.println(goodResponses[1]);
                break;
            case 2:
                System.out.println(goodResponses[2]);
                break;
            case 3:
                System.out.println(goodResponses[3]);
                break;
            default:
                System.out.println("Opção inválida. Tente novamente.");
                break;
        }
    }
}
