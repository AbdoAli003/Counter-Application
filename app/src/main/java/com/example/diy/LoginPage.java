package com.example.diy;

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.EditText;
import android.widget.Toast;

import androidx.activity.EdgeToEdge;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.graphics.Insets;
import androidx.core.view.ViewCompat;
import androidx.core.view.WindowInsetsCompat;

public class LoginPage extends AppCompatActivity {
    private EditText Username;
    private EditText Password;
    public native boolean loginToServer(String username, String password);
    static
    {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        EdgeToEdge.enable(this);
        setContentView(R.layout.activity_login_page);
        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.main), (v, insets) -> {
            Insets systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars());
            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom);
            Username = findViewById(R.id.usr);
            Password = findViewById(R.id.pas);
            return insets;
        });
    }
    public void login(View v)
    {
        String username = Username.getText().toString();
        String password = Password.getText().toString();
        boolean success = loginToServer(username,password);
        Log.d("LoginPage", "Attempting to log in with Username: " + username + " and Password: " + password);
        if (success)
        {
            Intent i = new Intent(this,MainActivity.class);
            startActivity(i);
        }
        else
        {
            Toast.makeText(this, "Login failed. Please try again.", Toast.LENGTH_SHORT).show();
        }

    }


}