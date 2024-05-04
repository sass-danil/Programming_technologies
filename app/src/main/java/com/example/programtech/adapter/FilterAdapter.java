package com.example.programtech.adapter;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import com.example.programtech.R;
import com.example.programtech.model.Filter;

import java.util.List;

public class FilterAdapter extends RecyclerView.Adapter<FilterAdapter.FilterViewHolder> {

    Context context;
    List<Filter> filters;

    public FilterAdapter(Context context, List<Filter> filters) {
        this.context = context;
        this.filters = filters;
    }
    @NonNull
    @Override
    public FilterViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        View filterItems = LayoutInflater.from(context).inflate(R.layout.filter_item,parent, false);
        return new FilterViewHolder(filterItems);
    }
    @Override
    public void onBindViewHolder(@NonNull FilterViewHolder holder, int position) {
        holder.filterTitle.setText(filters.get(position).getTitle());
    }
    @Override
    public int getItemCount() {
        return filters.size();
    }

    public static final class FilterViewHolder extends RecyclerView.ViewHolder{
        TextView filterTitle;
        public FilterViewHolder(@NonNull View itemView) {
            super(itemView);

            filterTitle = itemView.findViewById(R.id.filterTitile);
        }
    }

}
