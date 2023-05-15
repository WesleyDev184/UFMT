package entidades;

public class Endereco {
	private String logradouro;
	private int numero;
	private String bairro;

	public Endereco(String logradouro, int numero, String bairro) {
		this.setLogradouro(logradouro);
		this.setNumero(numero);
		this.setBairro(bairro);
	}

	public String getLogradouro() {
		return logradouro;
	}

	public void setLogradouro(String logradouro) {
		this.logradouro = logradouro;
	}

	public int getNumero() {
		return numero;
	}

	public void setNumero(int numero) {
		this.numero = numero;
	}

	public String getBairro() {
		return bairro;
	}

	public void setBairro(String bairro) {
		this.bairro = bairro;
	}

}
