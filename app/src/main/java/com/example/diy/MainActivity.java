package com.example.diy;

import android.os.Bundle;
import android.view.View;
import android.widget.TextView;

import androidx.activity.EdgeToEdge;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.graphics.Insets;
import androidx.core.view.ViewCompat;
import androidx.core.view.WindowInsetsCompat;

public class MainActivity extends AppCompatActivity {

    private TextView t;
    private static int cnt = 0;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        EdgeToEdge.enable(this);
        setContentView(R.layout.activity_main);
        t = findViewById(R.id.txt);
        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.main), (v, insets) -> {
            Insets systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars());
            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom);
            return insets;
        });
        setTitle("Counter");
    }
    public void updateText()
    {
        if (t!=null)
            t.setText(String.valueOf(cnt));
    }
    public void increment(View v)
    {
        cnt++;
        updateText();
    }
    public void decrement(View v)
    {
        if (cnt > 0) cnt--;
        updateText();
    }
    public void Reset(View v)
    {
        cnt = 0;
        updateText();
    }

}