import entidades.Anestesista;
import entidades.Cardiologista;
import entidades.Medico;
import entidades.Ortopedista;
import entidades.ResidenteAnestesista;

public class App {

    public static void main(String[] args) {

        Ortopedista orto = new Ortopedista();
        Anestesista anes = new Anestesista();
        Cardiologista card = new Cardiologista();

        Medico[] arrayMedicos = new Medico[] { orto, anes, card };
        for (Medico valor : arrayMedicos) {
            valor.operar();
        }

        //
        // Medico medico = orto;
        // medico.operar();
        // orto.metodoOrtopedista();
        //
        // Funcionario f = orto;
        // Pessoa p = orto;
        // Object o = orto;

        ResidenteAnestesista rAnes = new ResidenteAnestesista();
        Anestesista anes2 = new Anestesista();
        rAnes.operar();
        anes2.operar();
        // rAnes = (ResidenteAnestesista) anes2;
        // rAnes.metodoAnestesista();

    }

}