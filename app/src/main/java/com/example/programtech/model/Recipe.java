package com.example.programtech.model;

public class Recipe {
    private String name;
    private String difficulty;
    private String description; // Новое поле

    public Recipe(String name, String difficulty, String description) {
        this.name = name;
        this.difficulty = difficulty;
        this.description = description;
    }

    public String getName() {
        return name;
    }

    public String getDifficulty() {
        return difficulty;
    }

    public String getDescription() {
        return description;
    }
}
