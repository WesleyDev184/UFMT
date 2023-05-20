package entidades;

public class Parto extends Procedimento {
	private Medico[] medicos = new Medico[] { new Anestesista(null, 0, 0), new Obstetra(null, 0, 0),
			new Pediatra(null, 0, 0) };

}
