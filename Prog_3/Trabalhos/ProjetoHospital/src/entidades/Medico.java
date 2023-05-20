package entidades;

public abstract class Medico extends Funcionario {
	private int CRM;
	private double valorHora;
	private String especialidade;

	public String getEspecialidade() {
		return especialidade;
	}

	public void setEspecialidade(String especialidade) {
		this.especialidade = especialidade;
	}

	public int getCRM() {
		return CRM;
	}

	public void setCRM(int cRM) {
		CRM = cRM;
	}

	public double getValorHora() {
		return valorHora;
	}

	public void setValorHora(double valorHora) {
		if (valorHora > 0) {
			this.valorHora = valorHora;
		}
	}

	public abstract void operar();
}