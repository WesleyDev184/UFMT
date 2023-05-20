package dao.MedicosDAO;

import java.util.List;

import entidades.Medico;

public interface MedicoInterface {
  public boolean insertDoctor(Medico medico);

  public Medico searchDoctor(String pesquisa);

  public List<Medico> listDoctor();

}