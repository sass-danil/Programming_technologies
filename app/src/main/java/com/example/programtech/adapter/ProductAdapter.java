package com.example.programtech.adapter;

import android.app.DatePickerDialog;
import android.content.Context;
import android.graphics.Color;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.EditText;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.TextView;
import androidx.annotation.NonNull;
import androidx.appcompat.app.AlertDialog;
import androidx.recyclerview.widget.RecyclerView;
import com.example.programtech.R;
import com.example.programtech.model.Product;

import java.util.Calendar;
import java.util.List;
import java.util.Locale;

public class ProductAdapter extends RecyclerView.Adapter<ProductAdapter.ProductViewHolder> {

    private Context context;
    private List<Product> products;

    public ProductAdapter(Context context, List<Product> products) {
        this.context = context;
        this.products = products;
    }

    @NonNull
    @Override
    public ProductViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        View productItems = LayoutInflater.from(context).inflate(R.layout.product_item, parent, false);
        return new ProductViewHolder(productItems);
    }

    @Override
    public void onBindViewHolder(@NonNull ProductViewHolder holder, int position) {
        Product product = products.get(position);
        holder.productBg.setBackgroundColor(Color.parseColor(product.getColor())); // Ensure color format is correct

        int imageId = context.getResources().getIdentifier(product.getImg(), "drawable", context.getPackageName());
        holder.productImg.setImageResource(imageId);

        holder.productName.setText(product.getTitle());
        holder.productDate.setText(product.getDate());
        holder.productCount.setText(String.valueOf(product.getCount()));

        holder.productButton.setOnClickListener(v -> showEditProductDialog(position, product));
    }

    @Override
    public int getItemCount() {
        return products.size();
    }

    private void showEditProductDialog(final int position, Product product) {
        LayoutInflater inflater = LayoutInflater.from(context);
        View view = inflater.inflate(R.layout.edit_product_dialog, null);

        EditText productNameInput = view.findViewById(R.id.productNameInput);
        EditText productDateInput = view.findViewById(R.id.productDateInput);
        EditText productCountInput = view.findViewById(R.id.productCountInput);
        EditText productIconInput = view.findViewById(R.id.productIconInput);

        productNameInput.setText(product.getTitle());
        productDateInput.setText(product.getDate());
        productCountInput.setText(String.valueOf(product.getCount()));
        productIconInput.setText(product.getImg());

        // Set up the date picker dialog
        productDateInput.setOnClickListener(v -> {
            Calendar cal = Calendar.getInstance();
            int year = cal.get(Calendar.YEAR);
            int month = cal.get(Calendar.MONTH);
            int day = cal.get(Calendar.DAY_OF_MONTH);

            DatePickerDialog datePickerDialog = new DatePickerDialog(context, (view1, year1, monthOfYear, dayOfMonth) -> {
                // Set the date string in the format you prefer
                productDateInput.setText(String.format(Locale.US, "%02d/%02d/%04d", dayOfMonth, monthOfYear + 1, year1));
            }, year, month, day);

            datePickerDialog.show();
        });

        AlertDialog dialog = new AlertDialog.Builder(context)
                .setTitle("Редактировать продукт")
                .setView(view)
                .setPositiveButton("Сохранить", (dialog12, which) -> {
                    product.setTitle(productNameInput.getText().toString());
                    product.setDate(productDateInput.getText().toString());
                    product.setCount(Integer.parseInt(productCountInput.getText().toString()));
                    product.setImg(productIconInput.getText().toString());
                    notifyItemChanged(position);
                })
                .setNegativeButton("Отмена", null)
                .setNeutralButton("Удалить", (dialog1, which) -> {
                    products.remove(position);
                    notifyItemRemoved(position);
                    notifyItemRangeChanged(position, products.size());
                })
                .create();
        dialog.show();
    }

    public static final class ProductViewHolder extends RecyclerView.ViewHolder {

        LinearLayout productBg;
        ImageView productImg;
        TextView productName, productDate, productCount;
        ImageButton productButton;

        public ProductViewHolder(@NonNull View itemView) {
            super(itemView);
            productBg = itemView.findViewById(R.id.product_bg);
            productImg = itemView.findViewById(R.id.product_img);
            productName = itemView.findViewById(R.id.product_name);
            productDate = itemView.findViewById(R.id.product_date);
            productCount = itemView.findViewById(R.id.product_count);
            productButton = itemView.findViewById(R.id.product_button);
        }
    }
}
