#include "future.h"
#include <stdio.h>
#include <stdlib.h>

void add_future_card(future_cards_t * fc, size_t index, card_t * ptr) {
  if (fc->n_decks <= index) {
    fc->decks = realloc(fc->decks, sizeof(*fc->decks)*(index+1));
    for (int i = fc->n_decks; i < index+1; i++) {
      fc->decks[i].n_cards = 0;
      fc->decks[i].cards = NULL;
    }
    fc->n_decks = index+1;
  }

  fc->decks[i].cards = realloc(fc->decks[i].cards, sizeof(*fc->decks[i].cards)*(fc->decks[i].n_cards+1));
  fc->decks[i].cards[fc->decks[i].n_cards++] = ptr;
}

void future_cards_from_deck(deck_t * deck, future_cards_t * fc) {
  if (deck->n_cards < fc->n_decks) {
    fprintf(stderr, "Error: deck's cards less then fc's decks.\n");
    return;
  }
  for (int i = 0; i < fc->n_decks; i++) {
    if(fc->decks[i].n_cards > 0) {
      for (int j = 0; j <fc->decks[i].n_cards; j++) {
	*(fc->decks[i].cards[j]) = *(deck->cards[i]);
      }
    }
  }
}
