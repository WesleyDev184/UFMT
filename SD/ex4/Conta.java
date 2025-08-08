import java.io.Serializable;

class Conta implements Serializable {
    private static final long serialVersionUID = 1L;
    
    private int numero;
    private double saldo;
    private StringBuilder extrato;
    
    public Conta(int numero) {
        this.numero = numero;
        this.saldo = 1000.0; // saldo inicial
        this.extrato = new StringBuilder();
        this.extrato.append("Conta ").append(numero).append(" criada com saldo de R$1000.00\n");
    }
    
    public int getNumero() {
        return numero;
    }
    
    public synchronized double getSaldo() {
        return saldo;
    }
    
    public synchronized String getExtrato() {
        return extrato.toString();
    }
    
    public synchronized boolean depositar(double valor) {
        if (valor <= 0) return false;
        saldo += valor;
        extrato.append("Depósito: +R$").append(String.format("%.2f", valor)).append("\n");
        return true;
    }
    
    public synchronized boolean sacar(double valor) {
        if (valor <= 0 || saldo < valor) return false;
        saldo -= valor;
        extrato.append("Saque: -R$").append(String.format("%.2f", valor)).append("\n");
        return true;
    }
    
    public synchronized boolean transferirPara(Conta contaDestino, double valor) {
        if (valor <= 0 || saldo < valor) return false;
        this.saldo -= valor;
        contaDestino.receberTransferencia(this.numero, valor);
        extrato.append("Transferência para conta ").append(contaDestino.getNumero())
              .append(": -R$").append(String.format("%.2f", valor)).append("\n");
        return true;
    }
    
    private synchronized void receberTransferencia(int contaOrigem, double valor) {
        saldo += valor;
        extrato.append("Transferência de conta ").append(contaOrigem)
              .append(": +R$").append(String.format("%.2f", valor)).append("\n");
    }
    
    @Override
    public String toString() {
        return "Conta " + numero + " - Saldo: R$" + String.format("%.2f", saldo);
    }
}
