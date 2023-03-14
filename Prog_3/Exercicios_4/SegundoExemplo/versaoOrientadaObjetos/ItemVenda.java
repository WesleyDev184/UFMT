public class ItemVenda {

	private int quantidade;
	private Produto produto;
	private float percentualDesconto;

	public ItemVenda(int quantidade, Produto produto, float percentualDesconto) {
		this.quantidade = quantidade;
		this.produto = produto;
		this.percentualDesconto = percentualDesconto;
	}

	public int getQuantidade() {
		return quantidade;
	}

	public void setQuantidade(int quantidade) {
		this.quantidade = quantidade;
	}

	public Produto getProduto() {
		return produto;
	}

	public void setProduto(Produto produto) {
		this.produto = produto;
	}

	public float getPercentualDesconto() {
		return percentualDesconto;
	}

	public void setPercentualDesconto(float percentualDesconto) {
		this.percentualDesconto = percentualDesconto;
	}

	public float calcularValorTotalItemSemDesconto() {
		return quantidade * produto.getValor();
	}

	public float calcularDescontoItem() {
		float totalItem = calcularValorTotalItemSemDesconto();
		float desconto = totalItem * percentualDesconto;
		return desconto;
	}

	public float calcularValorTotalItem() {
		return calcularValorTotalItemSemDesconto() - calcularDescontoItem();
	}
}