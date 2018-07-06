package trio.com.jniexceptionhandler;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {
    private EditText ed1;
    private EditText ed2;
    private TextView output;
    private TextView tv;
    private TextView tv2;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        ed1 = findViewById(R.id.first_ed);
        ed2 = findViewById(R.id.second_ed);
        output = findViewById(R.id.output);
        tv = findViewById(R.id.btn);
        tv2 = findViewById(R.id.btn2);

        tv.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                int a = Integer.parseInt(ed1.getText().toString());
                int b = Integer.parseInt(ed2.getText().toString());
                int val = Calculate.callJniDivide(a, b);
                output.setText(String.valueOf(val));
            }
        });

        tv2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                int a = Integer.parseInt(ed1.getText().toString());
                int b = Integer.parseInt(ed2.getText().toString());
                int val = Calculate2.callJniDivide2(a, b);
                output.setText(String.valueOf(val));
            }
        });
    }
}
