public class PLAINTEXT {

    public static final int[] IP = {
            58,50,42,34,26,18,10,2,
            60,52,44,36,28,20,12,4,
            62,54,46,38,30,22,14,6,
            64,56,48,40,32,24,16,8,
            57,49,41,33,25,17,9,1,
            59,51,43,35,27,19,11,3,
            61,53,45,37,29,21,13,5,
            63,55,47,39,31,23,15,7
    };

    public static final int[] IP_INV = {
            40,8,48,16,56,24,64,32,
            39,7,47,15,55,23,63,31,
            38,6,46,14,54,22,62,30,
            37,5,45,13,53,21,61,29,
            36,4,44,12,52,20,60,28,
            35,3,43,11,51,19,59,27,
            34,2,42,10,50,18,58,26,
            33,1,41,9,49,17,57,25
    };

    private String plainText64;

    public PLAINTEXT(String plainText64) {
        this.plainText64 = plainText64;
    }

    public String Ip() {
        return permute(plainText64, IP);
    }

    public String IpInv() {
        return permute(plainText64, IP_INV);
    }

    private String permute(String input, int[] table) {
        StringBuilder result = new StringBuilder();
        for (int i : table) {
            result.append(input.charAt(i - 1));
        }
        return result.toString();
    }

    public String[] Split_Half() {
        return new String[]{
                plainText64.substring(0, 32),
                plainText64.substring(32)
        };
    }

}
