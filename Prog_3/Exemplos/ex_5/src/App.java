import java.util.Scanner;

public class App {
    private static UsuarioDAO usuarioDAO;
    private static Scanner scanner;

    public static void main(String[] args) {
        usuarioDAO = new UsuarioDAO();
        scanner = new Scanner(System.in);

        exibirMenu();

        scanner.close();
        usuarioDAO.fecharConexao();
    }

    private static void exibirMenu() {
        int escolha = -1;

        while (escolha != 0) {
            System.out.println("=== MENU ===");
            System.out.println("1. Adicionar usuário");
            System.out.println("2. Atualizar usuário");
            System.out.println("3. Excluir usuário");
            System.out.println("4. Buscar usuário por ID");
            System.out.println("0. Sair");
            System.out.print("Escolha uma opção: ");
            escolha = scanner.nextInt();
            scanner.nextLine(); // Limpar o buffer do scanner

            switch (escolha) {
                case 1:
                    adicionarUsuario();
                    break;
                case 2:
                    atualizarUsuario();
                    break;
                case 3:
                    excluirUsuario();
                    break;
                case 4:
                    buscarUsuarioPorId();
                    break;
                case 0:
                    System.out.println("Encerrando o programa...");
                    break;
                default:
                    System.out.println("Opção inválida. Tente novamente.");
                    break;
            }

            System.out.println();
        }
    }

    private static void adicionarUsuario() {
        System.out.println("=== Adicionar Usuário ===");
        System.out.print("CPF: ");
        String id_String = scanner.nextLine();
        System.out.print("Nome: ");
        String nome = scanner.nextLine();
        System.out.print("Telefone: ");
        String telefone = scanner.nextLine();

        int id = Integer.parseInt(id_String);

        Usuario novoUsuario = new Usuario(id, nome, telefone);
        usuarioDAO.inserirUsuario(novoUsuario);

        System.out.println();
    }

    private static void atualizarUsuario() {
        System.out.println("=== Atualizar Usuário ===");
        System.out.print("ID do usuário: ");
        int id = scanner.nextInt();
        scanner.nextLine(); // Limpar o buffer do scanner

        Usuario usuarioExistente = usuarioDAO.buscarUsuarioPorId(id);

        if (usuarioExistente == null) {
            System.out.println("Usuário não encontrado.");
            return;
        }

        System.out.print("Novo nome: ");
        String novoNome = scanner.nextLine();
        System.out.print("Novo telefone: ");
        String novoTelefone = scanner.nextLine();

        usuarioExistente.setNome(novoNome);
        usuarioExistente.setTelefone(novoTelefone);

        usuarioDAO.atualizarUsuario(usuarioExistente);

        System.out.println();
    }

    private static void excluirUsuario() {
        System.out.println("=== Excluir Usuário ===");
        System.out.print("ID do usuário: ");
        int id = scanner.nextInt();
        scanner.nextLine(); // Limpar o buffer do scanner

        Usuario usuarioExistente = usuarioDAO.buscarUsuarioPorId(id);

        if (usuarioExistente == null) {
            System.out.println("Usuário não encontrado.");
            return;
        }

        usuarioDAO.excluirUsuario(id);

        System.out.println();
    }

    private static void buscarUsuarioPorId() {
        System.out.println("=== Buscar Usuário por ID ===");
        System.out.print("ID do usuário: ");
        int id = scanner.nextInt();
        scanner.nextLine(); // Limpar o buffer do scanner

        Usuario usuario = usuarioDAO.buscarUsuarioPorId(id);

        if (usuario == null) {
            System.out.println("Usuário não encontrado.");
        } else {
            System.out.println("ID: " + usuario.getId());
            System.out.println("Nome: " + usuario.getNome());
            System.out.println("Telefone: " + usuario.getTelefone());
        }

        System.out.println();
    }

}