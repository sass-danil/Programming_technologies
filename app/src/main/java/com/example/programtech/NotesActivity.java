package com.example.programtech;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import com.example.programtech.adapter.NoteAdapter;
import com.example.programtech.model.Note;

import java.util.ArrayList;
import java.util.List;

public class NotesActivity extends AppCompatActivity {

    private static final int ADD_NOTE_REQUEST = 1;

    RecyclerView notesRecycler;
    NoteAdapter notesAdapter;
    List<Note> noteList;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_note);

        // Initialize TextViews
        TextView recipesTextView = findViewById(R.id.Products);
        TextView notesTextView = findViewById(R.id.Recipes);

        // Set click listeners for navigation
        recipesTextView.setOnClickListener(v -> {
            Intent intent = new Intent(NotesActivity.this, MainActivity.class);
            startActivity(intent);
        });

        notesTextView.setOnClickListener(v -> {
            Intent intent = new Intent(NotesActivity.this, RecipeActivity.class);
            startActivity(intent);
        });


        noteList = new ArrayList<>();
        noteList.add(new Note("Заметка 1", "Содержание заметки 1"));
        noteList.add(new Note("Заметка 2", "Содержание заметки 2"));
        noteList.add(new Note("Заметка 3", "Содержание заметки 3"));

        notesRecycler = findViewById(R.id.notesRecycler);
        notesRecycler.setLayoutManager(new LinearLayoutManager(this));
        notesAdapter = new NoteAdapter(this, noteList);
        notesRecycler.setAdapter(notesAdapter);

        Button addNoteButton = findViewById(R.id.addNoteButton);
        addNoteButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(NotesActivity.this, AddNoteActivity.class);
                startActivityForResult(intent, ADD_NOTE_REQUEST);
            }
        });
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, @Nullable Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        if (requestCode == ADD_NOTE_REQUEST && resultCode == RESULT_OK) {
            if (data != null) {
                String title = data.getStringExtra("NOTE_TITLE");
                String content = data.getStringExtra("NOTE_CONTENT");
                noteList.add(new Note(title, content));
                notesAdapter.notifyDataSetChanged();
            }
        }
    }
}
