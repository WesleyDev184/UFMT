package entidades;

public class Ortopedista extends Medico {

	public Ortopedista(String nome, int cRM, double valorHora) {
	}

	@Override
	public void operar() {
		System.out.println("Operar do Ortopedista");
	}

	public void metodoOrtopedista() {
		System.out.println("Metodo exclusivo da classe Ortopedista");
	}

}
