package entidades;

public class Ginecologia extends Medico {

  public Ginecologia(String nome, int cRM, double valorHora) {
  }

  @Override
  public void operar() {
    System.out.println("Operar do Ginecologia");
  }
}
