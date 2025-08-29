public class Filial {
    private String id;
    private double totalVendasDiarias;
    private String[] produtosMaisVendidos;

    public Filial(String id, double totalVendasDiarias, String[] produtosMaisVendidos) {
        this.id = id;
        this.totalVendasDiarias = totalVendasDiarias;
        this.produtosMaisVendidos = produtosMaisVendidos == null ? new String[0] : produtosMaisVendidos.clone();
    }

    public String getId() {
        return id;
    }

    public double getTotalVendasDiarias() {
        return totalVendasDiarias;
    }

    public String[] getProdutosMaisVendidos() {
        return produtosMaisVendidos.clone();
    }

    public Object[] getTopProdutos(int quantidade) {
        if (quantidade <= 0 || produtosMaisVendidos.length == 0) return new Object[0];
        if (quantidade >= produtosMaisVendidos.length) return produtosMaisVendidos.clone();
        return java.util.Arrays.copyOfRange(produtosMaisVendidos, 0, quantidade);
    }

    @Override
    public String toString() {
        return "Filial{" + "id='" + id + '\'' + ", totalVendasDiarias=" + totalVendasDiarias + ", produtos=" + java.util.Arrays.toString(produtosMaisVendidos) + '}';
    }
}
