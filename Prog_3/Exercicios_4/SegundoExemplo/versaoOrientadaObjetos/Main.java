public class Main {

	private static Produto[] produtos;
	private static Vendedor[] vendedores;
	private static Cliente[] clientes;
	private static Pedido pedido;

	private static void criarDadosTeste() {

		Produto p1 = new Produto(1, "Mesa", 10, 500);
		Produto p2 = new Produto(2, "Cadeira", 20, 150);
		Produto p3 = new Produto(3, "Fog�o", 5, 1000);
		Produto p4 = new Produto(4, "Sof�", 4, 2000);
		produtos = new Produto[] { p1, p2, p3, p4 };

		Vendedor v1 = new Vendedor(1, "Ademar", 0.1f);
		Vendedor v2 = new Vendedor(2, "Ros�lia", 0.2f);
		vendedores = new Vendedor[] { v1, v2 };

		Cliente c1 = new Cliente(1, "Jo�o", "Rua X, 100");
		Cliente c2 = new ClienteEspecial(2, "Carlos", "Rua Y, 200", 10);
		Cliente c3 = new Cliente(3, "Carina", "Rua Z, 400");
		clientes = new Cliente[] { c1, c2, c3 };

		ItemVenda i1 = new ItemVenda(1, p1, 10);
		ItemVenda i2 = new ItemVenda(6, p2, 15);
		ItemVenda i3 = new ItemVenda(1, p3, 5);
		ItemVenda[] itens = new ItemVenda[] { i1, i2, i3 };

		pedido = new Pedido(c2, v1, itens);
	}

	public static void main(String[] args) {
		System.out.println("Iniciando Venda (5).");
		criarDadosTeste();
		pedido.realizarVenda();
		System.out.println("Venda Concluida.");
	}
}