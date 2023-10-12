#include "input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

deck_t * hand_from_string(const char * str, future_cards_t * fc) {
  deck_t * deck = malloc(sizeof(*deck));
  deck->cards = NULL;
  deck->n_cards = 0;
  const char * ptr = str;
  size_t count = 0;
  while (ptr[0] != '\n' && ptr[0] != '\0') {
    if (ptr[0] == '?') {
      card_t * c = add_empty_card(deck);
      add_future_card(fc, ptr[1]-'0', c);
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

deck_t ** read_input(FILE * f, size_t * n_hands, future_cards_t * \
fc) {
  deck_t ** deck_ts = NULL;
  char * line = NULL;
  size_t sz = 0;
  *n_hands = 0;
  while (getline(&line, &sz, f) > 1) { // new line will return 1       deck_t * current = hand_from_string(line, fc);
    if (line == NULL) {
      fprintf(stderr, "a poker hand has at least 5 cards in it.\n"\
);

      free(line);
      return NULL;
    }
    deck_ts = realloc(deck_ts, sizeof(*deck_ts)*(*n_hands+1));
    deck_ts[*n_hands] = current;
    (*n_hands)++;
  }
  free(line);
  return deck_ts;
}
