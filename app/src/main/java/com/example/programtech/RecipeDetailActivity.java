package com.example.programtech;

import android.annotation.SuppressLint;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import com.example.programtech.adapter.RecipeAdapter;
import com.example.programtech.model.Recipe;

import java.util.ArrayList;
import java.util.List;

public class RecipeDetailActivity extends AppCompatActivity {

    RecyclerView recipeRecycler;
    RecipeAdapter recipeAdapter;

    @SuppressLint("MissingInflatedId")
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_recipe);

        // Prepare recipe data
        List<Recipe> recipeList = new ArrayList<>();
        recipeList.add(new Recipe("Омлет", "Легко", getString(R.string.recipe_omelet)));
        recipeList.add(new Recipe("Салат", "Средне", getString(R.string.recipe_salad)));
        recipeList.add(new Recipe("Стейк", "Сложно", getString(R.string.recipe_steak)));

        // Setup RecyclerView for recipes
        recipeRecycler = findViewById(R.id.recipeRecycler);
        recipeRecycler.setLayoutManager(new LinearLayoutManager(this));
        recipeAdapter = new RecipeAdapter(this, recipeList);
        recipeRecycler.setAdapter(recipeAdapter);
    }
}
