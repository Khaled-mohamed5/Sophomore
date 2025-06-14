import java.util.Scanner;

public class RSA {
    private long p;
    private long q;
    private long n;
    private long phi;
    private long e;
    private long d;

    public RSA(long p, long q) {
        this.p = p;
        this.q = q;
        generateKeys();
    }

    public void generateKeys() {
        n = p * q;
        phi = (p - 1) * (q - 1);
        e = findCoprime(phi);
        d = calculateModularInverse(e, phi);

        System.out.println("Key generation complete!");
        System.out.println("Public Key (n, e): (" + n + ", " + e + ")");
        System.out.println("Private Key (n, d): (" + n + ", " + d + ")");
    }

    private long findCoprime(long phi) {
        long candidate = 3;
        while (candidate < phi) {
            if (gcd(candidate, phi) == 1) {
                return candidate;
            }
            candidate += 2;
        }
        throw new RuntimeException("No coprime found.");
    }

    private long gcd(long a, long b) {
        return b == 0 ? a : gcd(b, a % b);
    }

    private long calculateModularInverse(long a, long m) {
        long m0 = m, x = 1, y = 0;

        while (a > 1) {
            long q = a / m;
            long t = m;
            m = a % m;
            a = t;

            t = y;
            y = x - q * y;
            x = t;
        }

        return x < 0 ? x + m0 : x;
    }

    public long encrypt(long message) {
        if (message >= n) {
            throw new IllegalArgumentException("Message must be less than n.");
        }
        return modularExponentiation(message, e, n);
    }

    public long decrypt(long ciphertext) {
        return modularExponentiation(ciphertext, d, n);
    }

    private long modularExponentiation(long base, long exp, long mod) {
        long result = 1;
        base = base % mod;

        while (exp > 0) {
            if ((exp & 1) == 1) result = (result * base) % mod;
            exp = exp >> 1;
            base = (base * base) % mod;
        }
        return result;
    }

    public long[] encryptMessage(String message) {
        char[] chars = message.toCharArray();
        long[] encrypted = new long[chars.length];
        for (int i = 0; i < chars.length; i++) {
            encrypted[i] = encrypt((long) chars[i]);
        }
        return encrypted;
    }

    public String decryptMessage(long[] encrypted) {
        StringBuilder sb = new StringBuilder();
        for (long val : encrypted) {
            sb.append((char) decrypt(val));
        }
        return sb.toString();
    }

    public static boolean isPrime(long num) {
        if (num < 2) return false;
        if (num == 2 || num == 3) return true;
        if (num % 2 == 0 || num % 3 == 0) return false;
        for (long i = 5; i * i <= num; i += 6) {
            if (num % i == 0 || num % (i + 2) == 0) return false;
        }
        return true;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        long p = 0, q = 0;
        while (true) {
            try {
                System.out.print("Enter prime number p: ");
                p = Long.parseLong(scanner.nextLine());
                if (!isPrime(p)) throw new IllegalArgumentException("Not a prime.");
                break;
            } catch (Exception e) {
                System.out.println("Invalid input. Please enter a valid prime number.");
            }
        }

        while (true) {
            try {
                System.out.print("Enter prime number q (not equal to p): ");
                q = Long.parseLong(scanner.nextLine());
                if (!isPrime(q) || q == p) throw new IllegalArgumentException("Invalid q.");
                break;
            } catch (Exception e) {
                System.out.println("Invalid input. Please enter a valid prime number different from p.");
            }
        }

        RSA rsa = new RSA(p, q);

        System.out.println("\nChoose message type:");
        System.out.println("1. Numeric");
        System.out.println("2. Text");
        System.out.print("Enter choice (1 or 2): ");
        int choice;
        try {
            choice = Integer.parseInt(scanner.nextLine());
        } catch (Exception e) {
            System.out.println("Invalid choice.");
            scanner.close();
            return;
        }

        if (choice == 1) {
            System.out.print("Enter number to encrypt: ");
            try {
                long num = Long.parseLong(scanner.nextLine());
                long encrypted = rsa.encrypt(num);
                long decrypted = rsa.decrypt(encrypted);
                System.out.println("Encrypted: " + encrypted);
                System.out.println("Decrypted: " + decrypted);
            } catch (Exception e) {
                System.out.println("Invalid number.");
            }
        } else if (choice == 2) {
            System.out.print("Enter text to encrypt: ");
            String text = scanner.nextLine();
            long[] encryptedText = rsa.encryptMessage(text);
            System.out.print("Encrypted values: ");
            for (long val : encryptedText) System.out.print(val + " ");
            System.out.println();
            String decrypted = rsa.decryptMessage(encryptedText);
            System.out.println("Decrypted text: " + decrypted);
        } else {
            System.out.println("Invalid choice.");
        }

        scanner.close();
    }
}
