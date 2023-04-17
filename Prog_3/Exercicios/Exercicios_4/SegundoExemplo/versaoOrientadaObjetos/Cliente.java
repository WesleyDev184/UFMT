public class Cliente extends Pessoa {

	private String endereco;

	public Cliente(int codigo, String nome, String endereco) {
		super(codigo, nome);
		this.endereco = endereco;
	}

	public String getEndereco() {
		return endereco;
	}

	public void setEndereco(String endereco) {
		this.endereco = endereco;
	}
}