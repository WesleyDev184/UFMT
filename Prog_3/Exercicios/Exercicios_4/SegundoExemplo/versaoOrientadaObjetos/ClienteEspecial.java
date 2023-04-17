public class ClienteEspecial extends Cliente {

	private float percentualDescontoClienteEspecial;

	public ClienteEspecial(int codigo, String nome, String endereco,
			float percentualDescontoClienteEspecial) {
		super(codigo, nome, endereco);
		this.percentualDescontoClienteEspecial = percentualDescontoClienteEspecial;
	}

	public float getPercentualDescontoClienteEspecial() {
		return percentualDescontoClienteEspecial;
	}

	public void setPercentualDescontoClienteEspecial(float percentualDescontoClienteEspecial) {
		this.percentualDescontoClienteEspecial = percentualDescontoClienteEspecial;
	}

	public float calculaDescontoPedido(float totalPedido) {
		return totalPedido * percentualDescontoClienteEspecial / 100;
	}
}