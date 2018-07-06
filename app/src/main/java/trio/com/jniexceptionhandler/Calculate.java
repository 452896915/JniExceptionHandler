package trio.com.jniexceptionhandler;

import android.util.Log;

public class Calculate {
    static {
        System.loadLibrary("CalculateJni");
    }

    public static native int jniDivide(int input1, int input2);

    public static int callJniDivide(int input1, int input2) {
        try {
            return jniDivide(input1, input2);
        } catch (Exception e) {
            Log.e("JniExceptionHandler", e.toString());
            return -1;
        }
    }
}
