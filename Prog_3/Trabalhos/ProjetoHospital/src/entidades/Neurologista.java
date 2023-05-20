package entidades;

public class Neurologista extends Medico {

  public Neurologista(String nome, int cRM, double valorHora) {
  }

  @Override
  public void operar() {
    System.out.println("Operar do Neurologista");
  }
}
