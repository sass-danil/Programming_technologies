package com.example.programtech;

import android.os.Bundle;
import android.widget.TextView;
import androidx.appcompat.app.AppCompatActivity;

public class RecipeDetailActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_recipe_detail);

        TextView recipeNameTextView = findViewById(R.id.recipe_detail_name);
        TextView recipeDescriptionTextView = findViewById(R.id.recipe_detail_description);

        // Get the recipe details from the intent
        String recipeName = getIntent().getStringExtra("recipe_name");
        String recipeDescription = getIntent().getStringExtra("recipe_description");

        // Set the recipe details to the TextViews
        recipeNameTextView.setText(recipeName);
        recipeDescriptionTextView.setText(recipeDescription);
    }
}
