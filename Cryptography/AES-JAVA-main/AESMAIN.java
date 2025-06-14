import java.util.Scanner;

public class AESMAIN { public static void main(String[] args) {
    Scanner scanner = new Scanner(System.in);

    // Step 1: Get 16-character key
    System.out.print("Enter a 16-character key: ");
    String keyStr = scanner.nextLine();
    while (keyStr.length() != 16) {
        System.out.print("Key must be exactly 16 characters. Try again: ");
        keyStr = scanner.nextLine();
    }

    // Step 2: Get 16-character plaintext
    System.out.print("Enter a 16-character plaintext: ");
    String plainStr = scanner.nextLine();
    while (plainStr.length() != 16) {
        System.out.print("Plaintext must be exactly 16 characters. Try again: ");
        plainStr = scanner.nextLine();
    }

    // Step 3: Convert input to byte arrays
    byte[] key = keyStr.getBytes();
    byte[] plaintext = plainStr.getBytes();

    // Step 4: Create AES instance
    AES128 aes = new AES128(key);

    // Step 5: Encrypt
    byte[] encrypted = aes.encryptBlock(plaintext);
    System.out.print("Encrypted (hex): ");
    for (byte b : encrypted) {
        System.out.printf("%02X ", b);
    }
    System.out.println();

    // Step 6: Decrypt
    byte[] decrypted = aes.decryptBlock(encrypted);
    System.out.println("Decrypted: " + new String(decrypted));

    scanner.close();
}
}
