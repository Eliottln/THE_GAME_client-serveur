package com.example.the_game_client;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.Button;
import android.widget.EditText;
import android.widget.RadioButton;
import android.widget.RadioGroup;
import android.widget.TextView;

import java.io.IOException;

public class GameRoom extends AppCompatActivity {

    private TextView tvPile, tvDeck;
    private RadioGroup radioPile;
    private RadioButton radioButton;
    private EditText card;
    private boolean isPileString = true;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_game_room);

        tvPile = findViewById(R.id.tvPile);
        tvDeck = findViewById(R.id.tvDeck);
        radioPile = findViewById(R.id.rgPile);
        card = findViewById(R.id.etCard);

        Button btnSendCard = findViewById(R.id.btnSendCard);
        btnSendCard.setOnClickListener(v -> {
            if (!card.getText().toString().equals("")) {
                int selectedId = radioPile.getCheckedRadioButtonId();
                radioButton = (RadioButton) findViewById(selectedId);
                new Thread(new Thread3(card.getText().toString(), radioButton.getContentDescription().toString())).start();
                card.setText("");
            }
        });

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
                            if (isPileString){
                                try {
                                    String pile = message.split("\t")[0] + "\n"
                                            + message.split("\t")[1] + "\n"
                                            + message.split("\t")[2] + "\n"
                                            + message.split("\t")[3];
                                    tvPile.setText(pile);
                                    isPileString = false;
                                }
                                catch(Exception e){
                                    tvDeck.setText(message);
                                }
                            }
                            else if (!isPileString){
                                tvDeck.setText(message);
                                isPileString=true;
                            }
                        });
                    }
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    static class Thread3 implements Runnable {
        private final String message, message2;
        Thread3(String message, String message2) {
            this.message = message;
            this.message2 = message2;
        }
        @Override
        public void run() {
            MainActivity.output.write("PILE");
            MainActivity.output.flush();
            MainActivity.output.write(message+'-'+message2);
            MainActivity.output.flush();
        }
    }
}