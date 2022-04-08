package com.example.the_game_client;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.TextView;

import java.io.IOException;

public class GameRoom extends AppCompatActivity {

    private TextView tvPile;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_game_room);

        tvPile = findViewById(R.id.tvPile);
        new Thread(new Thread2()).start();
    }

    class Thread2 implements Runnable {
        @Override
        public void run() {
            while (true) {
                try {
                    final String message = MainActivity.input.readLine();
                    if (message != null) {
                        runOnUiThread(() -> {
                            tvPile.setText(message);
                        });
                    }
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
    }
}