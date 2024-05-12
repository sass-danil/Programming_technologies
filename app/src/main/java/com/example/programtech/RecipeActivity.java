package com.example.programtech;

import android.annotation.SuppressLint;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import com.example.programtech.MainActivity;
import com.example.programtech.NoteActivity;
import com.example.programtech.R;
import com.example.programtech.adapter.RecipeAdapter;
import com.example.programtech.model.Recipe;
import java.util.ArrayList;
import java.util.List;

public class RecipeActivity extends AppCompatActivity {

    RecyclerView recipeRecycler;
    RecipeAdapter recipeAdapter;

    @SuppressLint("MissingInflatedId")
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_recipe);

        // Prepare recipe data
        List<Recipe> recipeList = new ArrayList<>();
        recipeList.add(new Recipe("Омлет", "Легко"));
        recipeList.add(new Recipe("Салат", "Средне"));
        recipeList.add(new Recipe("Стейк", "Сложно"));

        // Setup RecyclerView for recipes
        recipeRecycler = findViewById(R.id.recipeRecycler);
        recipeRecycler.setLayoutManager(new LinearLayoutManager(this));
        recipeAdapter = new RecipeAdapter(this, recipeList);
        recipeRecycler.setAdapter(recipeAdapter);

        // Находим TextView для "Продуктов" и устанавливаем обработчик нажатия
        TextView recipesTextView = findViewById(R.id.Products);
        recipesTextView.setOnClickListener(v -> {
            // Переходим на страницу с рецептами
            Intent intent = new Intent(RecipeActivity.this, MainActivity.class);
            startActivity(intent);
        });

        // Находим TextView для "Заметок" и устанавливаем обработчик нажатия
        TextView productsTextView = findViewById(R.id.Notes);
        productsTextView.setOnClickListener(v -> {
            // Переходим на страницу с заметками
            Intent intent = new Intent(RecipeActivity.this, NoteActivity.class);
            startActivity(intent);
        });

    }
}
