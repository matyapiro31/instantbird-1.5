/* -*- Mode: Java; c-basic-offset: 4; tab-width: 20; indent-tabs-mode: nil; -*-
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

package org.mozilla.gecko;

import org.mozilla.gecko.AwesomeBarTabs.OnUrlOpenListener;
import org.mozilla.gecko.util.GamepadUtils;
import org.mozilla.gecko.util.StringUtils;
import org.mozilla.gecko.widget.FaviconView;

import android.content.Context;
import android.content.res.TypedArray;
import android.util.AttributeSet;
import android.view.KeyEvent;
import android.view.LayoutInflater;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.View.OnLongClickListener;
import android.view.animation.AlphaAnimation;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.TextView;

class SearchEngineRow extends AnimatedHeightLayout {
    // Duration for fade-in animation
    private static final int ANIMATION_DURATION = 250;

    // Inner views
    private final FlowLayout mSuggestionView;
    private final FaviconView mIconView;
    private final LinearLayout mUserEnteredView;
    private final TextView mUserEnteredTextView;

    // Inflater used when updating from suggestions
    private final LayoutInflater mInflater;

    // Search engine associated with this view
    private SearchEngine mSearchEngine;

    // Selected suggestion view
    private int mSelectedView = 0;

    // Event listeners for suggestion views
    private final OnClickListener mClickListener;
    private final OnLongClickListener mLongClickListener;

    // On URL open listener
    private OnUrlOpenListener mUrlOpenListener;

    public SearchEngineRow(Context context) {
        this(context, null);
    }

    public SearchEngineRow(Context context, AttributeSet attrs) {
        this(context, attrs, 0);
    }

    public SearchEngineRow(Context context, AttributeSet attrs, int defStyle) {
        super(context, attrs, defStyle);

        mClickListener = new OnClickListener() {
            @Override
            public void onClick(View v) {
                final String suggestion = getSuggestionTextFromView(v);

                // If we're not clicking the user-entered view (the first suggestion item)
                // and the search matches a URL pattern, go to that URL. Otherwise, do a
                // search for the term.
                if (mUrlOpenListener != null) {
                    if (v != mUserEnteredView && !StringUtils.isSearchQuery(suggestion, false)) {
                        mUrlOpenListener.onUrlOpen(suggestion, null);
                    } else {
                        mUrlOpenListener.onSearch(mSearchEngine, suggestion);
                    }
                }
            }
        };

        mLongClickListener = new OnLongClickListener() {
            @Override
            public boolean onLongClick(View v) {
                if (mUrlOpenListener != null) {
                    final String suggestion = getSuggestionTextFromView(v);
                    mUrlOpenListener.onEditSuggestion(suggestion);
                    return true;
                }

                return false;
            }
        };

        mInflater = LayoutInflater.from(context);
        mInflater.inflate(R.layout.search_engine_row, this);

        mSuggestionView = (FlowLayout) findViewById(R.id.suggestion_layout);
        mIconView = (FaviconView) findViewById(R.id.suggestion_icon);

        // User-entered search term is first suggestion
        mUserEnteredView = (LinearLayout) findViewById(R.id.suggestion_user_entered);
        mUserEnteredView.setOnClickListener(mClickListener);

        mUserEnteredTextView = (TextView) findViewById(R.id.suggestion_text);
    }

    private String getSuggestionTextFromView(View v) {
        final TextView suggestionText = (TextView) v.findViewById(R.id.suggestion_text);
        return suggestionText.getText().toString();
    }

    private void setSuggestionOnView(View v, String suggestion) {
        final TextView suggestionText = (TextView) v.findViewById(R.id.suggestion_text);
        suggestionText.setText(suggestion);
    }

    public void setSearchTerm(String searchTerm) {
        mUserEnteredTextView.setText(searchTerm);
    }

    public void setOnUrlOpenListener(OnUrlOpenListener listener) {
        mUrlOpenListener = listener;
    }

    public void updateFromSearchEngine(SearchEngine searchEngine, boolean doAnimation) {
        // Update search engine reference
        mSearchEngine = searchEngine;

        // Set the search engine icon (e.g., Google) for the row
        mIconView.updateImage(mSearchEngine.icon, mSearchEngine.name);

        // Add additional suggestions given by this engine
        final int recycledSuggestionCount = mSuggestionView.getChildCount();
        final int suggestionCount = mSearchEngine.suggestions.size();

        for (int i = 0; i < suggestionCount; i++) {
            final View suggestionItem;

            // Reuse suggestion views from recycled view, if possible
            if (i + 1 < recycledSuggestionCount) {
                suggestionItem = mSuggestionView.getChildAt(i + 1);
                suggestionItem.setVisibility(View.VISIBLE);
            } else {
                suggestionItem = mInflater.inflate(R.layout.suggestion_item, null);

                suggestionItem.setOnClickListener(mClickListener);
                suggestionItem.setOnLongClickListener(mLongClickListener);

                final ImageView magnifier =
                        (ImageView) suggestionItem.findViewById(R.id.suggestion_magnifier);
                magnifier.setVisibility(View.GONE);

                mSuggestionView.addView(suggestionItem);
            }

            final String suggestion = mSearchEngine.suggestions.get(i);
            setSuggestionOnView(suggestionItem, suggestion);

            if (doAnimation) {
                AlphaAnimation anim = new AlphaAnimation(0, 1);
                anim.setDuration(ANIMATION_DURATION);
                anim.setStartOffset(i * ANIMATION_DURATION);
                suggestionItem.startAnimation(anim);
            }
        }

        // Hide extra suggestions that have been recycled
        for (int i = suggestionCount + 1; i < recycledSuggestionCount; i++) {
            mSuggestionView.getChildAt(i).setVisibility(View.GONE);
        }

        // Make sure mSelectedView is still valid
        if (mSelectedView >= mSuggestionView.getChildCount()) {
            mSelectedView = mSuggestionView.getChildCount() - 1;
        }
    }

    @Override
    public boolean onKeyDown(int keyCode, android.view.KeyEvent event) {
        final View suggestion = mSuggestionView.getChildAt(mSelectedView);

        if (event.getAction() != android.view.KeyEvent.ACTION_DOWN) {
            return false;
        }

        switch (event.getKeyCode()) {
        case KeyEvent.KEYCODE_DPAD_RIGHT:
            final View nextSuggestion = mSuggestionView.getChildAt(mSelectedView + 1);
            if (nextSuggestion != null) {
                changeSelectedSuggestion(suggestion, nextSuggestion);
                mSelectedView++;
                return true;
            }
            break;

        case KeyEvent.KEYCODE_DPAD_LEFT:
            final View prevSuggestion = mSuggestionView.getChildAt(mSelectedView - 1);
            if (prevSuggestion != null) {
                changeSelectedSuggestion(suggestion, prevSuggestion);
                mSelectedView--;
                return true;
            }
            break;

        case KeyEvent.KEYCODE_BUTTON_A:
            // TODO: handle long pressing for editing suggestions
            return suggestion.performClick();
        }

        return false;
    }

    private void changeSelectedSuggestion(View oldSuggestion, View newSuggestion) {
        oldSuggestion.setDuplicateParentStateEnabled(false);
        newSuggestion.setDuplicateParentStateEnabled(true);
        oldSuggestion.refreshDrawableState();
        newSuggestion.refreshDrawableState();
    }

    public void onSelected() {
        mSelectedView = 0;
        mUserEnteredView.setDuplicateParentStateEnabled(true);
        mUserEnteredView.refreshDrawableState();
    }

    public void onDeselected() {
        final View suggestion = mSuggestionView.getChildAt(mSelectedView);
        suggestion.setDuplicateParentStateEnabled(false);
        suggestion.refreshDrawableState();
    }
}