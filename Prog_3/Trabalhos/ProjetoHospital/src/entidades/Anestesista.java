package entidades;

public class Anestesista extends Medico {

	@Override
	public void operar() {
		System.out.println("Operar do Anestesista");
	}

	public void metodoAnestesista() {
		System.out.println("Metodo de Anestesista");
	}
}
