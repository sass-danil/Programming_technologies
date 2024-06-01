package com.example.programtech;

import android.os.Bundle;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

public class RecipeDetailActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_recipe_detail);

        TextView recipeTitle = findViewById(R.id.recipeTitle);
        TextView recipeDifficulty = findViewById(R.id.recipeDifficulty);
        TextView recipeContent = findViewById(R.id.recipeContent);

        // Get data from intent
        String title = getIntent().getStringExtra("RECIPE_TITLE");
        String difficulty = getIntent().getStringExtra("RECIPE_DIFFICULTY");
        String content = getIntent().getStringExtra("RECIPE_CONTENT");

        // Set data to views
        recipeTitle.setText(title);
        recipeDifficulty.setText(difficulty);
        recipeContent.setText(content);
    }
}
