package com.example.programtech;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;

import androidx.appcompat.app.AppCompatActivity;

public class NoteDetailActivity extends AppCompatActivity {

    public static final String EXTRA_NOTE_TITLE = "EXTRA_NOTE_TITLE";
    public static final String EXTRA_NOTE_CONTENT = "EXTRA_NOTE_CONTENT";
    public static final String EXTRA_NOTE_POSITION = "EXTRA_NOTE_POSITION";

    private EditText noteTitleEditText;
    private EditText noteContentEditText;
    private Button saveButton;
    private Button deleteButton;

    private int notePosition;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_note_detail);

        noteTitleEditText = findViewById(R.id.noteTitleEditText);
        noteContentEditText = findViewById(R.id.noteContentEditText);
        saveButton = findViewById(R.id.saveButton);
        deleteButton = findViewById(R.id.deleteButton);

        Intent intent = getIntent();
        if (intent != null && intent.hasExtra(EXTRA_NOTE_TITLE) && intent.hasExtra(EXTRA_NOTE_CONTENT) && intent.hasExtra(EXTRA_NOTE_POSITION)) {
            String title = intent.getStringExtra(EXTRA_NOTE_TITLE);
            String content = intent.getStringExtra(EXTRA_NOTE_CONTENT);
            notePosition = intent.getIntExtra(EXTRA_NOTE_POSITION, -1);

            noteTitleEditText.setText(title);
            noteContentEditText.setText(content);
        }

        saveButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent resultIntent = new Intent();
                resultIntent.putExtra(EXTRA_NOTE_TITLE, noteTitleEditText.getText().toString());
                resultIntent.putExtra(EXTRA_NOTE_CONTENT, noteContentEditText.getText().toString());
                resultIntent.putExtra(EXTRA_NOTE_POSITION, notePosition);
                setResult(RESULT_OK, resultIntent);
                finish();
            }
        });

        deleteButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent resultIntent = new Intent();
                resultIntent.putExtra(EXTRA_NOTE_POSITION, notePosition);
                setResult(RESULT_FIRST_USER, resultIntent);
                finish();
            }
        });
    }
}
