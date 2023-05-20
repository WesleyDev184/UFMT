package entidades;

public class Otorrinolaringologista extends Medico {

  public Otorrinolaringologista(String nome, int cRM, double valorHora) {
  }

  @Override
  public void operar() {
    System.out.println("Operar do Otorrinolaringologista");
  }
}
