package com.example.programtech.model;

public class Recipe {
    private String name;
    private String difficulty;

    public Recipe(String name, String difficulty) {
        this.name = name;
        this.difficulty = difficulty;
    }

    public String getName() {
        return name;
    }

    public String getDifficulty() {
        return difficulty;
    }
}
