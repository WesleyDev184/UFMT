import java.net.URL;
import java.util.Arrays;
import java.util.List;
import java.util.Scanner;

import org.apache.xmlrpc.client.XmlRpcClient;
import org.apache.xmlrpc.client.XmlRpcClientConfigImpl;

public class ClienteMonitoramento {

    public static void main(String[] args) {

        Scanner scanner = new Scanner(System.in);

        List<String> filiais = Arrays.asList(
                "A", "B", "C", "D",
                "E", "F", "G", "H"
        );

        System.out.print("Digite o IP/host do servidor (enter = localhost): ");
        String hostInput = scanner.nextLine().trim();
        if (hostInput.isEmpty()) {
            hostInput = "127.0.0.1";
        }

        try {
            // Configuração do cliente para se conectar ao servidor
            String serverUrl = String.format("http://%s:8080/xmlrpc", hostInput);
            XmlRpcClientConfigImpl config = new XmlRpcClientConfigImpl();
            config.setServerURL(new URL(serverUrl));
            XmlRpcClient client = new XmlRpcClient();
            client.setConfig(config);

            boolean sair = false;
            while (!sair) {
                System.out.println("\n--- Menu de Monitoramento ---");
                System.out.println("1) Ver total de vendas de uma filial");
                System.out.println("2) Ver total de vendas de todas as filiais (ampliado)");
                System.out.println("3) Listar produtos mais vendidos de uma filial");
                System.out.println("4) Listar top N produtos para todas as filiais (ampliado)");
                System.out.println("5) Sair");
                System.out.print("Escolha uma opção: ");

                String opc = scanner.nextLine().trim();
                switch (opc) {
                    case "1": {
                        System.out.print("Digite o ID da filial (ex: A): ");
                        String id = scanner.nextLine().trim();
                        try {
                            Object[] params = new Object[]{id};
                            Object resp = client.execute("vendas.obterTotalVendasDiarias", params);
                            double total = asDouble(resp);
                            System.out.printf("Vendas totais da %s: R$ %.2f\n", id, total);
                        } catch (Exception e) {
                            System.err.println("Erro ao obter vendas: " + e.getMessage());
                        }
                        break;
                    }
                    case "2": {
                        System.out.println("Totais das filiais:");
                        for (String id : filiais) {
                            try {
                                Object[] params = new Object[]{id};
                                Object resp = client.execute("vendas.obterTotalVendasDiarias", params);
                                double total = asDouble(resp);
                                System.out.printf("  Filial %s: R$ %.2f\n", id, total);
                            } catch (Exception e) {
                                System.err.printf("  Erro na %s: %s\n", id, e.getMessage());
                            }
                        }
                        break;
                    }
                    case "3": {
                        System.out.print("Digite o ID da filial (ex: A): ");
                        String id = scanner.nextLine().trim();
                        System.out.print("Quantos produtos (N): ");
                        int n = parseIntOrDefault(scanner.nextLine().trim(), 5);
                        try {
                            Object[] params = new Object[]{id, n};
                            Object[] produtos = (Object[]) client.execute("vendas.listarProdutosMaisVendidos", params);
                            System.out.println("Produtos mais vendidos na " + id + ":");
                            printArrayProdutos(produtos);
                        } catch (Exception e) {
                            System.err.println("Erro ao listar produtos: " + e.getMessage());
                        }
                        break;
                    }
                    case "4": {
                        System.out.print("Quantos top produtos por filial (N): ");
                        int n = parseIntOrDefault(scanner.nextLine().trim(), 3);
                        for (String id : filiais) {
                            try {
                                Object[] params = new Object[]{id, n};
                                Object[] produtos = (Object[]) client.execute("vendas.listarProdutosMaisVendidos", params);
                                System.out.println("\n Filial " + id + ":");
                                printArrayProdutos(produtos);
                            } catch (Exception e) {
                                System.err.printf("  Erro na %s: %s\n", id, e.getMessage());
                            }
                        }
                        break;
                    }
                    case "5": {
                        sair = true;
                        break;
                    }
                    default:
                        System.out.println("Opção inválida. Tente novamente.");
                }
            }

        } catch (Exception e) {
            System.err.println("Erro no cliente de monitoramento: " + e.getMessage());
            e.printStackTrace();
        } finally {
            scanner.close();
        }
    }

    private static double asDouble(Object resp) {
        if (resp == null) return 0.0;
        if (resp instanceof Number) return ((Number) resp).doubleValue();
        try {
            return Double.parseDouble(resp.toString());
        } catch (NumberFormatException e) {
            return 0.0;
        }
    }

    private static int parseIntOrDefault(String s, int def) {
        try {
            return Integer.parseInt(s);
        } catch (NumberFormatException e) {
            return def;
        }
    }

    private static void printArrayProdutos(Object[] produtos) {
        if (produtos == null || produtos.length == 0) {
            System.out.println("  (nenhum produto retornado)");
            return;
        }
        for (int i = 0; i < produtos.length; i++) {
            Object p = produtos[i];
            System.out.printf("  %d) %s\n", i + 1, p == null ? "null" : p.toString());
        }
    }
}