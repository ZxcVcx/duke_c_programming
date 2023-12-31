#include "input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

deck_t * hand_from_string(const char * str, future_cards_t * fc) {
  deck_t * deck = malloc(sizeof(*deck));
  deck->cards = NULL;
  deck->n_cards = 0;
  const char * ptr = str;

  // a typical str: "      0s  5s    ?0  ?2 ?4  3h  ?50 \n\0"
  while (*ptr != '\n' && *ptr != '\0') {
    if (*ptr == ' ') {
      ptr++;
      continue;
    }
    
    if (ptr[0] == '?') {
      int num = atoi(ptr+1);
      add_future_card(fc, num, add_empty_card(deck));
      while (*ptr != ' ' && *ptr != '\n' && *ptr != '\0') {
	ptr++;
      }
      ptr++;
    } else {
      add_card_to(deck, card_from_letters(ptr[0], ptr[1]));
      ptr+=3;
    }
  }
  if (deck->n_cards < 5) {
    free_deck(deck);
    return NULL;
  }
  return deck;
}

deck_t ** read_input(FILE * f, size_t * n_hands, future_cards_t * fc) {
  deck_t ** deck_ts = NULL;
  char * line = NULL;
  size_t sz = 0;
  *n_hands = 0;
  while (getline(&line, &sz, f) > 1) { // new line will return 1
    deck_t * current = hand_from_string(line, fc);
    if (current == NULL) {
      fprintf(stderr, "a poker hand has at least 5 cards in it.\n");

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
