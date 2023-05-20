package entidades;

public class ResidenteAnestesista extends Anestesista {

	public ResidenteAnestesista(String nome, int cRM, double valorHora) {
		super(nome, cRM, valorHora);
		// TODO Auto-generated constructor stub
	}

	public void metodoExclusivo() {
		System.out.println("Metodo exclusivo da classe ResidenteAnestesista");
	}

	@Override
	public void operar() {
		System.out.println("Operar do Residente!!!!");
	}
}
