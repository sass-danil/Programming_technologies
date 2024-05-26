package com.example.programtech;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import androidx.appcompat.app.AppCompatActivity;

public class NoteDetailActivity extends AppCompatActivity {

    public static final String EXTRA_NOTE_ID = "com.example.programtech.EXTRA_NOTE_ID";
    public static final String EXTRA_NOTE_TITLE = "com.example.programtech.EXTRA_NOTE_TITLE";
    public static final String EXTRA_NOTE_CONTENT = "com.example.programtech.EXTRA_NOTE_CONTENT";
    public static final String EXTRA_NOTE_POSITION = "com.example.programtech.EXTRA_NOTE_POSITION";

    private EditText noteTitleEditText;
    private EditText noteContentEditText;
    private Button saveButton;
    private Button deleteButton;
    private long noteId;
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
        noteId = intent.getLongExtra(EXTRA_NOTE_ID, -1);
        String noteTitle = intent.getStringExtra(EXTRA_NOTE_TITLE);
        String noteContent = intent.getStringExtra(EXTRA_NOTE_CONTENT);
        notePosition = intent.getIntExtra(EXTRA_NOTE_POSITION, -1);

        noteTitleEditText.setText(noteTitle);
        noteContentEditText.setText(noteContent);

        saveButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String title = noteTitleEditText.getText().toString();
                String content = noteContentEditText.getText().toString();

                Intent resultIntent = new Intent();
                resultIntent.putExtra(EXTRA_NOTE_ID, noteId);
                resultIntent.putExtra(EXTRA_NOTE_TITLE, title);
                resultIntent.putExtra(EXTRA_NOTE_CONTENT, content);
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
