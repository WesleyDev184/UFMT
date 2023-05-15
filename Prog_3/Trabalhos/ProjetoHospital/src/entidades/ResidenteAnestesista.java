package entidades;

public class ResidenteAnestesista extends Anestesista {

	public void metodoExclusivo() {
		System.out.println("Metodo exclusivo da classe ResidenteAnestesista");
	}

	@Override
	public void operar() {
		System.out.println("Operar do Residente!!!!");
		// super.operar();
	}
}
