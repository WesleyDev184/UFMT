package entidades;

public class Ortopedista extends Medico {

	@Override
	public void operar() {
		System.out.println("Operar do Ortopedista");
	}

	public void metodoOrtopedista() {
		System.out.println("Metodo exclusivo da classe Ortopedista");
	}

}
