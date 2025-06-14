import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter the initial seed: ");
        String initialSeed = scanner.nextLine();

        System.out.print("Enter the number of tap positions: ");
        int numTaps = scanner.nextInt();
        int[] tapPositions = new int[numTaps];

        for (int i = 0; i < numTaps; i++) {
            System.out.print("Enter tap position " + (i + 1) + ": ");
            tapPositions[i] = scanner.nextInt();
        }

        scanner.nextLine(); // Consume newline

        System.out.print("Enter plain text to encrypt: ");
        String plainText = scanner.nextLine();

        LFSR lfsr = new LFSR(initialSeed, tapPositions);

        String keyStream = lfsr.sequenceGeneration(100);
        System.out.println("Generated sequence: " + keyStream);

        String cipherText = lfsr.encryptDecrypt(plainText, keyStream);
        System.out.println("Encrypted: " + cipherText);

        String decrypted = lfsr.encryptDecrypt(cipherText, keyStream);
        System.out.println("Decrypted: " + decrypted);

        scanner.close();
    }
}