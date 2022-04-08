package com.example.the_game_client;

import androidx.appcompat.app.AppCompatActivity;

import android.annotation.SuppressLint;
import android.content.Intent;
import android.os.Bundle;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

public class CreateGame extends AppCompatActivity {

    private EditText etPlayersCards;
    private boolean change = false;
    @SuppressLint("SetTextI18n")
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_create_game);

        etPlayersCards = findViewById(R.id.etPlayersCards);

        Button btnStrt = findViewById(R.id.btnStrt);
        btnStrt.setOnClickListener(v -> {
            if (!etPlayersCards.getText().toString().equals("")){
                new Thread(new Thread3(etPlayersCards.getText().toString())).start();
                if (!change){
                    change=true;
                    TextView tvStrt = findViewById(R.id.tvStrt);
                    tvStrt.setText("Nombre de cartes :");
                    etPlayersCards.setHint("nb_cartes");
                    btnStrt.setText("Commencer");
                    change=true;
                }
                else{
                    Intent intent = new Intent(CreateGame.this, GameRoom.class);
                    startActivity(intent);
                    finish();
                }
            }
        });

    }


    static class Thread3 implements Runnable {
        private final String message;
        Thread3(String message) {
            this.message = message;
        }
        @Override
        public void run() {
            MainActivity.output.write(message);
            MainActivity.output.flush();
        }
    }
}