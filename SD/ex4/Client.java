import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.util.Scanner;

public class Client {
    private static String sessionId = null;
    private static Banco bancoRef = null;
    private static Scanner sc = new Scanner(System.in);
    
    public static void main(String[] args) {
        String host = args.length > 0 ? args[0] : "localhost";
        
        try {
            Registry registry = LocateRegistry.getRegistry(host, 1099);
            bancoRef = (Banco) registry.lookup("Banco");
            
            // Conectar à conta
            if (!conectarConta()) {
                System.out.println("Não foi possível conectar. Encerrando...");
                return;
            }
            
            // Menu principal
            menuPrincipal();
            
        } catch (Exception e) {
            System.err.println("Erro ao conectar com o servidor: " + e.getMessage());
            e.printStackTrace();
        } finally {
            // Desconectar ao sair
            desconectar();
            sc.close();
        }
    }
    
    private static boolean conectarConta() {
        System.out.println("\n=== CONEXÃO AO SISTEMA BANCÁRIO ===");
        
        try {
            // Listar contas disponíveis
            String[] contas = bancoRef.listarContas();
            System.out.println("\nContas disponíveis:");
            for (int i = 0; i < contas.length; i++) {
                System.out.println(i + " - " + contas[i]);
            }
            
            System.out.print("\nDigite o número da conta para conectar (0-" + (contas.length-1) + "): ");
            int numeroConta;
            
            try {
                numeroConta = sc.nextInt();
                sc.nextLine(); // limpar buffer
            } catch (Exception e) {
                System.out.println("Entrada inválida!");
                sc.nextLine();
                return false;
            }
            
            // Tentar conectar
            sessionId = bancoRef.conectarConta(numeroConta);
            System.out.println("Conectado com sucesso à conta " + numeroConta + "!");
            return true;
            
        } catch (RemoteException e) {
            System.out.println("Erro ao conectar: " + e.getMessage());
            return false;
        }
    }
    
    private static void menuPrincipal() {
        while (true) {
            try {
                // Verificar se a sessão ainda é válida
                if (!bancoRef.validarSessao(sessionId)) {
                    System.out.println("Sessão expirada. Reconectando...");
                    if (!conectarConta()) {
                        break;
                    }
                }
                
                System.out.println("\n=== MENU PRINCIPAL ===");
                System.out.println("1 - Consultar Saldo");
                System.out.println("2 - Extrato");
                System.out.println("3 - Depositar");
                System.out.println("4 - Sacar");
                System.out.println("5 - Transferir");
                System.out.println("6 - Trocar de Conta");
                System.out.println("0 - Sair");
                System.out.print("Opção: ");
                
                int op;
                try {
                    op = sc.nextInt();
                    sc.nextLine(); // limpar buffer
                } catch (Exception e) {
                    System.out.println("Entrada inválida!");
                    sc.nextLine();
                    continue;
                }

                if (op == 0) break;
                
                if (op == 6) {
                    desconectar();
                    if (!conectarConta()) {
                        break;
                    }
                    continue;
                }

                executarOperacao(op);
                
            } catch (RemoteException e) {
                System.out.println("Erro na comunicação com o servidor: " + e.getMessage());
                System.out.println("Tentando reconectar...");
                
                // Tentar reconectar
                if (!conectarConta()) {
                    break;
                }
            }
        }
    }
    
    private static void executarOperacao(int operacao) {
        try {
            switch (operacao) {
                case 1: // Consultar Saldo
                    double saldo = bancoRef.getSaldo(sessionId);
                    System.out.printf("Saldo atual: R$ %.2f%n", saldo);
                    break;
                    
                case 2: // Extrato
                    String extrato = bancoRef.getExtrato(sessionId);
                    System.out.println("\n=== EXTRATO ===");
                    System.out.println(extrato);
                    break;
                    
                case 3: // Depositar
                    System.out.print("Valor do depósito: R$ ");
                    double valorDep = sc.nextDouble();
                    boolean depOk = bancoRef.depositar(sessionId, valorDep);
                    System.out.println(depOk ? "Depósito realizado com sucesso!" : "Erro no depósito!");
                    break;
                    
                case 4: // Sacar
                    System.out.print("Valor do saque: R$ ");
                    double valorSaq = sc.nextDouble();
                    boolean saqOk = bancoRef.sacar(sessionId, valorSaq);
                    System.out.println(saqOk ? "Saque realizado com sucesso!" : "Erro no saque (saldo insuficiente?)!");
                    break;
                    
                case 5: // Transferir
                    try {
                        String[] contas = bancoRef.listarContas();
                        System.out.println("\nContas disponíveis para transferência:");
                        for (int i = 0; i < contas.length; i++) {
                            System.out.println(i + " - " + contas[i]);
                        }
                        
                        System.out.print("Conta destino (0-" + (contas.length-1) + "): ");
                        int contaDest = sc.nextInt();
                        System.out.print("Valor da transferência: R$ ");
                        double valorTransf = sc.nextDouble();
                        
                        boolean transfOk = bancoRef.transferir(sessionId, contaDest, valorTransf);
                        System.out.println(transfOk ? "Transferência realizada com sucesso!" : "Erro na transferência (saldo insuficiente?)!");
                    } catch (Exception e) {
                        System.out.println("Erro na entrada de dados: " + e.getMessage());
                        sc.nextLine(); // limpar buffer
                    }
                    break;
                    
                default:
                    System.out.println("Opção inválida!");
            }
        } catch (RemoteException e) {
            System.out.println("Erro na operação: " + e.getMessage());
        } catch (Exception e) {
            System.out.println("Erro: " + e.getMessage());
            sc.nextLine(); // limpar buffer
        }
    }
    
    private static void desconectar() {
        if (sessionId != null && bancoRef != null) {
            try {
                bancoRef.desconectar(sessionId);
                System.out.println("Desconectado com sucesso!");
            } catch (RemoteException e) {
                System.out.println("Erro ao desconectar: " + e.getMessage());
            }
            sessionId = null;
        }
    }
}