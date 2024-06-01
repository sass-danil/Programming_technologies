package com.example.programtech;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import androidx.appcompat.app.AppCompatActivity;

public class AddNoteActivity extends AppCompatActivity {

    private EditText noteTitleEditText;
    private EditText noteContentEditText;
    private int noteId = -1;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_add_note);

        noteTitleEditText = findViewById(R.id.noteTitleEditText);
        noteContentEditText = findViewById(R.id.noteContentEditText);
        Button saveNoteButton = findViewById(R.id.saveNoteButton);

        Intent intent = getIntent();
        if (intent.hasExtra(NoteDetailActivity.EXTRA_NOTE_ID)) {
            noteId = intent.getIntExtra(NoteDetailActivity.EXTRA_NOTE_ID, -1);
            noteTitleEditText.setText(intent.getStringExtra(NoteDetailActivity.EXTRA_NOTE_TITLE));
            noteContentEditText.setText(intent.getStringExtra(NoteDetailActivity.EXTRA_NOTE_CONTENT));
        }

        saveNoteButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String title = noteTitleEditText.getText().toString();
                String content = noteContentEditText.getText().toString();

                if (!title.isEmpty() && !content.isEmpty()) {
                    Intent resultIntent = new Intent();
                    resultIntent.putExtra(NoteDetailActivity.EXTRA_NOTE_ID, noteId);
                    resultIntent.putExtra(NoteDetailActivity.EXTRA_NOTE_TITLE, title);
                    resultIntent.putExtra(NoteDetailActivity.EXTRA_NOTE_CONTENT, content);
                    setResult(RESULT_OK, resultIntent);
                    finish();
                }
            }
        });
    }
}