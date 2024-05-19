package com.example.programtech;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import androidx.appcompat.app.AppCompatActivity;

public class AddNoteActivity extends AppCompatActivity {

    private int notePosition = -1;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_add_note);

        EditText noteTitleEditText = findViewById(R.id.noteTitleEditText);
        EditText noteContentEditText = findViewById(R.id.noteContentEditText);
        Button saveNoteButton = findViewById(R.id.saveNoteButton);

        Intent intent = getIntent();
        if (intent != null && intent.hasExtra("NOTE_TITLE") && intent.hasExtra("NOTE_CONTENT")) {
            String title = intent.getStringExtra("NOTE_TITLE");
            String content = intent.getStringExtra("NOTE_CONTENT");
            noteTitleEditText.setText(title);
            noteContentEditText.setText(content);
            notePosition = intent.getIntExtra("NOTE_POSITION", -1);
        }

        saveNoteButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String title = noteTitleEditText.getText().toString();
                String content = noteContentEditText.getText().toString();

                if (!title.isEmpty() && !content.isEmpty()) {
                    Intent resultIntent = new Intent();
                    resultIntent.putExtra("NOTE_TITLE", title);
                    resultIntent.putExtra("NOTE_CONTENT", content);
                    if (notePosition != -1) {
                        resultIntent.putExtra("NOTE_POSITION", notePosition);
                    }
                    setResult(RESULT_OK, resultIntent);
                    finish();
                }
            }
        });
    }
}
