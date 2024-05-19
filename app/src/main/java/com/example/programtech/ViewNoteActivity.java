package com.example.programtech;

import android.os.Bundle;
import android.widget.TextView;
import androidx.appcompat.app.AppCompatActivity;

public class ViewNoteActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_view_note);

        TextView noteTitleTextView = findViewById(R.id.noteTitleTextView);
        TextView noteContentTextView = findViewById(R.id.noteContentTextView);

        // Получаем данные заметки из Intent
        String title = getIntent().getStringExtra("NOTE_TITLE");
        String content = getIntent().getStringExtra("NOTE_CONTENT");

        // Устанавливаем данные в TextView
        noteTitleTextView.setText(title);
        noteContentTextView.setText(content);
    }
}
