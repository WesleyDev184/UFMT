package entidades;

import java.util.Date;

public abstract class Pessoa {
	private String nome;
	private String sexo;
	public static int qtdPessoa;
	private Endereco endereco;
	private String dataNascimento;

	public String getNome() {
		return nome;
	}

	public void setNome(String nome) {
		this.nome = nome;
	}

	public String getSexo() {
		return sexo;
	}

	public void setSexo(String sexo) {
		this.sexo = sexo;
	}

	public Endereco getEndereco() {
		return endereco;
	}

	public void setEndereco(Endereco endereco) {
		this.endereco = endereco;
	}

	public static int getQtdPessoa() {
		return qtdPessoa;
	}

	public static void setQtdPessoa(int qtdPessoa) {
		Pessoa.qtdPessoa = qtdPessoa;
	}

	public String getDataNascimento() {
		return dataNascimento;
	}

	public void setDataNascimento(String dataNascimento) {
		this.dataNascimento = dataNascimento;
	}
}
