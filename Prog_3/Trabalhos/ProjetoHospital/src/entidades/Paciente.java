package entidades;

import java.util.Date;

public class Paciente extends Pessoa {
	private Date dataInternacao;

	public Date getDataInternacao() {
		return dataInternacao;
	}

	public void setDataInternacao(Date dataInternacao) {
		this.dataInternacao = dataInternacao;
	}

}
