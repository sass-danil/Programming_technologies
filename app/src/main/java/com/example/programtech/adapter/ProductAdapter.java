package com.example.programtech.adapter;

import android.content.Context;
import android.graphics.Color;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.appcompat.view.menu.MenuView;
import androidx.recyclerview.widget.RecyclerView;

import com.example.programtech.R;
import com.example.programtech.model.Product;
import com.google.android.material.transition.Hold;

import java.util.List;

public class ProductAdapter extends RecyclerView.Adapter<ProductAdapter.ProductViewHolder> {


    Context context;
    List<Product> products;

    public ProductAdapter(Context context, List<Product> products) {
        this.context = context;
        this.products = products;
    }

    @NonNull
    @Override
    public ProductViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        View productItems = LayoutInflater.from(context).inflate(R.layout.product_item,parent, false);
        return new ProductAdapter.ProductViewHolder(productItems);
    }

    @Override
    public void onBindViewHolder(@NonNull ProductViewHolder holder, int position) {
        holder.productBg.setBackgroundColor(Color.parseColor(products.get(position).getColor()));

        int imageId = context.getResources().getIdentifier( products.get(position).getImg(),"drawable", context.getPackageName());
        holder.productImg.setImageResource(imageId);

        holder.productName.setText(products.get(position).getTitle());
        holder.productDate.setText(products.get(position).getTitle());
        holder.productCount.setText(products.get(position).getTitle());

        int ButtonId = context.getResources().getIdentifier(products.get(position).getImg(),"drawable", context.getPackageName());
        holder.productButton.setImageResource(ButtonId);
    }

    @Override
    public int getItemCount() {
        return products.size();
    }

    public static final class ProductViewHolder extends RecyclerView.ViewHolder{

        LinearLayout productBg;
        ImageView productImg;
        TextView productName, productDate,productCount;
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
