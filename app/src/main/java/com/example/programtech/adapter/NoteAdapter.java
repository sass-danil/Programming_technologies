package com.example.programtech.adapter;

import android.content.Context;
import android.text.TextUtils;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;
import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;
import com.example.programtech.R;
import com.example.programtech.model.Note;
import java.util.List;

public class NoteAdapter extends RecyclerView.Adapter<NoteAdapter.NotesViewHolder> {

    private Context context;
    private List<Note> notes;
    private OnNoteClickListener noteClickListener;

    public NoteAdapter(Context context, List<Note> notes, OnNoteClickListener noteClickListener) {
        this.context = context;
        this.notes = notes;
        this.noteClickListener = noteClickListener;
    }

    @NonNull
    @Override
    public NotesViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        View view = LayoutInflater.from(context).inflate(R.layout.note_item, parent, false);
        return new NotesViewHolder(view);
    }

    @Override
    public void onBindViewHolder(@NonNull NotesViewHolder holder, int position) {
        Note note = notes.get(position);
        holder.bind(note);
    }

    @Override
    public int getItemCount() {
        return notes.size();
    }

    public class NotesViewHolder extends RecyclerView.ViewHolder {

        TextView noteTitle;
        TextView noteContent;

        public NotesViewHolder(@NonNull View itemView) {
            super(itemView);
            noteTitle = itemView.findViewById(R.id.note_title);
            noteContent = itemView.findViewById(R.id.note_content);

            itemView.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View v) {
                    int position = getAdapterPosition();
                    if (position != RecyclerView.NO_POSITION && noteClickListener != null) {
                        noteClickListener.onNoteClick(position);
                    }
                }
            });

            itemView.setOnLongClickListener(new View.OnLongClickListener() {
                @Override
                public boolean onLongClick(View v) {
                    int position = getAdapterPosition();
                    if (position != RecyclerView.NO_POSITION && noteClickListener != null) {
                        noteClickListener.onNoteLongClick(position);
                    }
                    return true;
                }
            });
        }

        public void bind(Note note) {
            noteTitle.setText(note.getTitle());
            noteContent.setText(note.getContent());
            noteContent.setMaxLines(2);
            noteContent.setEllipsize(TextUtils.TruncateAt.END);
        }
    }

    public interface OnNoteClickListener {
        void onNoteClick(int position);
        void onNoteLongClick(int position);
    }
}
