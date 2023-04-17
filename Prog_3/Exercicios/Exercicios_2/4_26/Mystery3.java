// o codigo abaixo imprime o seguinte:

// >>>>>>>>>>
// <<<<<<<<<<
// >>>>>>>>>>
// <<<<<<<<<<
// >>>>>>>>>>
// <<<<<<<<<<
// >>>>>>>>>>
// <<<<<<<<<<
// >>>>>>>>>>
// <<<<<<<<<<


public class Mystery3 {
    public static void main(String[] args) {
        int row = 10;
        int column = 1;
        while (row >= 1) {
            while (column <= 10) {
                System.out.print(row % 2 == 1 ? "<" : ">");
                ++column;
            }
            --row;
            System.out.println();
            column = 1;
        }
    }
}