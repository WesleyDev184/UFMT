import java.rmi.Remote;
import java.rmi.RemoteException;

public interface Banco extends Remote {
    // Métodos para autenticação/sessão
    String conectarConta(int numeroConta) throws RemoteException;
    boolean validarSessao(String sessionId) throws RemoteException;
    
    // Métodos bancários com identificação de sessão
    double getSaldo(String sessionId) throws RemoteException;
    String getExtrato(String sessionId) throws RemoteException;
    boolean depositar(String sessionId, double valor) throws RemoteException;
    boolean sacar(String sessionId, double valor) throws RemoteException;
    boolean transferir(String sessionId, int contaDestino, double valor) throws RemoteException;
    
    // Métodos de utilidade
    String[] listarContas() throws RemoteException;
    void desconectar(String sessionId) throws RemoteException;
}