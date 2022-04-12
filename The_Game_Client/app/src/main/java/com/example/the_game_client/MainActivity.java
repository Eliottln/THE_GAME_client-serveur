package com.example.the_game_client;

import android.annotation.SuppressLint;
import android.content.Intent;
import android.os.Bundle;
import androidx.appcompat.app.AppCompatActivity;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;

@SuppressLint("SetTextI18n")
public class MainActivity extends AppCompatActivity {
    private Thread Thread1 = null;
    private EditText etIP, etPort;
    private TextView tvMessages;
    private Button btnStart, btnJoin;
    private String SERVER_IP;
    private int SERVER_PORT;
    public static PrintWriter output;
    public static BufferedReader input;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        etIP = findViewById(R.id.etIP);
        etPort = findViewById(R.id.etPort);
        tvMessages = findViewById(R.id.tvMessages);
        btnStart = findViewById(R.id.btnStart);
        btnJoin = findViewById(R.id.btnJoin);

        btnStart.setOnClickListener(v -> {
            new Thread(new Thread3("MAKE")).start();
            Intent intent = new Intent(MainActivity.this,CreateGame.class);
            startActivity(intent);
            finish();
        });

        btnJoin.setOnClickListener(v -> {
            new Thread(new Thread3("JOIN")).start();
            Intent intent = new Intent(MainActivity.this,GameRoom.class);
            startActivity(intent);
            finish();
        });

        Button btnConnect = findViewById(R.id.btnConnect);
        btnConnect.setOnClickListener(v -> {
            tvMessages.setText("");
            SERVER_IP = etIP.getText().toString().trim();
            SERVER_PORT = Integer.parseInt(etPort.getText().toString().trim());
            Thread1 = new Thread(new Thread1());
            Thread1.start();
        });

    }

    class Thread1 implements Runnable {
        @Override
        public void run() {
            Socket socket;
            try {
                socket = new Socket(SERVER_IP, SERVER_PORT);
                output = new PrintWriter(socket.getOutputStream());
                input = new BufferedReader(new InputStreamReader(socket.getInputStream()));
                runOnUiThread(() -> {
                    Button btnConnect = findViewById(R.id.btnConnect);
                    btnConnect.setVisibility(View.GONE);
                    btnStart.setVisibility(View.VISIBLE);
                    btnJoin.setVisibility(View.VISIBLE);
                    tvMessages.setText("Connected\n");
                });
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }

    static class Thread3 implements Runnable {
        private final String message;
        Thread3(String message) {
            this.message = message;
        }
        @Override
        public void run() {
            output.write(message);
            output.flush();
        }
    }
}