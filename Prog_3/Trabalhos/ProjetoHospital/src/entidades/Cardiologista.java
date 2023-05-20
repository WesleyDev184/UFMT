package entidades;

public class Cardiologista extends Medico {

	public Cardiologista(String nome, int cRM, double valorHora) {
	}

	@Override
	public void operar() {
		System.out.println("Operar do Cardiologista");

	}

}
