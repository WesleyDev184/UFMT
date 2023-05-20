package entidades;

public class Endocrinologista extends Medico {

  public Endocrinologista(String nome, int cRM, double valorHora) {
  }

  @Override
  public void operar() {
    System.out.println("Operar do Endocrinologista");
  }
}
