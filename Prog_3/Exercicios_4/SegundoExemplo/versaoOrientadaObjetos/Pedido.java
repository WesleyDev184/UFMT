public class Pedido {

	private Cliente cliente;
	private Vendedor vendedor;
	private ItemVenda[] itens;

	public Pedido(Cliente cliente, Vendedor vendedor, ItemVenda[] itens) {
		this.cliente = cliente;
		this.vendedor = vendedor;
		this.itens = itens;
	}

	public Cliente getCliente() {
		return cliente;
	}

	public void setCliente(Cliente cliente) {
		this.cliente = cliente;
	}

	public Vendedor getVendedor() {
		return vendedor;
	}

	public void setVendedor(Vendedor vendedor) {
		this.vendedor = vendedor;
	}

	public ItemVenda[] getItens() {
		return itens;
	}

	public void setItens(ItemVenda[] itens) {
		this.itens = itens;
	}

	public float calcularValorTotalPedido() {
		float valorTotal = 0;
		for (ItemVenda item : itens) {
			valorTotal = valorTotal + item.calcularValorTotalItem();
		}
		return valorTotal;
	}

	public float calcularComissaoPedido() {

		if (cliente instanceof ClienteEspecial) {
			ClienteEspecial clienteEspecial = (ClienteEspecial) cliente;
			float totalPedido = calcularValorTotalPedido();
			return (totalPedido - clienteEspecial.calculaDescontoPedido(totalPedido))
					* vendedor.getPercentualComissao();
		} else
			return calcularValorTotalPedido() * vendedor.getPercentualComissao();
	}

	public void realizarVenda() {

		// Remover os produtos vendidos do estoque
		for (ItemVenda itemVenda : getItens()) {
			Produto produto = itemVenda.getProduto();
			String nomeProduto = produto.getNome();
			float valorProduto = produto.getValor();
			int estoqueProduto = produto.getEstoque();
			int qtdeItem = itemVenda.getQuantidade();
			float descontoItem = itemVenda.getPercentualDesconto();
			float desconto = itemVenda.calcularDescontoItem();
			float totalItem = itemVenda.calcularValorTotalItem();
			produto.saidaEstoque(qtdeItem);
			System.out.println("Item Pedido: Produto:");
			System.out.println("  Nome do produto   = " + nomeProduto);
			System.out.println("  Estoque Anterior  = " + estoqueProduto);
			System.out.println("   Quantidade Item  = " + qtdeItem);
			System.out.println("Percentual Desconto = " + descontoItem);
			System.out.println("             Valor  = " + valorProduto);
			System.out.println("    Valor Desconto  = " + desconto);
			System.out.println("        Total Item  = " + totalItem);
		}

		float totalPedido = calcularValorTotalPedido();
		float descontoPedido = 0;
		if (cliente instanceof ClienteEspecial) {

			ClienteEspecial clienteEspecial = (ClienteEspecial) cliente;
			float percentualDesconto = clienteEspecial.getPercentualDescontoClienteEspecial();
			float totalPedidoAntes = totalPedido;
			descontoPedido = clienteEspecial.calculaDescontoPedido(totalPedidoAntes);
			totalPedido = totalPedidoAntes - descontoPedido;
			System.out.println(" Percentual Desconto Cliente Especial = " + percentualDesconto);
			System.out.println(" Total Pedido Antes do Desconto       = " + totalPedidoAntes);
			System.out.println(" Valor do Desconto                    = " + descontoPedido);
			System.out.println(" Total Pedido Antes do Desconto       = " + totalPedido);
		}

		// Busca nome do vendedor e calcula comiss�o do vendedor:
		float percentualComissao = getVendedor().getPercentualComissao();
		String nomeVendedor = getVendedor().getNome();
		System.out.println("Nome do Vendedor: " + nomeVendedor);
		System.out.println("Percentual de Comiss�o: " + percentualComissao);

		// Busca nome do cliente:
		String nomeCliente = getCliente().getNome();
		String enderecoCliente = getCliente().getEndereco();
		System.out.println("Nome do Cliente: " + nomeCliente);
		System.out.println("Endere�o do Cliente: " + enderecoCliente);

		// Acessa dados totais:
		float totalComissao = calcularComissaoPedido();
		System.out.println("Valor Total do pedido: " + totalPedido);
		System.out.println("Valor Total da Comiss�o: " + totalComissao);
	}
}