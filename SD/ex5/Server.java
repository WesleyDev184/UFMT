import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;
import java.util.UUID;
import java.util.Vector;
import java.util.concurrent.ConcurrentHashMap;

public class Server implements Banco {
    private Vector<Conta> contas;
    private ConcurrentHashMap<String, Integer> sessoes; // sessionId -> numeroConta

    public Server() {
        contas = new Vector<>();
        sessoes = new ConcurrentHashMap<>();
        
        // Criar 5 contas iniciais
        for (int i = 0; i < 5; i++) {
            contas.add(new Conta(i));
        }
        System.out.println("Servidor iniciado com " + contas.size() + " contas.");
    }
    
    @Override
    public String conectarConta(int numeroConta) throws RemoteException {
        if (numeroConta < 0 || numeroConta >= contas.size()) {
            throw new RemoteException("Número de conta inválido: " + numeroConta);
        }
        
        String sessionId = UUID.randomUUID().toString();
        sessoes.put(sessionId, numeroConta);
        
        System.out.println("Cliente conectado à conta " + numeroConta + " com sessão: " + sessionId);
        return sessionId;
    }
    
    @Override
    public boolean validarSessao(String sessionId) throws RemoteException {
        return sessionId != null && sessoes.containsKey(sessionId);
    }
    
    private Conta obterContaDaSessao(String sessionId) throws RemoteException {
        if (!validarSessao(sessionId)) {
            throw new RemoteException("Sessão inválida ou expirada");
        }
        
        Integer numeroConta = sessoes.get(sessionId);
        return contas.get(numeroConta);
    }

    @Override
    public double getSaldo(String sessionId) throws RemoteException {
        Conta conta = obterContaDaSessao(sessionId);
        return conta.getSaldo();
    }

    @Override
    public String getExtrato(String sessionId) throws RemoteException {
        Conta conta = obterContaDaSessao(sessionId);
        return conta.getExtrato();
    }

    @Override
    public boolean depositar(String sessionId, double valor) throws RemoteException {
        Conta conta = obterContaDaSessao(sessionId);
        return conta.depositar(valor);
    }

    @Override
    public boolean sacar(String sessionId, double valor) throws RemoteException {
        Conta conta = obterContaDaSessao(sessionId);
        return conta.sacar(valor);
    }

    @Override
    public boolean transferir(String sessionId, int contaDestino, double valor) throws RemoteException {
        if (contaDestino < 0 || contaDestino >= contas.size()) {
            throw new RemoteException("Conta destino inválida: " + contaDestino);
        }
        
        Conta contaOrigem = obterContaDaSessao(sessionId);
        Conta contaDest = contas.get(contaDestino);
        
        return contaOrigem.transferirPara(contaDest, valor);
    }
    
    @Override
    public String[] listarContas() throws RemoteException {
        String[] lista = new String[contas.size()];
        for (int i = 0; i < contas.size(); i++) {
            lista[i] = contas.get(i).toString();
        }
        return lista;
    }
    
    @Override
    public void desconectar(String sessionId) throws RemoteException {
        if (sessoes.remove(sessionId) != null) {
            System.out.println("Cliente desconectado da sessão: " + sessionId);
        }
    }

    public static void main(String[] args) {
        try {
            Server obj = new Server();
            Banco stub = (Banco) UnicastRemoteObject.exportObject(obj, 0);
            Registry registry = LocateRegistry.createRegistry(1099);
            registry.rebind("Banco", stub);
            System.out.println("Servidor pronto!");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}