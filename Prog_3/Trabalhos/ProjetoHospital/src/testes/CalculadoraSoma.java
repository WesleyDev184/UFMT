package testes;

import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JTextField;
import javax.swing.SwingUtilities;

public class CalculadoraSoma extends JFrame implements ActionListener {
  private JTextField textField1, textField2, textFieldResultado;
  private JButton buttonSomar;

  public CalculadoraSoma() {
    // Configurações básicas da janela
    setTitle("Calculadora de Soma");
    setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    setSize(300, 200);
    setLocationRelativeTo(null);
    setLayout(new GridLayout(4, 2));

    // Criação dos componentes da calculadora
    JLabel label1 = new JLabel("Número 1:");
    textField1 = new JTextField();
    JLabel label2 = new JLabel("Número 2:");
    textField2 = new JTextField();
    buttonSomar = new JButton("Somar");
    JLabel labelResultado = new JLabel("Resultado:");
    textFieldResultado = new JTextField();
    textFieldResultado.setEditable(false);

    // Adiciona os componentes na janela
    add(label1);
    add(textField1);
    add(label2);
    add(textField2);
    add(buttonSomar);
    add(labelResultado);
    add(textFieldResultado);

    // Adiciona o ActionListener ao botão de soma
    buttonSomar.addActionListener(this);

    // Exibe a janela
    setVisible(true);
  }

  public void actionPerformed(ActionEvent e) {
    if (e.getSource() == buttonSomar) {
      try {
        // Lê os valores digitados nos campos de texto
        int num1 = Integer.parseInt(textField1.getText());
        int num2 = Integer.parseInt(textField2.getText());

        // Realiza a soma
        int resultado = num1 + num2;

        // Exibe o resultado no campo de texto correspondente
        textFieldResultado.setText(Integer.toString(resultado));
      } catch (NumberFormatException ex) {
        // Exceção lançada se um número inválido for inserido
        JOptionPane.showMessageDialog(this, "Digite números válidos!",
            "Erro", JOptionPane.ERROR_MESSAGE);
      }
    }
  }

  public static void main(String[] args) {
    SwingUtilities.invokeLater(() -> new CalculadoraSoma());
  }
}
