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

    private Context context;
    private List<Filter> filters;
    private static FilterClickListener listener;

    // Интерфейс для обработки кликов по элементам фильтра
    public interface FilterClickListener {
        void onFilterClicked(Filter filter);
    }

    // Конструктор адаптера
    public FilterAdapter(Context context, List<Filter> filters, FilterClickListener listener) {
        this.context = context;
        this.filters = filters;
        this.listener = listener;
    }

    @NonNull
    @Override
    public FilterViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        // Создание нового view
        View filterItems = LayoutInflater.from(context).inflate(R.layout.filter_item, parent, false);
        // viewType используется здесь как позиция списка
        return new FilterViewHolder(filterItems, listener, filters.get(viewType));
    }

    @Override
    public void onBindViewHolder(@NonNull FilterViewHolder holder, int position) {
        // Получение элемента фильтра и установка его названия
        Filter filter = filters.get(position);
        holder.filterTitle.setText(filter.getTitle());
        // Обновляем ссылку на фильтр в holder для правильной обработки кликов
        holder.updateFilter(filter);
    }

    @Override
    public int getItemCount() {
        return filters.size();
    }

    // Класс ViewHolder для элементов фильтра
    public static class FilterViewHolder extends RecyclerView.ViewHolder {
        TextView filterTitle;

        public FilterViewHolder(@NonNull View itemView, final FilterClickListener listener, final Filter filter) {
            super(itemView);
            filterTitle = itemView.findViewById(R.id.filterTitle);

            // Установка слушателя кликов с передачей текущего фильтра
            itemView.setOnClickListener(v -> listener.onFilterClicked(filter));
        }

        // Метод для обновления ссылки на текущий фильтр
        public void updateFilter(Filter newFilter) {
            itemView.setOnClickListener(v -> listener.onFilterClicked(newFilter));
        }
    }
}
