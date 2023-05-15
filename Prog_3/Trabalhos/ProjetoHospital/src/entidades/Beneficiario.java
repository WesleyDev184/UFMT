package entidades;

import java.util.Date;
import java.util.Iterator;
import java.util.LinkedList;

public class Beneficiario {
	private String nome;
	private Date dataNascimento;
	private String tipoBeneficiario;
	public LinkedList<Beneficiario> dependentes = new LinkedList<Beneficiario>();

	public Beneficiario(String nome, Date data, String tipo) {
		this.nome = nome;
		this.dataNascimento = data;
		this.tipoBeneficiario = tipo;
	}

	public void listarDependentes() {
		Iterator<Beneficiario> i = this.dependentes.iterator();
		while (i.hasNext()) {
			System.out.println(i.next().nome);
		}
	}

	public void adicionaDependente(Beneficiario dependente) {
		this.dependentes.add(dependente);
	}

	public String getTipoBeneficiario() {
		return tipoBeneficiario;
	}

	public void setTipoBeneficiario(String tipoBeneficiario) {
		this.tipoBeneficiario = tipoBeneficiario;
	}

	public Date getDataNascimento() {
		return dataNascimento;
	}

	public void setDataNascimento(Date dataNascimento) {
		this.dataNascimento = dataNascimento;
	}

	public String getNome() {
		return nome;
	}

	public void setNome(String nome) {
		this.nome = nome;
	}

	public static void main(String[] args) {
		Beneficiario b1 = new Beneficiario("Saymon", new Date(), "titular");
		Beneficiario filho1 = new Beneficiario("Willian", new Date(), "dependente");
		Beneficiario filho2 = new Beneficiario("Paulinho", new Date(), "dependente");
		filho1.listarDependentes();

		b1.adicionaDependente(filho1);
		b1.adicionaDependente(filho2);
		b1.listarDependentes();
	}
}
