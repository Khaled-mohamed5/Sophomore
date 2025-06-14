public class LFSR {
    private String seed;
    private int[] tapPositions;

    public LFSR(String seed, int[] tapPositions) {
        this.seed = seed;
        this.tapPositions = tapPositions;
    }

    private char xor(char a, char b) {
        return (a == b) ? '0' : '1';
    }

    public String sequenceGeneration(int length) {
        StringBuilder generatedSequence = new StringBuilder(seed);
        for (int i = 0; i < length - seed.length(); i++) {
            char feedbackBit = generatedSequence.charAt(generatedSequence.length() - tapPositions[0]);
            for (int j = 1; j < tapPositions.length; j++) {
                feedbackBit = xor(
                        feedbackBit,
                        generatedSequence.charAt(generatedSequence.length() - tapPositions[j])
                );
            }
            generatedSequence.append(feedbackBit);
        }
        return generatedSequence.toString();
    }

    public String encryptDecrypt(String message, String keystream) {
        StringBuilder result = new StringBuilder();
        for (int i = 0; i < message.length(); i++) {
            char mess = message.charAt(i);
            char key = keystream.charAt(i % keystream.length());
            result.append(xor(mess, key));
        }
        return result.toString();
    }
}