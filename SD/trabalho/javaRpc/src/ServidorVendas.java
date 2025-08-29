import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class ServidorVendas {

    private List<Filial> filiais;

    public ServidorVendas() {
        filiais = new ArrayList<>();

        filiais.add(new Filial("A", 2500.50, new String[]{"Notebook", "Mouse sem fio", "Teclado Mecânico", "Monitor 4K"}));
        filiais.add(new Filial("B", 4150.75, new String[]{"Smartphone", "Capa para celular", "Fone Bluetooth", "Carregador USB-C"}));
        filiais.add(new Filial("C", 980.00, new String[]{"Cabo HDMI", "Filtro de linha", "Webcam", "Microfone USB"}));
        filiais.add(new Filial("D", 6120.40, new String[]{"SSD 1TB", "HD Externo", "Placa de Vídeo", "Fonte ATX"}));
        filiais.add(new Filial("E", 1750.10, new String[]{"Tablet", "Caneta Stylus", "Capa Tablet", "Suporte"}));
        filiais.add(new Filial("F", 3033.33, new String[]{"Impressora", "Toner", "Papel A4", "Scanner"}));
        filiais.add(new Filial("G", 489.99, new String[]{"Cartucho de Tinta", "Adaptador", "Hub USB"}));
        filiais.add(new Filial("H", 8540.20, new String[]{"Desktop Gamer", "Monitor Curvo", "Cadeira Gamer", "Teclado RGB"}));
    }

    private Filial findFilial(String id) {
        if (id == null) return null;
        for (Filial f : filiais) {
            if (id.equals(f.getId())) return f;
        }
        return null;
    }

    public double obterTotalVendasDiarias(String filialId) {
        System.out.println("Recebida chamada para obterTotalVendasDiarias para a filial: " + filialId);
        Filial f = findFilial(filialId);
        return f == null ? 0.0 : f.getTotalVendasDiarias();
    }

    public Object[] listarProdutosMaisVendidos(String filialId, int quantidade) {
        System.out.println("Recebida chamada para listarProdutosMaisVendidos para a filial: " + filialId + " com quantidade: " + quantidade);
        Filial f = findFilial(filialId);
        if (f == null) return new Object[0];
        return f.getTopProdutos(quantidade);
    }

    public String[] listarFiliaisDisponiveis() {
        String[] ids = new String[filiais.size()];
        for (int i = 0; i < filiais.size(); i++) ids[i] = filiais.get(i).getId();
        return ids;
    }

    @Override
    public String toString() {
        return "ServidorVendas{filiais=" + Arrays.toString(listarFiliaisDisponiveis()) + '}';
    }
}