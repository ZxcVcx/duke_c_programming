#include "input.h"
#include <stdio.h>
#include <stdlib.h>

deck_t * hand_from_string(const char * str, future_cards_t * fc) {
  deck_t * deck = malloc(sizeof(*deck));
  deck->cards = NULL;
  deck->n_cards = 0;
  char * ptr = NULL;
  size_t count = 0;
  while (*ptr != '\n' && *ptr != '\0') {
    if (ptr[0] == '?') {
      card_t * c = add_empty_card(deck);
      add_future_card(fc, count, c);
    } else {
      card_t c = card_from_letters(ptr[0], ptr[1]);
      assert_card_valid(c);
      add_card_to(deck, c);
    }
    ptr += 3;
    count++;
  }
  if (count < 5) {
    free_deck(deck);
    return NULL;
  }
  return deck;
}

deck_t ** read_input(FILE * f, size_t * n_hands, future_cards_t * fc) {
  deck_t ** decks = NULL;
  char * line = NULL;
  size_t sz = 0;
  *n_hands = 0;
  while (getline(&line, &sz, f) >= 0) {
    deck_t * current = hand_from_string(line, fc);
    if (current == NULL) {
      fprintf(stderr, "a poker hand has at least 5 cards in it.\n");
      free(line);
      return NULL;
    }
    decks = realloc(deck, sizeof(*deck)*(*n_hand+1));
    decks[*n_hand] = current;
    (*n_hand)++;
  }
  free(line);
  return decks;
}
