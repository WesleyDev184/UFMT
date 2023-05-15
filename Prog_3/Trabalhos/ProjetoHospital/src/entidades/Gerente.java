package entidades;

public class Gerente extends Funcionario {
	private String CRA;

	public String getCRA() {
		return CRA;
	}

	public void setCRA(String cRA) {
		CRA = cRA;
	}

	public void liberarPagamento() {
		System.out.println("Liberar Pagamento");
	}
}
