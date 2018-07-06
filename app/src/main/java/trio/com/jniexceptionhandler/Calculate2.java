package trio.com.jniexceptionhandler;

import android.util.Log;

public class Calculate2 {
    static {
        System.loadLibrary("CalculateJni2");
    }

    public static native int jniDivide(int input1, int input2);

    public static int callJniDivide2(int input1, int input2) {
        return jniDivide(input1, input2);
    }
}
