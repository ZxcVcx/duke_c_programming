#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "deck.h"
void print_hand(deck_t * hand){
  for(unsigned i = 0; i < hand->n_cards; i++) {
    // print_card(*((*hand).cards[i]));
    print_card(*hand->cards[i]);
    printf(" ");
  }
}

int deck_contains(deck_t * d, card_t c) {
  for (unsigned i = 0; i < d->n_cards; i++) {
    char value = value_letter(*d->cards[i]);
    char suit = suit_letter(*d->cards[i]);
    if (value == value_letter(c) && suit == suit_letter(c)) {
      return 1;
    }
  }
  return 0;
}

void shuffle(deck_t * d){
  for (unsigned i = 0; i < d->n_cards; i++) {
    unsigned rand = random() / (RAND_MAX / (i+1));
    card_t tmp = *d->cards[i];
    *d->cards[i] = *d->cards[rand];
    *d->cards[rand] = tmp;
  } 
}

void assert_full_deck(deck_t * d) {
  // for(unsigned i = 0; i < d->n_cards; i++) {
  //  assert_card_valid(*d->cards[i]);
  //}
  for(unsigned i = 0; i < d->n_cards; i++) {
    // unsigned dup = 0;
    for (unsigned j = 0; j < i; j++) {
      char value = value_letter(*d->cards[j]);
      char suit = suit_letter(*d->cards[j]);
      assert(!(value == value_letter(*d->cards[i]) && suit == suit_letter(*d->cards[i])));
    }
  }
}
