package dao.MedicosDAO;

import java.util.List;
import java.util.Scanner;

import entidades.Medico;

public class TestesMedico {
  public static void main(String[] args) {
    try {
      MedicoDAO medicoDAO = new MedicoDAO();
      Scanner scanner = new Scanner(System.in);

      List<Medico> medicos = medicoDAO.listDoctor();

      int opcao;
      do {
        System.out.println("1 - Listar médicos");
        System.out.println("2 - Cadastrar médico");
        System.out.println("3 - Atualizar médico");
        System.out.println("4 - Remover médico");
        System.out.println("5 - Pesquisar médico");
        System.out.println("0 - Sair");
        System.out.println("\nDigite a opção desejada: ");
        opcao = scanner.nextInt();

        switch (opcao) {
          case 1:
            for (Medico medico : medicos) {
              System.out.println(medico);
            }
            break;
          case 2:
            System.out.println("Digite o nome do médico: ");
            String nome = scanner.next();
            System.out.println("Digite o CRM do médico: ");
            int crm = scanner.nextInt();
            System.out.println("Digite o valor da hora do médico: ");
            double valorHora = scanner.nextDouble();
            System.out.println("Digite a especialidade do médico: ");
            String especialidade = scanner.next();
            System.out.println("Digite a data de nascimento do médico dia/mes/ano : ");
            String dataNascimento = scanner.next();

            Medico medico = medicoDAO.createMedico(nome, crm, valorHora, especialidade);
            medico.setEspecialidade(especialidade);
            medico.setDataNascimento(dataNascimento);

            System.out.println(medico);

            if (medico != null) {
              medicoDAO.insertDoctor(medico);
            }
            break;
          case 3:
            System.out.println("Digite o CRM do médico: ");
            crm = scanner.nextInt();
            System.out.println("Digite o novo valor da hora do médico: ");
            valorHora = scanner.nextDouble();

            medicoDAO.updateDoctor(crm, valorHora);
            break;
          case 4:
            System.out.println("Digite o CRM do médico: ");
            crm = scanner.nextInt();

            medicoDAO.deleteDoctor(crm);
            break;

          case 5:
            System.out.println("Digite o CRM ou o nome do médico: ");
            String pesquisa = scanner.next();

            Medico medicoPesquisado = medicoDAO.searchDoctor(pesquisa);
            if (medicoPesquisado != null) {
              System.out.println(medicoPesquisado);
            } else {
              System.out.println("Médico não encontrado!");
            }
            break;

          case 0:
            System.out.println("Saindo...");
            break;
          default:
            System.out.println("Opção inválida!");
            break;
        }
      } while (opcao != 0);

      scanner.close();
    } catch (Exception e) {
      e.printStackTrace();
    }
  }

}
