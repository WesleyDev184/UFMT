import org.apache.xmlrpc.server.PropertyHandlerMapping;
import org.apache.xmlrpc.server.XmlRpcServer;
import org.apache.xmlrpc.webserver.WebServer;

public class ServidorFilial {

    public static void main(String[] args) {
        try {
            System.out.println("Iniciando o servidor da filial na porta 8080...");

            WebServer webServer = new WebServer(8080);
            XmlRpcServer xmlRpcServer = webServer.getXmlRpcServer();

            PropertyHandlerMapping phm = new PropertyHandlerMapping();
            phm.addHandler("vendas", ServidorVendas.class);
            xmlRpcServer.setHandlerMapping(phm);

            webServer.start();
            System.out.println("Servidor da filial iniciado com sucesso.");
            System.out.println("Pronto para receber chamadas de RPC."); 

            // Exibe as filiais disponíveis a partir do handler ServidorVendas
            try {
                ServidorVendas sv = new ServidorVendas();
                String[] filiais = sv.listarFiliaisDisponiveis();
                System.out.println("Filiais disponíveis: " + java.util.Arrays.toString(filiais));
            } catch (Throwable t) {
                System.err.println("Aviso: não foi possível listar filiais: " + t.getMessage());
            }

        } catch (Exception e) {
            System.err.println("Erro no servidor da filial: " + e.getMessage());
            e.printStackTrace();
        }
    }
}