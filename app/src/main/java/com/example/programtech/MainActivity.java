package com.example.programtech;



import android.os.Bundle;

import androidx.appcompat.app.AppCompatActivity;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import com.example.programtech.adapter.FilterAdapter;
import com.example.programtech.adapter.ProductAdapter;
import com.example.programtech.model.Filter;
import com.example.programtech.model.Product;

import java.util.ArrayList;
import java.util.List;


public class MainActivity extends AppCompatActivity {

    RecyclerView filterRecycler, productRecycler;
    FilterAdapter filterAdapter;
    ProductAdapter productAdapter;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        List<Filter> filterList = new ArrayList<>();
        filterList.add(new com.example.programtech.model.Filter(1,"По Количеству"));
        filterList.add(new com.example.programtech.model.Filter(2,"По Сроку Годности"));

        setFilterRecycler(filterList);


        List<Product> productList = new ArrayList<>();
        productList.add(new com.example.programtech.model.Product(1,"milk_svgrepo_com.xml", "Молоко", "12.12.2012", "#0A887D", 4));
        productList.add(new com.example.programtech.model.Product(2,"egg", "Яйца", "01.07.1917", "#0A887D",4));

        setProductRecycler(productList);
    }

    private void setProductRecycler(List<Product> productList) {

        RecyclerView.LayoutManager layoutManager = new LinearLayoutManager(this,RecyclerView.VERTICAL,false);

        productRecycler = findViewById(R.id.Product_Recycler);
        productRecycler.setLayoutManager(layoutManager);

        productAdapter = new ProductAdapter(this, productList);
        productRecycler.setAdapter(productAdapter);

    }


    private void setFilterRecycler(List<Filter> filterList) {

        RecyclerView.LayoutManager layoutManager = new LinearLayoutManager(this,RecyclerView.HORIZONTAL,false);

        filterRecycler = findViewById(R.id.filterRecycler);
        filterRecycler.setLayoutManager(layoutManager);

        filterAdapter = new FilterAdapter(this,filterList);
        filterRecycler.setAdapter(filterAdapter);
    }

}
