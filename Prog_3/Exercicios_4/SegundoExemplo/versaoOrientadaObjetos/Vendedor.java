public class Vendedor extends Pessoa {

	private float percentualComissao;

	public Vendedor(int codigo, String nome, float percentualComissao) {
		super(codigo, nome);
		this.percentualComissao = percentualComissao;
	}

	public float getPercentualComissao() {
		return percentualComissao;
	}

	public void setPercentualComissao(float percentualComissao) {
		this.percentualComissao = percentualComissao;
	}
}