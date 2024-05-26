package com.example.programtech;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

import androidx.appcompat.app.AppCompatActivity;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import com.example.programtech.adapter.FilterAdapter;
import com.example.programtech.adapter.ProductAdapter;
import com.example.programtech.model.Filter;
import com.example.programtech.model.Product;

import java.util.ArrayList;
import java.util.Calendar;
import java.util.Collections;
import java.util.List;
import java.util.Locale;

import android.app.DatePickerDialog;
import androidx.appcompat.app.AlertDialog;
import android.view.LayoutInflater;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.TextView;

import java.text.ParseException;
import java.text.SimpleDateFormat;

public class MainActivity extends AppCompatActivity implements FilterAdapter.FilterClickListener {

    RecyclerView filterRecycler, productRecycler;
    FilterAdapter filterAdapter;
    ProductAdapter productAdapter;
    List<Product> productList;
    private boolean sortByQuantityAsc = true;
    private boolean sortByDateAsc = true;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        setupFilterRecycler();
        setupProductRecycler();

        Button addProductButton = findViewById(R.id.addProductButton);
        addProductButton.setOnClickListener(v -> showAddProductDialog());

        // Initialize TextViews
        TextView recipesTextView = findViewById(R.id.Recipes);
        TextView notesTextView = findViewById(R.id.Notes);

        // Set click listeners for navigation
        recipesTextView.setOnClickListener(v -> {
            Intent intent = new Intent(MainActivity.this, RecipeActivity.class);
            startActivity(intent);
        });

        notesTextView.setOnClickListener(v -> {
            Intent intent = new Intent(MainActivity.this, NotesActivity.class);
            startActivity(intent);
        });

        ImageView accountImageView = findViewById(R.id.imageView);
        accountImageView.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(MainActivity.this, LoginActivity.class);
                startActivity(intent);
            }
        });
    }

    private void setupFilterRecycler() {
        List<Filter> filterList = new ArrayList<>();
        filterList.add(new Filter(1, "По Количеству"));
        filterList.add(new Filter(2, "По Сроку Годности"));
        filterRecycler = findViewById(R.id.filterRecycler);
        filterRecycler.setLayoutManager(new LinearLayoutManager(this, RecyclerView.HORIZONTAL, false));
        filterAdapter = new FilterAdapter(this, filterList, this);
        filterRecycler.setAdapter(filterAdapter);
    }

    private void setupProductRecycler() {
        productList = new ArrayList<>();
        productList.add(new Product(1, "milk", "Молоко", "12/12/2022", "#FFFFFF", 4));
        productList.add(new Product(2, "egg", "Яйца", "01/01/2023", "#FFFFFF", 12));
        productList.add(new Product(3, "dead_fish", "Рыба", "13/05/2024", "#FFFFFF", 1));
        productList.add(new Product(4, "butter", "Масло", "19/02/2023", "#FFFFFF", 3));
        productList.add(new Product(5, "bread", "Хлеб", "18/10/2024", "#FFFFFF", 10));
        productRecycler = findViewById(R.id.Product_Recycler);
        productRecycler.setLayoutManager(new LinearLayoutManager(this, RecyclerView.VERTICAL, false));
        productAdapter = new ProductAdapter(this, productList);
        productRecycler.setAdapter(productAdapter);
    }

    @Override
    public void onFilterClicked(Filter filter) {
        if ("По Количеству".equals(filter.getTitle())) {
            sortByQuantity();
        } else if ("По Сроку Годности".equals(filter.getTitle())) {
            sortByDate();
        }
    }

    private void sortByQuantity() {
        Collections.sort(productList, (p1, p2) -> sortByQuantityAsc ? Integer.compare(p1.getCount(), p2.getCount()) : Integer.compare(p2.getCount(), p1.getCount()));
        productAdapter.notifyDataSetChanged();
        sortByQuantityAsc = !sortByQuantityAsc;
    }

    private void sortByDate() {
        SimpleDateFormat format = new SimpleDateFormat("dd/MM/yyyy", Locale.getDefault());
        Collections.sort(productList, (p1, p2) -> {
            try {
                return sortByDateAsc ? format.parse(p1.getDate()).compareTo(format.parse(p2.getDate())) : format.parse(p2.getDate()).compareTo(format.parse(p1.getDate()));
            } catch (ParseException e) {
                e.printStackTrace();
                return 0;
            }
        });
        productAdapter.notifyDataSetChanged();
        sortByDateAsc = !sortByDateAsc;
    }

    private void showAddProductDialog() {
        LayoutInflater inflater = LayoutInflater.from(this);
        View view = inflater.inflate(R.layout.add_product_dialog, null);
        EditText productNameInput = view.findViewById(R.id.productNameInput);
        EditText productDateInput = view.findViewById(R.id.productDateInput);
        EditText productCountInput = view.findViewById(R.id.productCountInput);
        EditText productIconInput = view.findViewById(R.id.productIconInput);

        productDateInput.setOnClickListener(v -> {
            Calendar cal = Calendar.getInstance();
            int year = cal.get(Calendar.YEAR);
            int month = cal.get(Calendar.MONTH);
            int day = cal.get(Calendar.DAY_OF_MONTH);

            DatePickerDialog datePickerDialog = new DatePickerDialog(this, (view12, year12, monthOfYear, dayOfMonth) -> {
                productDateInput.setText(String.format(Locale.US, "%02d/%02d/%04d", dayOfMonth, monthOfYear + 1, year12));
            }, year, month, day);

            datePickerDialog.show();
        });

        AlertDialog dialog = new AlertDialog.Builder(this)
                .setTitle("Добавить новый продукт")
                .setView(view)
                .setPositiveButton("Добавить", (dialog1, which) -> {
                    String name = productNameInput.getText().toString();
                    String date = productDateInput.getText().toString();
                    int count = Integer.parseInt(productCountInput.getText().toString());
                    String icon = productIconInput.getText().toString();
                    addProduct(name, date, count, icon);
                })
                .setNegativeButton("Отмена", null)
                .create();
        dialog.show();
    }

    private void addProduct(String name, String date, int count, String icon) {
        Product newProduct = new Product(productList.size() + 1, icon, name, date, "#FFFFFF", count);
        productList.add(newProduct);
        productAdapter.notifyDataSetChanged();
    }
}
