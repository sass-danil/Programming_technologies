package com.example.programtech.adapter;

import android.content.Context;
import android.content.Intent;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageButton;
import android.widget.TextView;
import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;
import com.example.programtech.R;
import com.example.programtech.RecipeDetailActivity;
import com.example.programtech.model.Recipe;
import java.util.List;

public class RecipeAdapter extends RecyclerView.Adapter<RecipeAdapter.RecipeViewHolder> {

    private Context context;
    private List<Recipe> recipes;

    public RecipeAdapter(Context context, List<Recipe> recipes) {
        this.context = context;
        this.recipes = recipes;
    }

    @NonNull
    @Override
    public RecipeViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        View view = LayoutInflater.from(context).inflate(R.layout.recipe_item, parent, false);
        return new RecipeViewHolder(view);
    }

    @Override
    public void onBindViewHolder(@NonNull RecipeViewHolder holder, int position) {
        Recipe recipe = recipes.get(position);
        holder.bind(recipe);
    }

    @Override
    public int getItemCount() {
        return recipes.size();
    }

    public class RecipeViewHolder extends RecyclerView.ViewHolder {

        TextView recipeName;
        TextView recipeDifficulty;
        ImageButton recipeButton;

        public RecipeViewHolder(@NonNull View itemView) {
            super(itemView);
            recipeName = itemView.findViewById(R.id.recipe_name);
            recipeDifficulty = itemView.findViewById(R.id.recipe_difficulty);
            recipeButton = itemView.findViewById(R.id.recipe_button);
        }

        public void bind(Recipe recipe) {
            recipeName.setText(recipe.getName());
            recipeDifficulty.setText(recipe.getDifficulty());
            recipeButton.setOnClickListener(v -> {
                Intent intent = new Intent(context, RecipeDetailActivity.class);
                intent.putExtra("recipe_name", recipe.getName());
                intent.putExtra("recipe_description", recipe.getDescription());
                context.startActivity(intent);
            });
        }
    }
}
