package entidades;

public class Dermatologista extends Medico {

  public Dermatologista(String nome, int cRM, double valorHora) {
  }

  @Override
  public void operar() {
    System.out.println("Operar do Dermatologista");
  }

}
