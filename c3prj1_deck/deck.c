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
  for(unsigned i = 0; i < d->n_cards; i++) {
    for (unsigned j = 0; j < i; j++) {
      char value = value_letter(*d->cards[j]);
      char suit = suit_letter(*d->cards[j]);
      assert(!(value == value_letter(*d->cards[i]) && suit == suit_letter(*d->cards[i])));
    }
  }
}

void add_card_to(deck_t * deck, card_t c) {
  deck->cards = realloc(deck->cards, sizeof(*deck->cards)*(deck->n_cards+1));
  *deck->cards[deck->n_cards++] = c;
}

card_t * add_empty_card(deck_t * deck) {
  deck->cards = realloc(deck->cards, sizeof(*deck->cards)*(deck->n_cards+1));
  catd_t empty_card;
  empty_card->value=0;
  empty_card->suit=0;
  *deck->cards[deck->n_cards++] = empty_card;
  return deck->cards[deck->n_cards-1];
}

deck_t * make_deck_exclude(deck_t * exclude_cards) {
  deck_t * deck = malloc(sizeof(*deck));
  deck->cards = NULL;
  deck->n_cards = 0;
  for (unsigned i = 0; i < 52; i++) {
    card_t c = card_from_num(i);
    if (!deck_contains(exclude_cards, c)) {
      add_card_to(deck, c);
    }
  }
}

void free_deck(deck_t * deck) {
  free(deck->cards);
  free(deck);
}

deck_t * build_remaining_deck(deck_t ** hands, size_t n_hands) {
  deck_t * exclude = malloc(sizeof(*exclude));
  exclude->cards = NULL;
  deck->n_cards = 0;
  for (size_t i = 0; i < n_hands; i++) {
    for (size_t j = 0; j < hands[i]->n_cards; j++) {
      add_card_to(exclude, *hands[i]->cards[j]);
    }
  }
  deck_t * remain = make_deck_exclude(exclude);
  free_deck(exclude);
  return remain;
}
