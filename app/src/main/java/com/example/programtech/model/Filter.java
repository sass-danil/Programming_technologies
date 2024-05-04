package com.example.programtech.model;

public class Filter {

    int id;
    String Title;

    public Filter(int id, String title) {
        this.id = id;
        Title = title;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getTitle() {
        return Title;
    }

    public void setTitle(String title) {
        Title = title;
    }
}
